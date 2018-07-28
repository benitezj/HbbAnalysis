#include "Sample.h"
#include "plotRToVHTruth.C"

void runRToZHmmbbTruth(TString intag="",TString outtag=""){

  TString sampleName="mc14_13TeV.203921.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_500GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853";
  // TString sampleName="mc14_13TeV.203917.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_1000GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853";
  // TString sampleName="mc14_13TeV.203918.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_1500GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853";
  // TString sampleName="mc14_13TeV.203919.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_2000GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853";
  // TString sampleName="mc14_13TeV.203920.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_2500GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853";

  TString inpath=inputDir_+"/CxTupleSamples/ZHmmbb/"+CXTAG;
  if(intag.CompareTo("")!=0)inpath+="_"+intag;//version of the ntuples (tag at the end eg rho for CXTAG=00-07-00_rho)

  TString outpath=outputDir_+"/DC14Studies/RToZHmmbbTruth/"+CXTAG;
  if(intag.CompareTo("")!=0) outpath+="_"+intag; 
  if(outtag.CompareTo("")!=0) outpath+="_"+outtag; 
  outpath+="_"+sampleName; 
  system(TString("rm -rf ")+outpath);
  system(TString("mkdir ")+outpath);


  Sample* sample = new Sample("sample",sampleName.Data(),inpath);
  sample->addRootFiles("mc14_13TeV.203917.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_1000GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853",inpath);
  sample->addRootFiles("mc14_13TeV.203918.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_1500GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853",inpath);
  sample->addRootFiles("mc14_13TeV.203919.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_2000GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853",inpath);
  sample->addRootFiles("mc14_13TeV.203920.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_2500GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853",inpath);

  //For Resolution and Efficiency need to apply final cuts
  ////Can't call sample->skim() because that gets rid of TChain which contains the Gen histograms
  TString skim="eve_mc_w";
  skim+="*(83000<mm_m[vh_v[vh]]&&mm_m[vh_v[vh]]<99000)";
  skim+="*(met_pt<60000)";
  //skim+="*(70000<jj_m[vh_h[vh]]&&jj_m[vh_h[vh]]<150000)";
  skim+="*(mm_pt[vh_v[vh]]>(0.4*vh_mass[vh]-100000))";


  plotRToVHTruth(sample,outpath,skim);


  gROOT->ProcessLine(".q");
}
