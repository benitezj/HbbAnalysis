#include "ZmmPlotter.C"
#include "configZmm.C"
#include "plotZmm.C"


void runZmm(TString intag="",TString outtag=""){  

  gROOT->ProcessLine(".L ./HbbAnalysis/plots/ZmmPlotter.C+");
  
    
  TString inpath=inputDir_+"/CxTupleSamples/Zmm/"+CXTAG;
  if(intag.CompareTo("")!=0)inpath+="_"+intag;//version of the ntuples

  TString outpath=outputDir_+"/DC14Studies/Zmm/"+CXTAG;
  if(intag.CompareTo("")!=0)outpath+="_"+intag;
  if(outtag.CompareTo("")!=0)outpath+="_"+outtag;//version of the plots

  system(TString("rm -rf ")+outpath);
  system(TString("mkdir ")+outpath);

  ZmmPlotter * analysis = new ZmmPlotter("analysis",atlasInternal8TeV);
  configZmm(analysis,inpath,outpath);
  

  plotZmm(analysis);
  
  //analysis->plot("eve_mu",40,0,40,"","# of interactions","",c2,"mu");
  //analysis->plot("mm_m[zll_ll]/1000",100,50,130,""," mass(#mu^{+}#mu^{-}) (GeV)","",c2,"zll_m");
 
  //analysis->plot("zll_njet",10,0,10,"","# of central jets","",c2,"zll_njet");
  //analysis->plot("jet_pt[zll_jet]/1000",100,0,200,"zll_njet>0","lead central jet p_{T} (GeV)","",c2,"zll_leadjet_pt");

  gROOT->ProcessLine(".q");
}
