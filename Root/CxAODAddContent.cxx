#include "HbbAnalysis/CxAODAddContent.h"

#include "EventLoop/Job.h"
#include "EventLoop/OutputStream.h"
#include "EventLoop/Worker.h"

#include "xAODRootAccess/Init.h"
#include "xAODEventInfo/EventInfo.h"

#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthParticleAuxContainer.h"


#include "xAODJet/JetContainer.h"
#include "xAODJet/JetAuxContainer.h"
//#include "CxAODMaker/JetHandler.h"
//#include "JetResolution/JERTool.h"
//#include "JetResolution/JERSmearingTool.h"
//#include "JetCalibTools/JetCalibrationTool.h"
//#include "JetSelectorTools/JetCleaningTool.h"
//#include "JetUncertainties/JetUncertaintiesTool.h"
//#include "xAODBTagging/BTagging.h"

#include "CxAODTools/ConfigStore.h"
//#include "CxAODMaker/EventInfoHandler.h"
//#include "CxAODMaker/JetHandler.h"


////// For rho value computation needed with JetCalibTools-00-04-30
// need these packages
// xAODEventShape-00-00-04
// EventShapeTools-00-01-09
// EventShapeInterface-00-00-08
#include "xAODEventInfo/EventInfo.h"
#include "xAODJet/JetContainer.h"
#include "xAODEventShape/EventShape.h"
#include "JetCalibTools/JetCalibrationTool.h"
#include "JetRec/PseudoJetGetter.h"//
#include "EventShapeTools/EventDensityTool.h"//


ClassImp(CxAODAddContent)

CxAODAddContent :: CxAODAddContent (){}

CxAODAddContent :: CxAODAddContent (std::string m_configPath) :
  m_config(0),
  m_event(0)
  // m_eventInfoHandler(0),
  //  m_jetHandler(0)
{

  m_config = ConfigStore::createStore(m_configPath,false);
  if ( ! m_config ) {
    Error("initialize()","Couldn't create ConfigStore from file : %s",m_configPath.c_str());
    exit(0);
  }

  
  std::cout<<"CxAODAddContent was created"<<std::endl;
}

CxAODAddContent :: ~CxAODAddContent (){}


