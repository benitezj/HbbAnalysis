
#define NPILEUPBINS 100
#define PILEUPMIN 0
#define PILEUPMAX 100

void pileUpData(TString filename,TString fileout="pileup.root"){
  TFile input(filename,"READ");
  TH1F*HIn=(TH1F*)input.Get("avgintperbx");  
  
  //Rebin the input histogram 
  TH1F H("pileup","pileup",NPILEUPBINS,PILEUPMIN,PILEUPMAX);
  for(int bi=1;bi<=NPILEUPBINS;bi++){
    for(int bo=1;bo<=HIn->GetXaxis()->GetNbins();bo++){
      if( H.GetBinLowEdge(bi) < HIn->GetBinCenter(bo)
	  && 
	  HIn->GetBinCenter(bo) <= H.GetBinLowEdge(bi)+H.GetBinWidth(bi) ) 
	H.AddBinContent(bi,HIn->GetBinContent(bo));
    }
  }

  //normalize to unity
  if(H.Integral()>0){
    H.Scale(1./H.Integral());
  }else{
    cout<<"Histogram Integral is less than 0"<<endl;
    exit();
  }
  

  TFile output(fileout,"RECREATE");
  H.Write();
  output.ls();
  
  gROOT->ProcessLine(".q");
}

void pileUpMC(TString sample,TString fileout="pileup.root"){

  //TString sample="/afs/cern.ch/work/b/benitezj/CxTupleSamples/Zmm/00-00-06/mc14_8TeV.147807.PowhegPythia8_AU2CT10_Zmumu.merge.AOD.e1852_s1896_s1912_r5591_r5625_tid01522869_00";

  Sample S("S",sample);
  
  TH1F*H=S.getPileUp();

  //normalize to unity                                                                                                                            
  if(H->Integral()>0){
    H->Scale(1./H->Integral());
  }else{
    cout<<"Histogram Integral is less than 0"<<endl;
    exit();
  }
  
  TFile output(fileout,"RECREATE");
  H->SetName("pileup");
  H->Write();
  output.ls();
  

  gROOT->ProcessLine(".q");
}
