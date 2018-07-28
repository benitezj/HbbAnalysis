#ifndef RECOTUPLEMAKER_H
#define RECOTUPLEMAKER_H

#include "HbbAnalysis/BaseTupleMaker.h"
#include "HbbAnalysis/RecoTuple.h"

class RecoTupleMaker : public BaseTupleMaker
{
public:
  RecoTupleMaker ();//Default Do not use.
  RecoTupleMaker (std::string configPath);
  ~RecoTupleMaker ();

  virtual EL::StatusCode initialize ();
 
  // this is needed to distribute the algorithm to the workers
  ClassDef(RecoTupleMaker, 1);


protected:

  RecoTuple * m_tuple = 0; //!

  EL::StatusCode processRecoEventInfo();
  virtual EL::StatusCode processEvent();

  bool passCentralJet(int i){
    if( fabs(m_tuple->jet_eta[i]) > 2.5) return false;
    if( m_tuple->jet_pt[i] < 20000 ) return false;
    if( fabs(m_tuple->jet_eta[i]) < 2.4 
	&& m_tuple->jet_pt[i] < 50000 
	&& m_tuple->jet_jvf[i] < 0.5) return false;
    return true;
  } 
  bool passFWJet(int i){		       
    if( fabs(m_tuple->jet_eta[i]) <= 2.5 ) return false;
    if( fabs(m_tuple->jet_eta[i]) > 4.5 ) return false;
    if( m_tuple->jet_pt[i] < 30000 ) return false;
    return true;
  }
  
  void PrintElectrons();
  void PrintMuons();
  void PrintJets();
  void PrintMET();


private:

  std::string m_electronsNameIn;
  std::string m_muonsNameIn;
  std::string m_tausNameIn;
  std::string m_jetsNameIn;
  std::string m_missingETIn;

  
  EL::StatusCode processElectrons();
  EL::StatusCode processMuons();
  // EL::StatusCode processTaus();
  EL::StatusCode processJets();
  EL::StatusCode processMET();
  EL::StatusCode processEE();  
  EL::StatusCode processMM();  
  EL::StatusCode processJJ();  
  EL::StatusCode processEMET();  
  EL::StatusCode processMUMET();  
  
  EL::StatusCode processParticles();
  //bool passRecoEventCleaning();


};

#endif