EL::StatusCode CxAODAddContent :: setupJob (EL::Job& job)
{
  ////Commented lines needed only in case running this module standalone
  //EL::OutputStream out ("outputLabel");
  //job.outputAdd (out);
  

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode CxAODAddContent :: histInitialize ()
{
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode CxAODAddContent :: initialize ()
{
  m_event = wk()->xaodEvent();


  // m_eventInfoHandler = new EventInfoHandler(*m_config, m_event);
  // if (m_eventInfoHandler->initialize() != EL::StatusCode::SUCCESS) {
  //   Error("initialize()", "Failed to initialize tools in EventInfoHandler!");
  //   return EL::StatusCode::FAILURE;
  // }
  // //m_eventInfoHandler->executeEvent();


  // std::string name="jet";
  // std::string containerName;
  // m_config->getif<std::string>(name + "Container", containerName);
  // if( containerName.empty() ) {
  //   Warning("registerHandler()", ("Container for handler '" + name +
  //           "' not defined! Handler not registered.").c_str());
  //   return EL::StatusCode::FAILURE;
  // }
  // m_jetHandler = new JetHandler(name, *m_config, m_event, *m_eventInfoHandler);

  

  //******************************************
  edtool = new EventDensityTool("Kt4LCDensityTool");
  edtool->setProperty("JetAlgorithm", "Kt");
  edtool->setProperty("JetRadius", 0.4);
  edtool->setProperty("AbsRapidityMin", 0.0);
  edtool->setProperty("AbsRapidityMax", 2.0);
  edtool->setProperty("AreaDefinition", "Voronoi");
  edtool->setProperty("VoronoiRfact", 0.9);
  edtool->setProperty("OutputContainer", "Kt4LCTopoEventShape");
  //edtool->msg().setLevel( MSG::DEBUG );

  lcgetter = new PseudoJetGetter("lcget");
  lcgetter->setProperty("InputContainer", "CaloCalTopoCluster");
  lcgetter->setProperty("OutputContainer", "PseudoJetLCTopo");
  lcgetter->setProperty("Label","LCTopo");
  lcgetter->setProperty("SkipNegativeEnergy", true);
  lcgetter->setProperty("GhostScale", 0.0);
  lcgetter->initialize();

  asg::ToolStore::put(lcgetter);
  ToolHandle<IPseudoJetGetter> hlcget(lcgetter);  
  edtool->setProperty("JetInput", hlcget);

  edtool->initialize();
  //******************************************



  //TFile *file = wk()->getOutputFile ("outputLabel");
  //m_event->writeTo(file);
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode CxAODAddContent::fileExecute(){
   
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode CxAODAddContent::changeInput(bool firstFile){

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode CxAODAddContent :: execute ()
{

  // calculate event density, fill the EventShape object and put it in the data store.
  edtool->fillEventShape();

  if( fillTruthParticles() == EL::StatusCode::FAILURE ) return EL::StatusCode::FAILURE;
  if( fillJets()           == EL::StatusCode::FAILURE ) return EL::StatusCode::FAILURE;
  

  //m_event->fill(); //Do not call fill(), called by AnalysisBase (CxAODMaker)
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode CxAODAddContent :: postExecute ()
{

  ///Part of the rho computation
  xAOD::TActiveStore::store()->clear();

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode CxAODAddContent :: finalize ()
{  
  

  //TFile *file = wk()->getOutputFile ("outputLabel");
  //m_event->finishWritingTo( file );
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode CxAODAddContent :: histFinalize ()
{
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode CxAODAddContent :: fillTruthParticles(){

  /////////////////////
  //This copies the full container
  /////////////////////
  //m_event->copy("TruthParticle");

  /////////////////////////
  ///Copy selected particles
  /////////////////////////
  const xAOD::TruthParticleContainer * Input = 0;
  if( !m_event->retrieve( Input,"TruthParticle" ).isSuccess() ) {
    Error("fillTruthParticles", "Failed to retrieve %s contained. Exiting.", "TruthParticle");
    return EL::StatusCode::FAILURE;
  }

  ///https://twiki.cern.ch/twiki/bin/viewauth/AtlasComputing/SoftwareTutorialxAODAnalysisInROOT#Deep_copy
  xAOD::TruthParticleContainer* Output = new xAOD::TruthParticleContainer();
  xAOD::TruthParticleAuxContainer* OutputAux = new xAOD::TruthParticleAuxContainer();
  Output->setStore( OutputAux ); 
  if( ! m_event->record( Output, "TruthParticleSkim" ) ) { return EL::StatusCode::FAILURE; }
  if( ! m_event->record( OutputAux, "TruthParticleSkimAux." ) ) { return EL::StatusCode::FAILURE; } 
  for( xAOD::TruthParticleContainer::const_iterator itr = Input->begin();
       itr != Input->end(); 
       ++itr ) {

    int status=(*itr)->status();
    int pdgid=abs((*itr)->pdgId());
    
    if(status == 1 ) continue; 

    bool select=0;
    if(pdgid == 23 || pdgid == 24 || pdgid == 25) select=1; //Z, W, h

    if(pdgid == 11 || pdgid == 13 || pdgid == 15) select=1; //prompt e,mu,tau 
    if(pdgid == 12 || pdgid == 14 || pdgid == 16) select=1; //prompt neutrinos
    if(pdgid == 4 || pdgid == 5 || pdgid == 6) select=1; //prompt c,b,t

    if(pdgid == 32 || pdgid == 33 || pdgid == 34) select=1; //Z',Z'',W'
    if(pdgid == 35 || pdgid == 36 || pdgid == 37) select=1; //H2,H3,H+


    if(pdgid == 9000001 ) select=1; //ZH Resonance




    if(!select) continue;

    xAOD::TruthParticle* part = new xAOD::TruthParticle();
    part->makePrivateStore( **itr );
    Output->push_back( part );
  }

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode CxAODAddContent :: fillJets(){

  std::string collection = "AntiKt4LCTopoJets";

  const xAOD::JetContainer * Input = 0;
  if( !m_event->retrieve( Input, collection ).isSuccess() ) {
    Error("fillJets", "Failed to retrieve %s contained. Exiting.", collection.c_str() );
    return EL::StatusCode::FAILURE;
  }


  xAOD::JetContainer* Output = new xAOD::JetContainer();
  xAOD::JetAuxContainer* OutputAux = new xAOD::JetAuxContainer();
  Output->setStore( OutputAux ); 
  if( ! m_event->record( Output, collection+"Skim" ) ) { return EL::StatusCode::FAILURE; }
  if( ! m_event->record( OutputAux, collection+"SkimAux." ) ) { return EL::StatusCode::FAILURE; } 
  for( xAOD::JetContainer::const_iterator itr = Input->begin();
       itr != Input->end(); 
       ++itr ) {
    xAOD::Jet* part = new xAOD::Jet();
    part->makePrivateStore( **itr );
    Output->push_back( part );
  }

  return EL::StatusCode::SUCCESS;
}


