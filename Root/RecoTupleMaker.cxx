// packages includes
#include "HbbAnalysis/RecoTupleMaker.h"

#include "CxAODTools/ConfigStore.h"

#include "xAODMuon/Muon.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/Electron.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODJet/Jet.h"
#include "xAODJet/JetContainer.h"
#include "xAODMissingET/MissingETComponentMap.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODMissingET/MissingET.h"

ClassImp(RecoTupleMaker)

RecoTupleMaker :: RecoTupleMaker () {}
RecoTupleMaker :: ~RecoTupleMaker () {}

RecoTupleMaker :: RecoTupleMaker (std::string configPath) :
  BaseTupleMaker(configPath),
  m_tuple(0),
  m_electronsNameIn("none"),
  m_muonsNameIn("none"),
  m_jetsNameIn("none"),
  m_missingETIn("none")
{

  ConfigStore* config = ConfigStore::createStore(configPath);
  m_electronsNameIn = config->get<std::string>("tuple.ElectronsIn");
  m_muonsNameIn = config->get<std::string>("tuple.MuonsIn");
  m_jetsNameIn = config->get<std::string>("tuple.JetsIn");
  m_missingETIn  = config->get<std::string>("tuple.missingETIn");  
  delete config;  
  
}


EL::StatusCode RecoTupleMaker :: initialize ()
{

  if(!m_tuple){//tuple could have been defined upstream
    m_tuple = new RecoTuple();   
  }  
  BaseTupleMaker::m_tuple = m_tuple;
  
  return BaseTupleMaker::initialize();
}

EL::StatusCode RecoTupleMaker :: processEvent() 
{

  if( BaseTupleMaker::processEvent() == EL::StatusCode::FAILURE) 
    return EL::StatusCode::FAILURE;

  if( processRecoEventInfo() == EL::StatusCode::FAILURE) 
    return EL::StatusCode::FAILURE;
  incrementCounter("processRecoEventInfoCounter");

  if( processParticles() == EL::StatusCode::FAILURE) 
    return EL::StatusCode::FAILURE;
  incrementCounter("processParticlesCounter");
  
  // if( processRecoEventCleaning() == EL::StatusCode::FAILURE) 
  //   return EL::StatusCode::SUCCESS;
  // incrementCounter("processRecoEventCleaningCounter");


  return EL::StatusCode::SUCCESS;
}

