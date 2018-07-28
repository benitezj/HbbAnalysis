#include "WHmnubbPlotter.C"
#include "configWHmnubb.C"
#include "plotWHmnubb.C"


void runWHmnubb(TString intag="",TString outtag=""){  

  gROOT->ProcessLine(".L ./HbbAnalysis/plots/WHmnubbPlotter.C+");
    
  TString inpath=inputDir_+"/CxTupleSamples/WHmnubb/"+CXTAG;
  if(intag.CompareTo("")!=0)inpath+="_"+intag;//version of the ntuples

  TString outpath=outputDir_+"/DC14Studies/WHmnubb/"+CXTAG;
  if(intag.CompareTo("")!=0)outpath+="_"+intag;
  if(outtag.CompareTo("")!=0)outpath+="_"+outtag;//version of the plots

  system(TString("rm -rf ")+outpath);
  system(TString("mkdir ")+outpath);

  WHmnubbPlotter * analysis = new WHmnubbPlotter("analysis",atlasInternal8TeV);
  if(!(configWHmnubb(analysis,inpath,outpath)))
    return;

  plotWHmnubb(analysis);
 
  gROOT->ProcessLine(".q");
}
