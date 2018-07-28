#include "HbbAnalysis/ZllTupleMaker.h"


// this is needed to distribute the algorithm to the workers
ClassImp(ZllTupleMaker)


ZllTupleMaker :: ZllTupleMaker ()
{
  ///Do not use this constructor
}

ZllTupleMaker :: ZllTupleMaker (std::string configPath) :
  RecoTupleMaker(configPath),
  m_tuple(0),
  leptonIsoOption(0)
{
  
  leptonIsoOption = config->get<int>("tuple.2LepIsolation");

}


EL::StatusCode ZllTupleMaker :: initialize ()
{
  
  if(!m_tuple){
    //tuple must be created in a fully defined TupleMaker
    cout<<"ZllTupleMaker :: initialize() : Error, m_tuple should have been defined at this point"<<endl; 
    return EL::StatusCode::FAILURE;
  }
  RecoTupleMaker::m_tuple = m_tuple;
  
  return RecoTupleMaker::initialize();
}


EL::StatusCode ZllTupleMaker :: processEvent(){
  
  //Nothing to do here

  return RecoTupleMaker :: processEvent();
}


EL::StatusCode ZllTupleMaker :: fillJets ()
{
  //Note: l1p4 and l2p4 must be filled before

  /////Central jets
  m_tuple->zll_njet=0;
  m_tuple->zll_jet=-1;
  float maxpt=0.;
  for(int i=0;i<m_tuple->njet;i++){
    if(!passCentralJet(i)) continue;
    
    TLorentzVector Jp4;
    Jp4.SetPtEtaPhiM(m_tuple->jet_pt[i],m_tuple->jet_eta[i],m_tuple->jet_phi[i],m_tuple->jet_m[i]);

    //check overlap with muons
    if(Jp4.DeltaR(l1p4)<0.4) continue;
    if(Jp4.DeltaR(l2p4)<0.4) continue;

    m_tuple->zll_njet++;
 
    if(m_tuple->jet_pt[i] > maxpt){
      m_tuple->zll_jet = i ;
      maxpt = m_tuple->jet_pt[i];
    }
  }


  /////Forward jets
  m_tuple->zll_njetfw=0;
  m_tuple->zll_jetfw=-1;
  float maxptfw=0.;
  for(int i=0;i<m_tuple->njet;i++){
    if(!passFWJet(i)) continue;
    
    TLorentzVector Jp4;
    Jp4.SetPtEtaPhiM(m_tuple->jet_pt[i],m_tuple->jet_eta[i],m_tuple->jet_phi[i],m_tuple->jet_m[i]);

    //check overlap with muons
    if(Jp4.DeltaR(l1p4)<0.4) continue;
    if(Jp4.DeltaR(l2p4)<0.4) continue;

    m_tuple->zll_njetfw++;
 
    if(m_tuple->jet_pt[i] > maxptfw){
      m_tuple->zll_jetfw = i ;
      maxptfw = m_tuple->jet_pt[i];
    }
  }



  return EL::StatusCode::SUCCESS;
}


