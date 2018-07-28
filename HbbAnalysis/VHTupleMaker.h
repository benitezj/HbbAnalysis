#ifndef VHTUPLEMAKER_H
#define VHTUPLEMAKER_H

#include "HbbAnalysis/RecoTupleMaker.h"
#include "HbbAnalysis/VHTuple.h"

class VHTupleMaker : public RecoTupleMaker
{
public:
  VHTupleMaker ();//Default Do not use.
  VHTupleMaker (std::string configPath);

  virtual EL::StatusCode initialize ();
  
  // this is needed to distribute the algorithm to the workers
  ClassDef(VHTupleMaker, 1);

protected:
 
  VHTuple * m_tuple = 0 ; //!
  int jet1; //signal jets pT ordered 
  int jet2; //


  virtual EL::StatusCode processEvent();



  bool passLooseMuon(int idx,bool iso=1);
  bool passMediumMuon(int idx,bool iso=1);
  bool passTightMuon(int idx,bool iso=1);

  bool passLooseElectron(int idx,bool iso=1);
  bool passMediumElectron(int idx,bool iso=1);
  bool passTightElectron(int idx,bool iso=1);

  int countLooseLeptons();

  virtual bool jetOverlap(int jetindex) = 0; //to be defined in higher class

  EL::StatusCode  selectJets () ;

private:

  std::vector<int> fillCentralJets(); 
  void fillCentralJetsVeto(); 
  void fillFWJets();
  void fillBJets(); 

  bool passCentralJetVH(int i){
    if(!passCentralJet(i)) return false;
    if( m_tuple->jet_pt[i] < 30000 ) return false;
    return true;
  } 
  
};

#endif
