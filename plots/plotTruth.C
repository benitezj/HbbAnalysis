#include "Sample.h"
#include "plotterGlobals.h"

///////////////////////////////
void plotGenTruth(Sample* sample, TString histName, int nbins, float xmin, float xmax, 
		  TString xlabel, TString outpath){
  
  TCanvas C;

  TH1F* Hist = sample->getHisto(histName,nbins,xmin,xmax);
  if(!Hist){cout<<"Histo not found: "<<histName<<endl; return;}
  Hist->SetName(sample->GetName()+histName);
  Hist->Scale(1./sample->getSampleEventsSumW());

  Hist->GetXaxis()->SetTitle(xlabel);

  const char title[100];
  sprintf(title,"Integral = %.2f, Mean=%.1f, RMS=%.1f",Hist->Integral(),Hist->GetMean(),Hist->GetRMS());
  Hist->SetTitle(title);

  
  C.Clear();
  C.SetLogy(0);
  Hist->Draw("hist");
  C.Print(outpath+".png");
  Hist->GetYaxis()->SetRangeUser(1e-6*Hist->GetMaximum(),10*Hist->GetMaximum());
  C.SetLogy(1);
  C.Update();
  C.Print(outpath+".log.png");

  delete Hist;
}


void plotGenTruth_PtEtaPhi(Sample* sample, TString particleName, TString outpath){
  plotGenTruth(sample,TString("HGen_")+particleName+"_pt",50,0,500,"gen. p_{T} (GeV)",outpath+"_pt");
  plotGenTruth(sample,TString("HGen_")+particleName+"_eta",100,-10,10,"gen. eta",outpath+"_eta");
  //plotGenTruth(sample,TString("HGen_")+particleName+"_phi",100,-3.5,3.5,"ge. phi",outpath+"_phi");
}


//////////////////////////////////////////////////////////////
void plotTruth(Sample*sample, TString var, int nbins, float xmin, float xmax, 
	       TCut selection, TString xlabel, TString outpath){

  TCanvas C;

  TH1F* Hist = sample->getHistoNtpFile(var,nbins,xmin,xmax,selection);
  Hist->SetName(sample->GetName()+var);
  Hist->GetXaxis()->SetTitle(xlabel);

  const char title[100];
  sprintf(title,"Integral = %.2f, Mean=%.1f, RMS=%.1f",Hist->Integral(),Hist->GetMean(),Hist->GetRMS());
  Hist->SetTitle(title);
  
  C.Clear();
  C.SetLogy(0);
  Hist->Draw("hist");
  C.Print(outpath+".png");
  Hist->GetYaxis()->SetRangeUser(1,10*Hist->GetMaximum());
  C.SetLogy(1);
  C.Update();
  C.Print(outpath+".log.png");

  delete Hist;
}

void plotTruth_MPtEtaPhi(Sample* sample, TString index, TCut selection, TString outpath){
  plotTruth(sample,index,16,-1,15,"",index,&C,outpath+"_truthidx");
  plotTruth(sample,TString("truth_pt[")+index+"]/1000",100,0,500,selection,"gen. p_{T}",outpath+"_pt");
  plotTruth(sample,TString("truth_eta[")+index+"]",100,-8,8,selection,"gen. eta",outpath+"_eta");
  plotTruth(sample,TString("truth_phi[")+index+"]",100,-3.5,3.5,selection,"gen. phi",outpath+"_phi");
}


//////////////////////////////////
void plotTruthResolution(Sample*sample, TString var, TString refvar, int nbins, float xmin, float xmax, 
			 TString selection, TString xlabel, TString outpath){

  TCanvas C;

  TH1F Hist("Hist","",nbins,xmin,xmax); 
  sample->fillHisto(&Hist,var+"-"+refvar,TCut(selection));
  Hist.SetName(sample->GetName()+refvar+"Resolution");
  Hist.GetXaxis()->SetTitle(xlabel);
  Hist.Scale(1./Hist.Integral());

  const char title[100];
  sprintf(title,"Integral = %.2f, Mean=%.1f, RMS=%.1f",Hist.Integral(),Hist.GetMean(),Hist.GetRMS());
  Hist.SetTitle(title);

  
  C.Clear();
  C.SetLogy(0);
  Hist.Draw("hist");
  C.Print(outpath+".png");
  Hist.GetYaxis()->SetRangeUser(1e-4*Hist.GetMaximum(),10*Hist.GetMaximum());
  C.SetLogy(1);
  C.Update();
  C.Print(outpath+".log.png");

}


void plotTruthEfficiency(Sample* sample, TString histName, TString truthvar, int nbins, float xmin, float xmax, 
			 TString selection, TString xlabel, float ymax, TString outpath){

  TCanvas C;

  TH1F* HistGen = sample->getHisto(histName,nbins,xmin,xmax);
  if(!HistGen){cout<<"Histo not found: "<<histName<<endl; return;}
  HistGen->SetName(sample->GetName()+histName);
  HistGen->GetXaxis()->SetTitle(xlabel);


  TH1F HistReco(sample->GetName()+histName+"Efficiency","",nbins,xmin,xmax); 
  HistReco.Sumw2();
  sample->fillHisto(&HistReco,truthvar,TCut(selection));
  HistReco.GetXaxis()->SetTitle(xlabel);


  C.Clear();
  HistGen->GetYaxis()->SetTitle("Efficiency");
  HistGen->GetYaxis()->SetRangeUser(1,HistGen->GetMaximum()*10);
  HistGen->Draw("hist");
  HistReco.Draw("histpesame");
  C.SetLogy(1);
  C.Print(outpath+"_dist.log.png");
  C.SetLogy(0);

  //HistReco.Divide(HistGen);//cannot call this function because it will add the errors from the generator
  for(int b=1;b<=nbins;b++){
    if(HistGen->GetBinContent(b)>0. &&
       HistReco.GetBinError(b)/HistReco.GetBinContent(b)<0.5
       ){
      
      HistReco.SetBinContent(b,HistReco.GetBinContent(b)/HistGen->GetBinContent(b));
      HistReco.SetBinError(b,HistReco.GetBinError(b)/HistGen->GetBinContent(b));
    }else {
      HistReco.SetBinContent(b,0.);
      HistReco.SetBinError(b,0.);
    }
  }

  C.Clear();
  HistReco.GetYaxis()->SetTitle("Efficiency");
  HistReco.GetYaxis()->SetRangeUser(0,ymax);
  HistReco.Draw("histpe");
  C.Print(outpath+".png");

}
