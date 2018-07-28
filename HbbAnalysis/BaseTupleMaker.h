#ifndef BASETUPLEMAKER_H
#define BASETUPLEMAKER_H

// ROOT includes
#include <TSystem.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TLorentzVector.h>

// Event Loop includes
#include "EventLoop/Algorithm.h"
#include "EventLoop/StatusCode.h"
#include "xAODRootAccess/TEvent.h"


#ifndef __MAKECINT__
#include "CxAODTools/SuperDecorator.h"
#include "CxAODTools/IndexDecorator.h"
#endif // not __MAKECINT__

#include "CxAODTools/ConfigStore.h"

#include "HbbAnalysis/BaseTuple.h"

class BaseTupleMaker : public EL::Algorithm
{
public:
  BaseTupleMaker ();//Default Do not use.
  BaseTupleMaker (std::string configPath);
  virtual ~BaseTupleMaker();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  
  // this is needed to distribute the algorithm to the workers
  ClassDef(BaseTupleMaker, 1);


protected:
  ConfigStore* config = 0;

  BaseTuple * m_tuple = 0; //!
 
  xAOD::TEvent * m_event; //!
  TTree * m_tree; //!
  std::string m_filename; // output filename 

  std::string m_EventInfoIn;
  EL::StatusCode processBaseEventInfo();

  virtual EL::StatusCode processEvent();

  void incrementCounter(const char * name, float w=1.);
  float getCounter(const char * name);

  void printMCTruth();

  double deltaR(float meta, float mphi, float peta, float pphi) {
    double deta= fabs(meta - peta), dphi= fabs(mphi - pphi);
    if (dphi > TMath::Pi() ) dphi = 2*(TMath::Pi()) - dphi;
    return sqrt((dphi*dphi)+(deta*deta));
  }
  double mT(TLorentzVector l1, TLorentzVector l2) {
    return sqrt( pow(l1.Pt() + l2.Pt(), 2) -
		 pow(l1.Px() + l2.Px(), 2) -
		 pow(l1.Py() + l2.Py(), 2) );
  }



#ifndef __MAKECINT__
  SuperDecorator m_superDecorator; //!
  IndexDecorator m_indexDecorator; //!
#endif // not __MAKECINT__


private:

    
  std::vector<string> counterNames;
  std::vector<float> counters;
  void printCounters();

  //event counts 
  TH1D* HEventCounts; //!

  //Pileup histos
  TH1F* HPileUp; //!

  std::vector<std::string> pileUpDataFiles;
  std::vector<std::string> pileUpMCFiles;
  TH1F* PileUpRatios[BaseTuple::MAXMCPUWEIGHTS]; //!
  EL::StatusCode initPileUpWeights(TFile * f);
  EL::StatusCode fillPileUpWeights();

  ///Generator info
  std::string m_MCTruthIn;
  EL::StatusCode processMCTruth();
  void fillTruthParticle(int index, TLorentzVector P, int status, int pdg);
  void fillMCProcesses();
  
  TH1F* HGen_Zmm_m; //!
  TH1F* HGen_Zmm_pt; //!
  TH1F* HGen_Zmm_eta; //!
  TH1F* HGen_Zmm_m1_pt; //!
  TH1F* HGen_Zmm_m1_eta; //!
  TH1F* HGen_Zmm_m2_pt; //!
  TH1F* HGen_Zmm_m2_eta; //!

  TH1F* HGen_Zee_m; //!
  TH1F* HGen_Zee_pt; //!
  TH1F* HGen_Zee_eta; //!
  TH1F* HGen_Zee_e1_pt; //!
  TH1F* HGen_Zee_e1_eta; //!
  TH1F* HGen_Zee_e2_pt; //!
  TH1F* HGen_Zee_e2_eta; //!

  TH1F* HGen_Wmv_m; //!
  TH1F* HGen_Wmv_pt; //!
  TH1F* HGen_Wmv_eta; //!
  TH1F* HGen_Wmv_m_pt; //!
  TH1F* HGen_Wmv_m_eta; //!
  TH1F* HGen_Wmv_v_pt; //!
  TH1F* HGen_Wmv_v_eta; //!

  TH1F* HGen_Wev_m; //!
  TH1F* HGen_Wev_pt; //!
  TH1F* HGen_Wev_eta; //!
  TH1F* HGen_Wev_e_pt; //!
  TH1F* HGen_Wev_e_eta; //!
  TH1F* HGen_Wev_v_pt; //!
  TH1F* HGen_Wev_v_eta; //!

  TH1F* HGen_H0bb_m; //!
  TH1F* HGen_H0bb_pt; //!
  TH1F* HGen_H0bb_eta; //!
  TH1F* HGen_H0bb_b1_pt; //!
  TH1F* HGen_H0bb_b1_eta; //!
  TH1F* HGen_H0bb_b2_pt; //!
  TH1F* HGen_H0bb_b2_eta; //!

  TH1F* HGen_ZH_m; //!
  TH1F* HGen_ZH_pt; //!
  TH1F* HGen_ZH_eta; //!

  TH1F* HGen_WH_m; //!
  TH1F* HGen_WH_pt; //!
  TH1F* HGen_WH_eta; //!


  ///VH Resonance analysis
  TH1F* HGen_RToVH_m; //!
  TH1F* HGen_RToVH_pt; //!
  TH1F* HGen_RToVH_eta; //!

  TH1F* HGen_RToVH_V_m; //!
  TH1F* HGen_RToVH_V_pt; //!
  TH1F* HGen_RToVH_V_eta; //!

  TH1F* HGen_RToVH_H_m; //!
  TH1F* HGen_RToVH_H_pt; //!
  TH1F* HGen_RToVH_H_eta; //!

  TH1F* HGen_RToVH_H_b1_m; //!
  TH1F* HGen_RToVH_H_b1_pt; //!
  TH1F* HGen_RToVH_H_b1_eta; //!

  TH1F* HGen_RToVH_H_b2_m; //!
  TH1F* HGen_RToVH_H_b2_pt; //!
  TH1F* HGen_RToVH_H_b2_eta; //!

  TH1F* HGen_RToVH_H_p; //!
  TH1F* HGen_RToVH_H_dR; //!
  TH2F* HGen_RToVH_H_dRVsp; //!

  EL::StatusCode bookGenHistograms(TFile *f);
  void fillGenHistograms();

  
};

#endif