EL::StatusCode RecoTupleMaker :: processParticles ()
{
  
  if(processElectrons() == EL::StatusCode::FAILURE) return EL::StatusCode::FAILURE;
  if(processMuons() == EL::StatusCode::FAILURE) return EL::StatusCode::FAILURE;
  if(processJets() == EL::StatusCode::FAILURE) return EL::StatusCode::FAILURE;
  if(processMET() == EL::StatusCode::FAILURE) return EL::StatusCode::FAILURE;
  if(processEE() == EL::StatusCode::FAILURE) return EL::StatusCode::FAILURE;
  if(processMM() == EL::StatusCode::FAILURE) return EL::StatusCode::FAILURE;
  if(processJJ() == EL::StatusCode::FAILURE) return EL::StatusCode::FAILURE;
  if(processMUMET() == EL::StatusCode::FAILURE) return EL::StatusCode::FAILURE;
  if(processEMET() == EL::StatusCode::FAILURE) return EL::StatusCode::FAILURE;

 
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode RecoTupleMaker :: processRecoEventInfo() 
{

  const xAOD::EventInfo * eventInfo = 0;
  if( ! m_event->retrieve( eventInfo, m_EventInfoIn.c_str()).isSuccess() ) {
    Error("execute()","Failed to retrieve event info collection. Exiting." );
    return EL::StatusCode::FAILURE;
  }
 
  m_tuple->nvtx = m_superDecorator.get(eventInfo,EventInfoIntProps::NVtx3Trks);
  m_tuple->vtx_z[0] = m_superDecorator.get(eventInfo,EventInfoFloatProps::ZPV);


  return EL::StatusCode::SUCCESS;
}


EL::StatusCode RecoTupleMaker :: processElectrons() 
{
  const xAOD::ElectronContainer * eles = 0;
  if( !m_event->retrieve( eles, m_electronsNameIn.c_str() ).isSuccess() ) {
    Error("execute", "Failed to retrieve %s contained. Exiting.", m_electronsNameIn.c_str());
    return EL::StatusCode::FAILURE;
  }
  
  m_tuple->nele=0;

  // loop over electrons
  int i = 0;
  for( xAOD::ElectronContainer::const_iterator iter = eles->begin();
       iter!= eles->end(); ++iter) {
    if( i < RecoTuple::MAXELECTRONS) {
      //m_tuple->ele_charge[i] = (*iter)->charge();
      //terminate called after throwing an instance of 'SG::ExcBadAuxVar'
      //what():  SG::ExcBadAuxVar: Attempt to retrieve nonexistent aux data item `::combinedTrackParticleLink' (107).

      m_tuple->ele_charge[i] = 0;
      m_tuple->ele_m[i] = (*iter)->m();
      m_tuple->ele_pt[i] = (*iter)->pt();
      m_tuple->ele_phi[i] = (*iter)->phi();
      m_tuple->ele_eta[i] = (*iter)->eta();
      m_tuple->ele_E[i] = (*iter)->e();
      m_tuple->ele_ptiso[i] = (*iter)->isolationValue(xAOD::Iso::ptcone20);
      m_tuple->ele_etiso[i] = (*iter)->isolationValue(xAOD::Iso::topoetcone30);
      m_tuple->ele_d0[i] = 0.;
      m_tuple->ele_z0[i] = 0.;

      m_tuple->ele_idVHl[i] = m_superDecorator.get(*iter,ElecIntProps::isVHLooseElectron); 

      ++i;
    }else{
      Info( "processElectrons()" , " Trying to build too many electrons, max is %i" , RecoTuple::MAXELECTRONS);
    }
  }
  m_tuple->nele=i;
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode RecoTupleMaker :: processMuons() 
{
  const xAOD::MuonContainer * muons = 0;
  if( !m_event->retrieve( muons, m_muonsNameIn.c_str() ).isSuccess() ) {
    Error("execute", "Failed to retrieve %s contained. Exiting.", m_muonsNameIn.c_str());
    return EL::StatusCode::FAILURE;
  }
  m_tuple->nmuo=0;
  
  // loop over muons
  int i = 0;
  for( xAOD::MuonContainer::const_iterator iter = muons->begin();
       iter!= muons->end(); ++iter) {
    if( i < RecoTuple::MAXMUONS) {
      m_tuple->muo_charge[i] = 0;//(*iter)->charge();
      m_tuple->muo_m[i] = (*iter)->m();
      m_tuple->muo_pt[i] = (*iter)->pt();
      m_tuple->muo_phi[i] = (*iter)->phi();
      m_tuple->muo_eta[i] = (*iter)->eta();
      m_tuple->muo_E[i] = (*iter)->e();
      (*iter)->isolation(m_tuple->muo_ptiso[i], xAOD::Iso::ptcone20);
      (*iter)->isolation(m_tuple->muo_etiso[i], xAOD::Iso::etcone30);
      m_tuple->muo_idVHl[i] = m_superDecorator.get(*iter, MuonIntProps::isVHLooseMuon); 
      m_tuple->muo_idZH[i] = m_superDecorator.get(*iter, MuonIntProps::isZHSignalMuon); 
      m_tuple->muo_idWH[i] = m_superDecorator.get(*iter, MuonIntProps::isWHSignalMuon); 
      //m_tuple->muo_passor[i] = m_superDecorator.get(*iter, MuonIntProps::passOR); 
      //m_tuple->muo_d0[i] = m_superDecorator.get(*iter, MuonFloatProps::d0); 
      //m_tuple->muo_z0[i] = m_superDecorator.get(*iter, MuonFloatProps::z0); 

      ++i;
    }else{
      Info( "processMuons()" , " Trying to build too many muons, max is %i" , RecoTuple::MAXMUONS);
    }
  }
  m_tuple->nmuo=i;
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode RecoTupleMaker :: processJets() 
{
  const xAOD::JetContainer * jets = 0;
  if( !m_event->retrieve( jets, m_jetsNameIn.c_str() ).isSuccess() ) {
    Error("execute", "Failed to retrieve %s contained. Exiting.", m_jetsNameIn.c_str());
    return EL::StatusCode::FAILURE;
  }
  
  m_tuple->njet=0;

  // loop over jets
  int i = 0;
  for( xAOD::JetContainer::const_iterator iter = jets->begin();
       iter!= jets->end(); ++iter) {
    if( i < RecoTuple::MAXJETS) {
      m_tuple->jet_charge[i] = 0;//currently not set
      m_tuple->jet_m[i] = (*iter)->m();
      m_tuple->jet_pt[i] = (*iter)->pt();
      m_tuple->jet_phi[i] = (*iter)->phi();
      m_tuple->jet_eta[i] = (*iter)->eta();
      m_tuple->jet_E[i] = (*iter)->e();

      (*iter)->getAttribute("jvf0",m_tuple->jet_jvf[i]);
      (*iter)->getAttribute("MV1",m_tuple->jet_mv1[i]);
      (*iter)->getAttribute("SV1_IP3D",m_tuple->jet_sv1ip3d[i]);
      (*iter)->getAttribute("MV2c00",m_tuple->jet_mv2c00[i]);
      (*iter)->getAttribute("MV2c10",m_tuple->jet_mv2c10[i]);
      (*iter)->getAttribute("MV2c20",m_tuple->jet_mv2c20[i]);
      (*iter)->getAttribute("MVb",m_tuple->jet_mvb[i]);

      (*iter)->getAttribute("goodJet",m_tuple->jet_good[i]);

      ++i;
    }else{
      Info( "processJets()" , " Trying to build too many jets, max is %i" , RecoTuple::MAXJETS);
    }
  }

  m_tuple->njet=i;
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode RecoTupleMaker :: processMET() 
{
  const xAOD::MissingETContainer* metIn = 0;
  if (!m_event->retrieve(metIn, m_missingETIn.c_str()).isSuccess()) {
    Error("execute()", "Failed to retrieve missing ET collection. Exiting.");                                                                                   
    return EL::StatusCode::FAILURE;                                                                                                                             
  }                                                          
  
  //std::cout<<(*metIn)["Final"]->met()<<std::endl;                                                                                                               
  m_tuple->met_pt = (*metIn)["Final"]->met();
  m_tuple->met_eta = 0.;
  m_tuple->met_phi = (*metIn)["Final"]->phi();
  m_tuple->met_px = (*metIn)["Final"]->mpx();
  m_tuple->met_py = (*metIn)["Final"]->mpy();
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode RecoTupleMaker :: processEE() 
{
  //Note: Muon array must be filled prior
  m_tuple->nee=0;

  int iee=0;
  for(int e1 = 0; e1 < m_tuple->nele ; e1++){
    for(int e2 = 0; e2 < m_tuple->nele ; e2++){
      if( m_tuple->ele_pt[e1] > m_tuple->ele_pt[e2] ){//remove duplicates
	if( iee < RecoTuple::MAXEE) {

	  //build the di-electron
	  TLorentzVector e1p4;
	  e1p4.SetPtEtaPhiM(m_tuple->ele_pt[e1],m_tuple->ele_eta[e1],m_tuple->ele_phi[e1],m_tuple->ele_m[e1]);
	  TLorentzVector e2p4;
	  e2p4.SetPtEtaPhiM(m_tuple->ele_pt[e2],m_tuple->ele_eta[e2],m_tuple->ele_phi[e2],m_tuple->ele_m[e2]);
	  TLorentzVector eep4=e1p4 + e2p4;

	  m_tuple->ee_charge[iee] = m_tuple->ele_charge[e1] + m_tuple->ele_charge[e2];
	  m_tuple->ee_m[iee] = eep4.M();	  
	  m_tuple->ee_E[iee] = eep4.E();
	  m_tuple->ee_p[iee] = eep4.P();
	  m_tuple->ee_pt[iee] = eep4.Pt(); 
	  m_tuple->ee_phi[iee] = eep4.Phi();
	  m_tuple->ee_eta[iee] = eep4.Eta();
	  m_tuple->ee_dR[iee] = e1p4.DeltaR(e2p4);

	  m_tuple->ee_leg1[iee] = e1;
	  m_tuple->ee_leg2[iee] = e2;

	  ++iee;
	}else{
	  Info( "processEE()" , " Trying to build too many ele pairs, max is %i" , RecoTuple::MAXEE);
	}
      }
    }
  }
  m_tuple->nee=iee;
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode RecoTupleMaker :: processMM() 
{
  //Note: Muon array must be filled prior
  m_tuple->nmm=0;

  int imm=0;
  for(int m1 = 0; m1 < m_tuple->nmuo ; m1++){
    for(int m2 = 0; m2 < m_tuple->nmuo ; m2++){
      if( m_tuple->muo_pt[m1] > m_tuple->muo_pt[m2] ){//remove duplicates
	if( imm < RecoTuple::MAXMM) {

	  //build the dimuon
	  TLorentzVector m1p4;
	  m1p4.SetPtEtaPhiM(m_tuple->muo_pt[m1],m_tuple->muo_eta[m1],m_tuple->muo_phi[m1],m_tuple->muo_m[m1]);
	  TLorentzVector m2p4;
	  m2p4.SetPtEtaPhiM(m_tuple->muo_pt[m2],m_tuple->muo_eta[m2],m_tuple->muo_phi[m2],m_tuple->muo_m[m2]);
	  TLorentzVector mmp4=m1p4 + m2p4;

	  m_tuple->mm_charge[imm] = m_tuple->muo_charge[m1] + m_tuple->muo_charge[m2];
	  m_tuple->mm_m[imm] = mmp4.M();	  
	  m_tuple->mm_E[imm] = mmp4.E();
	  m_tuple->mm_p[imm] = mmp4.P();
	  m_tuple->mm_pt[imm] = mmp4.Pt(); 
	  m_tuple->mm_phi[imm] = mmp4.Phi();
	  m_tuple->mm_eta[imm] = mmp4.Eta();
	  m_tuple->mm_dR[imm] = m1p4.DeltaR(m2p4);
	  
	  m_tuple->mm_leg1[imm] = m1;
	  m_tuple->mm_leg2[imm] = m2;

	  ++imm;
	}else{
	  Info( "processMM()" , " Trying to build too many muon pairs, max is %i" , RecoTuple::MAXMM);
	}
      }
    }
  }
  m_tuple->nmm=imm;
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode RecoTupleMaker :: processJJ() 
{

  m_tuple->njj=0;
  // loop over jets1
  int ijj = 0;
  for(int j1 = 0; j1 < m_tuple->njet ; j1++){
    for(int j2 = 0; j2 < m_tuple->njet ; j2++){
      if( m_tuple->jet_pt[j1] > 15000  //do not consider low pT jets
	  && m_tuple->jet_pt[j2] > 15000 
	  && m_tuple->jet_pt[j1] > m_tuple->jet_pt[j2]  //remove duplicates
	  ){
	if( ijj < RecoTuple::MAXJJ ) {
	  
	  //build the dijet
	  TLorentzVector j1p4;
	  j1p4.SetPtEtaPhiM(m_tuple->jet_pt[j1],m_tuple->jet_eta[j1],m_tuple->jet_phi[j1],m_tuple->jet_m[j1]);
	  TLorentzVector j2p4;
	  j2p4.SetPtEtaPhiM(m_tuple->jet_pt[j2],m_tuple->jet_eta[j2],m_tuple->jet_phi[j2],m_tuple->jet_m[j2]);
	  TLorentzVector jjp4=j1p4 + j2p4;

	  m_tuple->jj_charge[ijj] = m_tuple->jet_charge[j1] + m_tuple->jet_charge[j2];
	  m_tuple->jj_m[ijj] = jjp4.M();	  
	  m_tuple->jj_E[ijj] = jjp4.E();
	  m_tuple->jj_p[ijj] = jjp4.P();
	  m_tuple->jj_pt[ijj] = jjp4.Pt(); 
	  m_tuple->jj_phi[ijj] = jjp4.Phi();
	  m_tuple->jj_eta[ijj] = jjp4.Eta();
	  m_tuple->jj_dR[ijj] = j1p4.DeltaR(j2p4);

	  m_tuple->jj_leg1[ijj] = j1;
	  m_tuple->jj_leg2[ijj] = j2;

	  ++ijj;
	}else{
	  Info( "processJJ()" , " Trying to build too many jet pairs, max is %i" , RecoTuple::MAXJJ);
	  j1=m_tuple->njet;//break out of the loops
	  j2=m_tuple->njet;
	}
      }
    }
  }
  m_tuple->njj=ijj;
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode RecoTupleMaker :: processEMET() 
{
  //Note: Muon array must be filled prior
  m_tuple->neMet=0;

  int ieMet=0;
  for(int i = 0; i < m_tuple->nele ; i++){
    if( ieMet < RecoTuple::MAXEMET) {
      
      //build the dimuon
      TLorentzVector ep4;
      ep4.SetPtEtaPhiM(m_tuple->ele_pt[i],m_tuple->ele_eta[i],m_tuple->ele_phi[i],m_tuple->ele_m[i]);
      TLorentzVector metp4;
      metp4.SetPtEtaPhiM(m_tuple->met_pt,m_tuple->met_eta,m_tuple->met_phi,m_tuple->met_pt);
      
      TLorentzVector eMetp4=ep4 + metp4;
      
      m_tuple->eMet_charge[ieMet] = m_tuple->ele_charge[i];
      m_tuple->eMet_m[ieMet] = eMetp4.M();	  
      m_tuple->eMet_E[ieMet] = eMetp4.E();
      m_tuple->eMet_p[ieMet] = eMetp4.P();
      m_tuple->eMet_pt[ieMet] = eMetp4.Pt(); 
      m_tuple->eMet_phi[ieMet] = eMetp4.Phi();
      m_tuple->eMet_eta[ieMet] = eMetp4.Eta();
      m_tuple->eMet_mT[ieMet] = mT(ep4,metp4);
      m_tuple->eMet_ele[ieMet] = i;
	    
      ++ieMet;
    }else{
      Info( "processEMET()" , " Trying to build too many e-met pairs, max is %i" , RecoTuple::MAXEMET);
    }
  }
  m_tuple->neMet=ieMet;
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode RecoTupleMaker :: processMUMET() 
{
  //Note: Muon array must be filled prior
  m_tuple->nmuMet=0;

  int imuMet=0;
  for(int i = 0; i < m_tuple->nmuo ; i++){
    if( imuMet < RecoTuple::MAXMUMET) {
      
      //build the dimuon
      TLorentzVector mup4;
      mup4.SetPtEtaPhiM(m_tuple->muo_pt[i],m_tuple->muo_eta[i],m_tuple->muo_phi[i],m_tuple->muo_m[i]);
      TLorentzVector metp4;
      metp4.SetPtEtaPhiM(m_tuple->met_pt,m_tuple->met_eta,m_tuple->met_phi,m_tuple->met_pt);
      TLorentzVector muMetp4=mup4 + metp4;
      
      m_tuple->muMet_charge[imuMet] = m_tuple->muo_charge[i];
      m_tuple->muMet_m[imuMet] = muMetp4.M();	  
      m_tuple->muMet_E[imuMet] = muMetp4.E();
      m_tuple->muMet_p[imuMet] = muMetp4.P();
      m_tuple->muMet_pt[imuMet] = muMetp4.Pt(); 
      m_tuple->muMet_phi[imuMet] = muMetp4.Phi();
      m_tuple->muMet_eta[imuMet] = muMetp4.Eta();
      m_tuple->muMet_mT[imuMet] = mT(mup4,metp4);
      m_tuple->muMet_mu[imuMet] = i;
      
      ++imuMet;
    }else{
      Info( "processMUMET()" , " Trying to build too many mu-met pairs, max is %i" , RecoTuple::MAXMUMET);
    }
  }
  m_tuple->nmuMet=imuMet;
  return EL::StatusCode::SUCCESS;
}



/////////////////////Tools
void  RecoTupleMaker::PrintElectrons(){
  cout<<"Electrons List: "<<endl;
  for(int i = 0; i < m_tuple->nele ; i++)
    cout<<"  "<<i<<" pt: "<<m_tuple->ele_pt[i]<<"  eta: "<<m_tuple->ele_eta[i]<<"   phi: "<<m_tuple->ele_phi[i]<<endl;;
}

void  RecoTupleMaker::PrintMuons(){
  cout<<"Muons List: "<<endl;
  for(int i = 0; i < m_tuple->nmuo ; i++)
    cout<<"  "<<i<<" pt: "<<m_tuple->muo_pt[i]<<"  eta: "<<m_tuple->muo_eta[i]<<"   phi: "<<m_tuple->muo_phi[i]<<endl;;
}

void  RecoTupleMaker::PrintJets(){
  cout<<"Jets List: "<<endl;
  for(int i = 0; i < m_tuple->njet ; i++)
    cout<<"  "<<i<<" pt: "<<m_tuple->jet_pt[i]<<"  eta: "<<m_tuple->jet_eta[i]<<"   phi: "<<m_tuple->jet_phi[i]<<endl;;
}

void  RecoTupleMaker::PrintMET(){
  cout<<"MET: sumet: "<<m_tuple->met_pt<<"  phi: "<<m_tuple->met_phi<<endl;;
}
