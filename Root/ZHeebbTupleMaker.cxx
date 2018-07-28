#include "HbbAnalysis/ZHeebbTupleMaker.h"

// this is needed to distribute the algorithm to the workers
ClassImp(ZHeebbTupleMaker)


ZHeebbTupleMaker :: ZHeebbTupleMaker ()
{
  ///Do not use this constructor
}

ZHeebbTupleMaker :: ZHeebbTupleMaker (std::string configPath) :
  ZHllbbTupleMaker(configPath),
  m_tuple(0)
{
}

EL::StatusCode ZHeebbTupleMaker :: initialize ()
{
  //this is the top level, ntuple must be defined here
  m_tuple = new ZHeebbTuple();
  ZHllbbTupleMaker::m_tuple = m_tuple;
    
  return ZHllbbTupleMaker::initialize(); 
}



EL::StatusCode ZHeebbTupleMaker :: processEEBB(){
  //Note: Muon array must be filled prior
  m_tuple->nvh=0;

  int ivh=0;
  for(int z = 0; z < m_tuple->nee ; z++){
    for(int h = 0; h < m_tuple->njj ; h++){
      if( ivh < VHTuple::MAXVH) {

	TLorentzVector zp4;
	zp4.SetPtEtaPhiM(m_tuple->ee_pt[z],m_tuple->ee_eta[z],m_tuple->ee_phi[z],m_tuple->ee_m[z]);
	TLorentzVector hp4;
	hp4.SetPtEtaPhiM(m_tuple->jj_pt[h],m_tuple->jj_eta[h],m_tuple->jj_phi[h],m_tuple->jj_m[h]);
	TLorentzVector vhp4 = zp4 + hp4;

	m_tuple->vh_charge[ivh] = m_tuple->ee_charge[z] + m_tuple->jj_charge[h];
	m_tuple->vh_m[ivh] = vhp4.M();          
	m_tuple->vh_E[ivh] = vhp4.E();
	m_tuple->vh_p[ivh] = vhp4.P();
	m_tuple->vh_pt[ivh] = vhp4.Pt(); 
	m_tuple->vh_phi[ivh] = vhp4.Phi();
	m_tuple->vh_eta[ivh] = vhp4.Eta();
	m_tuple->vh_dR[ivh] = zp4.DeltaR(hp4);
          
	m_tuple->vh_v[ivh] = z;
	m_tuple->vh_h[ivh] = h;

	m_tuple->vh_dPhiHMET[ivh]= m_tuple->jj_phi[h] - m_tuple->met_phi;
	
	TLorentzVector hp4Corr;
        hp4Corr.SetPtEtaPhiM(m_tuple->jj_pt[h] * 125000 / m_tuple->jj_m[h], m_tuple->jj_eta[h],m_tuple->jj_phi[h], 125000);
        m_tuple->vh_mass[ivh] = (zp4 + hp4Corr).M();


	++ivh;
      }else{
	Info( "processEEBB()" , " Trying to build too many ee-jj pairs, max is %i" , VHTuple::MAXVH);
      }
    }
  }
  m_tuple->nvh=ivh;
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode ZHeebbTupleMaker :: processEvent(){
  
  if( ZHllbbTupleMaker :: processEvent()  == EL::StatusCode::FAILURE) 
    return EL::StatusCode::FAILURE;
  

  //>2 Loose Leptons Veto
  if(countLooseLeptons()>2) return EL::StatusCode::FAILURE;
  incrementCounter("eventCounter_LooseLeptonsVeto");

  //Medium Electron
  int l1=-1;
  for (int i = 0; i < m_tuple->nele ; i++){
    if( !passMediumElectron(i) ) continue;
    l1=i;
    break;
  }
  if(l1==-1) return EL::StatusCode::FAILURE;
  incrementCounter("eventCounter_1MediumLepton");


  //Loose Electron
  int l2=-1;
  for (int i = 0; i < m_tuple->nele ; i++){
    if( i == l1 ) continue;
    if( !passLooseElectron(i) ) continue;
    l2=i;
    break;
  }
  if(l2==-1) return EL::StatusCode::FAILURE;
  incrementCounter("eventCounter_1LooseLepton");


  //order by pT
  if(m_tuple->ele_pt[l1] < m_tuple->ele_pt[l2]){
    int tmp=l1;
    l1 = l2;
    l2 = tmp; 
  }

  l1p4.SetPtEtaPhiM(m_tuple->ele_pt[l1],
  		    m_tuple->ele_eta[l1],
  		    m_tuple->ele_phi[l1],
  		    m_tuple->ele_m[l1]);
  l2p4.SetPtEtaPhiM(m_tuple->ele_pt[l2],
  		    m_tuple->ele_eta[l2],
  		    m_tuple->ele_phi[l2],
  		    m_tuple->ele_m[l2]);


  //Find the b-jets and fill extra jets
  if( selectJets() == EL::StatusCode::FAILURE ) 
    return EL::StatusCode::FAILURE;


  ///Create the llbb candidates
  if( processEEBB()  == EL::StatusCode::FAILURE) 
    return EL::StatusCode::FAILURE;


  //Find the selected VH : Note leptons and Jets must be pT ordered
  m_tuple->vh=-1;
  for(int i=0;i<m_tuple->nvh;i++){
    if(m_tuple->ee_leg1[m_tuple->vh_v[i]] == l1 &&
       m_tuple->ee_leg2[m_tuple->vh_v[i]] == l2 &&
       m_tuple->jj_leg1[m_tuple->vh_h[i]] == jet1 &&
       m_tuple->jj_leg2[m_tuple->vh_h[i]] == jet2 
       ) 
      m_tuple->vh=i;
  }  
  if( m_tuple->vh==-1) {
    cout<<"processEvent: something is wrong with the VH logic"<<endl; 
    return EL::StatusCode::FAILURE;
  }

  return EL::StatusCode::SUCCESS;
}

