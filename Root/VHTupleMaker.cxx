#include "HbbAnalysis/VHTupleMaker.h"

// this is needed to distribute the algorithm to the workers
ClassImp(VHTupleMaker)


VHTupleMaker :: VHTupleMaker ()
{
  ///Do not use this constructor
}

VHTupleMaker :: VHTupleMaker (std::string configPath) :
  RecoTupleMaker(configPath),
  m_tuple(0),
  jet1(-1),
  jet2(-1)
{
}

EL::StatusCode VHTupleMaker :: initialize ()
{
  if(!m_tuple){
    //tuple must be created in a fully defined TupleMaker
    cout<<"VHTupleMaker :: initialize() : Error, m_tuple should have been defined at this point"<<endl; 
    return EL::StatusCode::FAILURE;
  }
  RecoTupleMaker::m_tuple = m_tuple;
  
  return RecoTupleMaker::initialize();
}


EL::StatusCode VHTupleMaker :: processEvent(){

  return RecoTupleMaker :: processEvent();
}


void VHTupleMaker :: fillFWJets ()
{
  m_tuple->vh_njetfw=0;
  m_tuple->vh_jetfw=-1;
  float maxptfw=0.;
  for(int i=0;i<m_tuple->njet;i++){
    if(!passFWJet(i)) continue;
    m_tuple->vh_njetfw++;
    if(m_tuple->jet_pt[i] > maxptfw){
      m_tuple->vh_jetfw = i ;
      maxptfw = m_tuple->jet_pt[i];
    }
  }
}



bool VHTupleMaker :: passLooseMuon(int idx, bool iso){
  if( m_tuple->muo_idVHl[idx] == false ) return false;
  if( m_tuple->muo_pt[idx] < 7000 ) return false;
  if( fabs(m_tuple->muo_eta[idx]) > 2.7  ) return false;
  if( iso==1 && m_tuple->muo_ptiso[idx]/m_tuple->muo_pt[idx] > 0.1  ) return false;  
  return true;
}

bool VHTupleMaker :: passMediumMuon(int idx, bool iso){
  if( passLooseMuon(idx,iso) == false ) return false;
  if( m_tuple->muo_pt[idx] < 25000 ) return false;
  if( fabs(m_tuple->muo_eta[idx]) > 2.5  ) return false;
  return true;
}

bool VHTupleMaker :: passTightMuon(int idx, bool iso){
  if( passMediumMuon(idx,iso) == false ) return false;
  if( m_tuple->muo_ptiso[idx]/m_tuple->muo_pt[idx] > 0.04  ) return false;  
  if( m_tuple->muo_etiso[idx]/m_tuple->muo_pt[idx] > 0.04 )return false;
  //missing q/p selection missing ??
  return true;
}


bool VHTupleMaker :: passLooseElectron(int idx, bool iso){
  if( m_tuple->ele_idVHl[idx] == false ) return false;
  if( m_tuple->ele_pt[idx] < 7000 ) return false;
  if( fabs(m_tuple->ele_eta[idx]) > 2.47  ) return false;
  if( iso==1 && m_tuple->ele_ptiso[idx]/m_tuple->ele_pt[idx] > 0.1  ) return false;  
  //Missing OQ selection ??
  return true;
}

bool VHTupleMaker :: passMediumElectron(int idx, bool iso){
  if( passLooseElectron(idx,iso) == false ) return false;
  if( m_tuple->ele_pt[idx] < 25000 ) return false;
  return true;
}

bool VHTupleMaker :: passTightElectron(int idx, bool iso){
  if( passMediumElectron(idx,iso) == false ) return false;
  if( iso==1 && m_tuple->ele_ptiso[idx]/m_tuple->ele_pt[idx] > 0.04  ) return false;  
  if( iso==1 && m_tuple->ele_etiso[idx]/m_tuple->ele_pt[idx] > 0.04 )return false;
  return true;
}


int VHTupleMaker :: countLooseLeptons(){
  int N=0;
  for (int i = 0; i < m_tuple->nmuo ; i++){
    if( !passLooseMuon(i) ) continue;
    N++;
  }
  for (int i = 0; i < m_tuple->nele ; i++){
    if( !passLooseElectron(i) ) continue;
    N++;
  }

  return N;
}


void VHTupleMaker :: fillCentralJetsVeto()
{
  m_tuple->vh_njetveto=0;
  for(int i=0;i<m_tuple->njet;i++){
    if(!passCentralJet(i)) continue;
    if(this->jetOverlap(i)) continue;
    m_tuple->vh_njetveto++;
  }
}


std::vector<int>  VHTupleMaker :: fillCentralJets ()
{
  std::vector<int> list;
  m_tuple->vh_njet=0;
  m_tuple->vh_jet1=-1;
  float maxpt=0.;
  for(int i=0;i<m_tuple->njet;i++){
    if(!passCentralJetVH(i)) continue;
    if(this->jetOverlap(i)) continue;
    m_tuple->vh_njet++;
    list.push_back(i);

    if(m_tuple->jet_pt[i] > maxpt){
      m_tuple->vh_jet1 = i ;
      maxpt = m_tuple->jet_pt[i];
    }

  }

  // if(m_tuple->vh_njet == 3) //check the pT ordering
  //   cout<<"j1="<<m_tuple->jet_pt[m_tuple->vh_jet1]
  // 	<<", j2="<<m_tuple->jet_pt[m_tuple->vh_jet2]
  // 	<<", j3="<<m_tuple->jet_pt[m_tuple->vh_jet3]<<endl;
  

  return list;
}


