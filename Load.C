void Load(){
  gROOT->ProcessLine(".x ./HbbAnalysis/rootlogon.C");
  gROOT->ProcessLine(".L ./HbbAnalysis/plots/Sample.C+");
  gROOT->ProcessLine(".L ./HbbAnalysis/plots/Plotter.C+");
  
}

