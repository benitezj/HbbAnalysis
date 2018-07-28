#include "Sample.h"
#include "plottingTools.C"

void runCxAODDiff(TString TAG1,TString TAG2){

  //  TString sampleName="mc14_13TeV.161827.Pythia8_AU2CTEQ6L1_ZH125_llbb.merge.AOD.e3292_s1982_s2008_r5787_r5853_Test";
  TString sampleName="mc14_13TeV.203917.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_1000GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853";

  TString inpath1=inputDir_+"/CxAODSamples/"+TAG1;
  TString inpath2=inputDir_+"/CxAODSamples/"+TAG2;

  TString collection="AntiKt4LCTopoJets___NominalAuxDyn";
  //TString collection="AntiKt4LCTopoJets___OriginalAuxDyn";
  //TString collection="AntiKt4LCTopoJetsSkimAux";

  TString outpath=outputDir_+"/DC14Studies/CxAOD/TagDiff_"+sampleName+"_"+TAG1+"-"+TAG2;
  system(TString("rm -rf ")+outpath);
  system(TString("mkdir ")+outpath);

  Sample sample1("sample1",sampleName,inpath1);
  sample1.setFileName("outputLabel");
  sample1.setNtupleName("CollectionTree");

  Sample sample2("sample2",sampleName,inpath2);
  sample2.setFileName("outputLabel");
  sample2.setNtupleName("CollectionTree");


  compareSamples(&sample1,&sample2,collection+".pt/1000",50,0,100,outpath,collection+"_pt");
  compareSamples(&sample1,&sample2,collection+".eta",100,-5,5,outpath,collection+"_eta");

  gROOT->ProcessLine(".q");
}
