#include "plotterGlobals.h"

void compareSignalAndBkg(Sample* S, Sample* B, TString var, int nbins, float xmin, float xmax,
			 TString selection, TString xlabel, TCanvas*C,TString outpath){
  if(!S || !B) return;

  TH1F* HS=new TH1F("HS","",nbins,xmin,xmax);
  HS->GetXaxis()->SetTitle(xlabel);
  S->fillHisto(HS,var,selection.Data());
  HS->Scale(1./HS->Integral());
  
  TH1F* HB=new TH1F("HB","",nbins,xmin,xmax);
  HB->GetXaxis()->SetTitle(xlabel);
  B->fillHisto(HB,var,selection.Data());
  HB->Scale(1./HB->Integral());
  

  ////Linear Plot
  C->Clear();
  HS->GetYaxis()->SetRangeUser(0, HS->GetMaximum() > HB->GetMaximum() ? 1.2*HS->GetMaximum() : 1.2*HB->GetMaximum());
  HS->Draw("histp");
  HB->Draw("histsame");
  C->Print(outpath+".png");
  
  //Log Plot
  HS->GetYaxis()->SetRangeUser( HS->GetMaximum() < HB->GetMaximum() ? 1e-5*HS->GetMaximum() : 1e-5*HB->GetMaximum(),
  				HS->GetMaximum() > HB->GetMaximum() ? 10*HS->GetMaximum() : 10*HB->GetMaximum());
  C->SetLogy(1);
  C->Update();
  C->Print(outpath+".log.png");
  C->SetLogy(0);

  delete HS;
  delete HB;
}


TGraphErrors * makeROC(Sample* S, Sample* B, TString var, int n, float min, float max, TString type=""){
  if(!S || !B || n<=0){
    cout<<"invalid inputs"<<endl; return 0;
  }

  TGraphErrors * Graph = new TGraphErrors();
  
  //Get the total 
  TH1D HSigTot("HSigTot","",n,min,max);
  S->fillHisto(&HSigTot,var);
  TH1D HBkgTot("HBkgTot","",n,min,max);
  B->fillHisto(&HBkgTot,var);

  if(HSigTot.Integral(0,n+1) <= 0. 
     || HBkgTot.Integral(0,n+1) <= 0.){
    cout<<"Samples have 0 integral. "<<endl; return 0;
  }


  int counter=0;
  for(int i=0;i<n;i++){
    char cut[100];
    sprintf(cut,"%s>%.3e",var.Data(),min+i*(max-min)/n);
    
    TH1D HSig(TString("HSig")+(long)i,"",n,min,max);
    S->fillHisto(&HSig,var,cut);
    TH1D HBkg(TString("HBkg")+(long)i,"",n,min,max);
    B->fillHisto(&HBkg,var,cut);

    //calculate efficiencies
    double sigEff= HSig.Integral(0,n+1)/HSigTot.Integral(0,n+1);
    double bkgEff= HBkg.Integral(0,n+1)/HBkgTot.Integral(0,n+1);
    
    if(sigEff<=0. || bkgEff<=0.) continue;

    //Estimate the stat error on the efficiency
    double sigErr=0.;
    double bkgErr=0.;
    for(int b=0;b<=n;b++){
      //include underflow and overflow 
      sigErr += HSig.GetBinError(b)*HSig.GetBinError(b);
      bkgErr += HBkg.GetBinError(b)*HBkg.GetBinError(b);
    }
    sigErr=sqrt(sigErr)/HSig.Integral(0,n+1);//these are the relative errors
    bkgErr=sqrt(bkgErr)/HBkg.Integral(0,n+1);

    cout<<i<<" "<<cut<<" : SignalEff="<<sigEff<<"+/-"<<sigEff<<"%, BkgEff="<<bkgEff<<"+/-"<<bkgEff<<"%"<<endl;
    if(sigErr>0.6 || bkgErr>0.6 || sigErr<=0. || bkgErr<=0.)  continue;
    

    ////Fill the graph
    if(type.CompareTo("efficiency")==0){ 
      Graph->SetPoint(counter,sigEff,bkgEff);
      Graph->SetPointError(counter,
			   sigEff*sigErr,
			   bkgEff*bkgErr
			   );
    }
    if(type.CompareTo("rejection")==0){
      double rej=1/bkgEff;
      Graph->SetPoint(counter,sigEff,rej);
      Graph->SetPointError(counter,
			   sigEff*sigErr,
			   rej*bkgErr
			   );
    }


    counter++;
  }
  

  return Graph;
}


