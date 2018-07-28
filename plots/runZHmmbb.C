#include "ZHmmbbPlotter.C"
#include "configZHmmbb.C"
#include "plotZHmmbb.C"


void runZHmmbb(TString intag="",TString outtag=""){  

  gROOT->ProcessLine(".L ./HbbAnalysis/plots/ZHmmbbPlotter.C+");
    
  TString inpath=inputDir_+"/CxTupleSamples/ZHmmbb/"+CXTAG;
  if(intag.CompareTo("")!=0)inpath+="_"+intag;//version of the ntuples

  TString outpath=outputDir_+"/DC14Studies/ZHmmbb/"+CXTAG;
  if(intag.CompareTo("")!=0)outpath+="_"+intag;
  if(outtag.CompareTo("")!=0)outpath+="_"+outtag;//version of the plots

  system(TString("rm -rf ")+outpath);
  system(TString("mkdir ")+outpath);

  ZHmmbbPlotter * analysis = new ZHmmbbPlotter("analysis",atlasInternal8TeV);
  if(!(configZHmmbb(analysis,inpath,outpath))){
    cout<<"Failed to config"<<endl;
    return;
  }
    
  plotZHmmbb(analysis);
 
  gROOT->ProcessLine(".q");
}
