#include "WHenubbPlotter.C"
#include "configWHenubb.C"
#include "plotWHenubb.C"

void runWHenubb(TString intag="",TString outtag=""){  

  gROOT->ProcessLine(".L ./HbbAnalysis/plots/WHenubbPlotter.C+");
    
  TString inpath=inputDir_+"/CxTupleSamples/WHenubb/"+CXTAG;
  if(intag.CompareTo("")!=0)inpath+="_"+intag;//version of the ntuples

  TString outpath=outputDir_+"/DC14Studies/WHenubb/"+CXTAG;
  if(intag.CompareTo("")!=0)outpath+="_"+intag;
  if(outtag.CompareTo("")!=0)outpath+="_"+outtag;//version of the plots

  system(TString("rm -rf ")+outpath);
  system(TString("mkdir ")+outpath);

  WHenubbPlotter * analysis = new WHenubbPlotter("analysis",atlasInternal8TeV);
  if(!(configWHenubb(analysis,inpath,outpath)))
    return;

  plotWHenubb(analysis);
 
  gROOT->ProcessLine(".q");
}