void compareSamples(Sample* sample1, Sample* sample2, 
		    TString var, int N, float xmin, float xmax,
		    TString outpath, TString outname, TString selection=""){
  

  TH1F H1("H1","",N,xmin,xmax);
  H1.GetXaxis()->SetTitle(var);
  sample1->fillHisto(&H1,var,selection.Data());

  TH1F H2("H2","",N,xmin,xmax);
  H2.GetXaxis()->SetTitle(var);
  sample2->fillHisto(&H2,var,selection.Data());


  TH1F* hRatio = H2.Clone("HRatio");
  for(Int_t b=1;b<=N;b++) {
    if(H1.GetBinContent(b)>0.) hRatio->SetBinContent(b, H2.GetBinContent(b) / H1.GetBinContent(b) );
    else  hRatio->SetBinContent(b,0);
    hRatio->SetBinError(b,0);//do not show error as these two samples should have the same events in principle 
  }
  
  TPad * pad1=new TPad("pad1","",0,0.2,1,1);
  TPad * pad2=new TPad("pad2","",0,0,1,0.2);
  
  pad1->cd();
  if(H1.GetMaximum()>H2.GetMaximum()){
    H1.Draw("hist");
    H2.Draw("histpsame");
  }else {
    H2.Draw("histp");//H2 is always the new production and should plotted with points
    H1.Draw("histsame");
  }
  
  pad2->cd();
  hRatio->SetStats(0);
  hRatio->SetTitle("");
  hRatio->GetYaxis()->SetTitle("ratio");
  hRatio->GetXaxis()->SetTitle("");
  hRatio->GetYaxis()->SetNdivisions(5);
  hRatio->GetYaxis()->SetLabelSize(0.15);
  hRatio->GetYaxis()->SetTitleSize(0.2);
  hRatio->GetYaxis()->SetTitleOffset(0.20);
  hRatio->GetXaxis()->SetNdivisions(-1);
  hRatio->GetXaxis()->SetLabelSize(0.0001);
  hRatio->GetYaxis()->SetRangeUser(0.8,1.2);
  hRatio->Draw("hist pe");
  TLine line;
  line.DrawLine(xmin,1,xmax,1);
  
  TCanvas C;    
  C.Clear();
  pad1->Draw();
  pad2->Draw();
  C.Print(outpath+"/"+outname+".png");

  delete hRatio;
}


void compareCollections(Sample* sample, TString coll1, TString coll2, 
			TString var, int N, float xmin, float xmax,
			TString outpath, TString outname, TString selection=""){
  

  TH1F H1("H1","",N,xmin,xmax);
  H1.GetXaxis()->SetTitle(var);
  sample->fillHisto(&H1,coll1+"."+var,selection.Data());

  TH1F H2("H2","",N,xmin,xmax);
  H2.GetXaxis()->SetTitle(var);
  sample->fillHisto(&H2,coll2+"."+var,selection.Data());
  


  TH1F* hRatio = H2.Clone("HRatio");
  for(Int_t b=1;b<=N;b++) {
    if(H1.GetBinContent(b)>0.) hRatio->SetBinContent(b, H2.GetBinContent(b) / H1.GetBinContent(b) );
    else  hRatio->SetBinContent(b,0);
    hRatio->SetBinError(b,0);//do not show error as these two samples should have the same events in principle 
  }
  
  TPad * pad1=new TPad("pad1","",0,0.2,1,1);
  TPad * pad2=new TPad("pad2","",0,0,1,0.2);
  
  pad1->cd();
  if(H1.GetMaximum()>H2.GetMaximum()){
    H1.Draw("hist");
    H2.Draw("histpsame");
  }else {
    H2.Draw("histp");//H2 is always the new production and should plotted with points
    H1.Draw("histsame");
  }
  
  pad2->cd();
  hRatio->SetStats(0);
  hRatio->SetTitle("");
  hRatio->GetYaxis()->SetTitle("ratio");
  hRatio->GetXaxis()->SetTitle("");
  hRatio->GetYaxis()->SetNdivisions(5);
  hRatio->GetYaxis()->SetLabelSize(0.15);
  hRatio->GetYaxis()->SetTitleSize(0.2);
  hRatio->GetYaxis()->SetTitleOffset(0.20);
  hRatio->GetXaxis()->SetNdivisions(-1);
  hRatio->GetXaxis()->SetLabelSize(0.0001);
  hRatio->GetYaxis()->SetRangeUser(0.8,1.2);
  hRatio->Draw("hist pe");
  TLine line;
  line.DrawLine(xmin,1,xmax,1);
  
  TCanvas C;    
  C.Clear();
  pad1->Draw();
  pad2->Draw();
  C.Print(outpath+"/"+outname+".png");

  delete hRatio;
}
