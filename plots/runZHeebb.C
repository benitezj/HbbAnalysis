#include "ZHeebbPlotter.C"
#include "configZHeebb.C"
#include "plotZHeebb.C"


void runZHeebb(TString intag="",TString outtag=""){  

  gROOT->ProcessLine(".L ./HbbAnalysis/plots/ZHeebbPlotter.C+");
    
  TString inpath=inputDir_+"/CxTupleSamples/ZHeebb/"+CXTAG;
  if(intag.CompareTo("")!=0)inpath+="_"+intag;//version of the ntuples

  TString outpath=outputDir_+"/DC14Studies/ZHeebb/"+CXTAG;
  if(intag.CompareTo("")!=0)outpath+="_"+intag;
  if(outtag.CompareTo("")!=0)outpath+="_"+outtag;//version of the plots

  system(TString("rm -rf ")+outpath);
  system(TString("mkdir ")+outpath);

  ZHeebbPlotter * analysis = new ZHeebbPlotter("analysis",atlasInternal8TeV);
  if(!(configZHeebb(analysis,inpath,outpath))){
    cout<<"Config failed"<<endl;
    return;
  }

  plotZHeebb(analysis);
 
  gROOT->ProcessLine(".q");
}