void VHTupleMaker :: fillBJets ()
{
  m_tuple->vh_nbjet=0;
  m_tuple->vh_bjet1=-1;
  m_tuple->vh_bjet2=-1;
  for(int i=0;i<m_tuple->njet;i++){
    if(!passCentralJetVH(i)) continue;
    if(this->jetOverlap(i)) continue;
    if(m_tuple->jet_sv1ip3d[i] < 0.) continue; ////!!! Fix
    m_tuple->vh_nbjet++;
    if(m_tuple->vh_bjet1<0) m_tuple->vh_bjet1  = i ;
    else m_tuple->vh_bjet2 = i ;
  }

  //must be pT ordered for later
  if(m_tuple->vh_bjet2>0 && 
     m_tuple->jet_pt[m_tuple->vh_bjet2] > m_tuple->jet_pt[ m_tuple->vh_bjet1] )
    {
      int tmp= m_tuple->vh_bjet1;
      m_tuple->vh_bjet1 = m_tuple->vh_bjet2 ;
      m_tuple->vh_bjet2 = tmp;
    }
  
}

EL::StatusCode  VHTupleMaker :: selectJets ()
{
  
  ////////////////////////////////////
  ////Define the Forward Jets for veto
  ///////////////////////////////////
  fillFWJets();  
  
  
  // //Veto events with forward jets
  // if( m_tuple->vh_njetfw > 0) return EL::StatusCode::FAILURE;
  // incrementCounter("eventCounter_FWJetVeto");
  // This cut is not applied for 2-lep channel

  ////////////////////////
  ///Define the Central Jets for Veto
  ////////////////////////
  fillCentralJetsVeto();

  // //remove events with > 3 central Jets
  // if( m_tuple->vh_njetveto > 3 ) return EL::StatusCode::FAILURE;
  // incrementCounter("eventCounter_More3CentralJets");
  // This cut is not applied for 2-lep channel
  

  /////////////////////////
  ///Define the Central Jets
  // these have a different pT requirement
  ////////////////////////
  std::vector<int> centralJetList=fillCentralJets();

  //remove events with < 1 central Jets //Just to check single Jet efficiency
  if( m_tuple->vh_njet < 1 ) return EL::StatusCode::FAILURE;
  incrementCounter("eventCounter_AtLeast1CentralJet");

  //remove events with < 2 central Jets
  if( m_tuple->vh_njet < 2 ) return EL::StatusCode::FAILURE;
  incrementCounter("eventCounter_AtLeast2CentralJets");

  //pT cut on first Jet (jets are pT ordered)
  if( m_tuple->jet_pt[m_tuple->vh_jet1] < 45000 ) return EL::StatusCode::FAILURE;
  incrementCounter("eventCounter_NoHighPtJet");

  
  /////////////////////
  ///Apply b-tagging 
  ////////////////////
  fillBJets();

  //remove events with no b-Jets
  if( m_tuple->vh_nbjet == 0 ) return EL::StatusCode::FAILURE;
  incrementCounter("eventCounter_0BJets");

  //remove events with > 2 b-Jets
  if( m_tuple->vh_nbjet > 2 ) return EL::StatusCode::FAILURE;
  incrementCounter("eventCounter_More2BJets");

  ////////////////////////
  //identify the two signal jets 
  //////////////////////
  jet1=-1;
  jet2=-1;
  if( m_tuple->vh_njet  == 2 ){
    jet1 = centralJetList[0];
    jet2 = centralJetList[1];
  }else if( m_tuple->vh_nbjet == 2 ){    
    jet1 = m_tuple->vh_bjet1;
    jet2 = m_tuple->vh_bjet2; 
  } else if( m_tuple->vh_njet  > 2 && m_tuple->vh_nbjet == 1 ){
    ///loop over central jets and find the highest pT which is not jet1
    ///Note this list already has central jet requirement
    jet1 = m_tuple->vh_bjet1;
    float maxpt=0;
    for (std::vector<int>::iterator it = centralJetList.begin() ; it != centralJetList.end(); ++it){
      if((*it)!=jet1 && m_tuple->jet_pt[*it] > maxpt){
	jet2 = *it ;
	maxpt = m_tuple->jet_pt[*it];
      }
    }        
  }
  if(jet1==-1 || jet2==-1){
    cout<<"selectJets() : Something is wrong with the b-jets logic"<<endl;
    exit(0);
  }
  
  //must be pT ordered for later
  if(m_tuple->jet_pt[jet2] > m_tuple->jet_pt[jet1] ){
    int tmp=jet1;
    jet1 = jet2;
    jet2 = tmp;
  }


  return EL::StatusCode::SUCCESS;
}




  // if( m_tuple->vh_njet  == 2 ){
  //   jet1 = list[0];
  //   jet2 = list[1];
  // }else if( m_tuple->vh_njet  == 3 && m_tuple->vh_nbjet == 1 ){
  //   jet1 = m_tuple->vh_bjet1;
  //   float maxpt=0;
  //   for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
  //     if((*it)!=jet1 && m_tuple->jet_pt[*it] > maxpt){
  // 	jet2 = *it ;
  // 	maxpt = m_tuple->jet_pt[*it];
  //     }
  //   }        
  // }else if( m_tuple->vh_njet  == 3 && m_tuple->vh_nbjet == 2 ){    
  //   jet1 = m_tuple->vh_bjet1;
  //   jet2 = m_tuple->vh_bjet2; 
  // }

