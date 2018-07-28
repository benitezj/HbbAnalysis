#include "HbbAnalysis/BaseTupleMaker.h"

#include "EventLoop/Job.h"
#include "EventLoop/OutputStream.h"
#include "EventLoop/Worker.h"

#include "xAODRootAccess/Init.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODTruth/TruthParticleContainer.h"


ClassImp(BaseTupleMaker)

BaseTupleMaker :: BaseTupleMaker (){}
BaseTupleMaker :: ~BaseTupleMaker (){}

BaseTupleMaker :: BaseTupleMaker (std::string configPath) :
  config(ConfigStore::createStore(configPath)),
  m_tuple(0),
  m_event(0),
  m_tree(0),
  m_filename("none"),
  m_EventInfoIn("none"),
  m_superDecorator(),
  m_MCTruthIn("none")
{

  m_filename = config->get<std::string>("tuple.Label");
  m_EventInfoIn = config->get<std::string>("tuple.EventInfo");
  m_MCTruthIn = config->get<std::string>("tuple.MCTruth");
    
  cout<<"BaseTupleMaker was created"<<endl;
}


EL::StatusCode BaseTupleMaker :: setupJob (EL::Job& job)
{
 
  job.useXAOD();
  xAOD::Init( "BaseTupleMaker" ).ignore();
  
  EL::OutputStream out(m_filename);
  job.outputAdd(out);
  
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode BaseTupleMaker :: histInitialize ()
{
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode BaseTupleMaker :: initialize ()
{
  m_event = wk()->xaodEvent();
  Info("initialize()","Number of events = %lli", m_event->getEntries() );


  TFile * f = wk()->getOutputFile(m_filename);
  if(!f) { 
    Error( "initialize()" , "Failed to get output file");
    return EL::StatusCode::FAILURE;
  }


  ////Define the ntuple content
  ////tuple could have been defined upstream  
  if(! m_tuple) 
    m_tuple = new BaseTuple();
  m_tree = new TTree("tuple","tuple");
  if(!m_tuple || !m_tree) { 
    Error( "initialize()" , "Failed to make m_tree or m_tuple");
    return EL::StatusCode::FAILURE;
  }
  m_tree->SetDirectory(f);
  m_tuple->DefineBranches(m_tree);
  Info("initialize()","Branches defined");

  
  ///////Init MC Pile-up weights
  if( initPileUpWeights(f) == EL::StatusCode::FAILURE ){
    Error( "initialize()" , "Failed to initialize the pile-up weights");
    return EL::StatusCode::FAILURE;
  }


  ////Save the history of the sum of event weights
  cout<<"Clonning MetaData_EventCount from: "<<wk()->inputFile()->GetName()<<endl;
  TH1D* HEventCountsIn = dynamic_cast<TH1D*>(wk()->inputFile()->Get("MetaData_EventCount"));
  if (!HEventCountsIn) {
    Error("initialize()", "MetaData_EventCount not found");
    return EL::StatusCode::FAILURE;
  }
  HEventCounts=(TH1D*)(HEventCountsIn->Clone("MetaData_EventCount"));
  //HEventCounts->Reset(); //do not reset to start adding first file here
  HEventCounts->SetDirectory(f);
  

  if(bookGenHistograms(f) == EL::StatusCode::FAILURE ){
    Error( "initialize()" , "Failed to book Generator histograms");
    return EL::StatusCode::FAILURE;
  }

  
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode BaseTupleMaker::fileExecute(){
   
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode BaseTupleMaker::changeInput(bool firstFile){
  cout<<"Processing: "<<wk()->inputFile()->GetName()<<endl;
  
  //Add the sum of the event weights
  if(!firstFile){//HEventCounts does not exist for first file
    TH1D* HEventCountsIn = dynamic_cast<TH1D*>(wk()->inputFile()->Get("MetaData_EventCount"));
    if(!HEventCountsIn){
      Error("initialize()", "MetaData_EventCount not found");
      return EL::StatusCode::FAILURE;
    }
    HEventCounts->Add(HEventCountsIn);
  }
  
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode BaseTupleMaker :: execute ()
{

  if( int(getCounter("inputCounter")) % 100 == 0) 
    cout<<"Event number = "<<getCounter("inputCounter")
	<<" ,  selected events = "<<getCounter("outputCounter")
	<<endl;
  incrementCounter("inputCounter");
  
  
  if(this->processEvent() == EL::StatusCode::FAILURE) 
    return EL::StatusCode::SUCCESS; 


  incrementCounter("outputCounter");
  incrementCounter("outputCounterSumW",m_tuple->eve_mc_w);
  m_tree->Fill();
  return EL::StatusCode::SUCCESS;
}


///////////////////////////

EL::StatusCode BaseTupleMaker :: processEvent() 
{
  if( processBaseEventInfo() == EL::StatusCode::FAILURE) 
    return EL::StatusCode::FAILURE;
  incrementCounter("processBaseEventInfoCounter");
  incrementCounter("processBaseEventInfoCounterSumW",m_tuple->eve_mc_w);  //mc_w must be filled 
  

  if( m_tuple->eve_isMC && processMCTruth() == EL::StatusCode::FAILURE) 
    return EL::StatusCode::FAILURE;
  incrementCounter("processMCTruthCounter");


  // if( processBaseEventCleaning() == EL::StatusCode::FAILURE) 
  //   return EL::StatusCode::SUCCESS;
  // incrementCounter("processBaseEventCleaningCounter");


  return EL::StatusCode::SUCCESS;
}

EL::StatusCode BaseTupleMaker :: processBaseEventInfo() 
{

  ///Fill Event Level info
  const xAOD::EventInfo * eventInfo = 0;
  if( ! m_event->retrieve( eventInfo, m_EventInfoIn.c_str()).isSuccess() ) {
    Error("execute()","Failed to retrieve event info collection. Exiting." );
    return EL::StatusCode::FAILURE;
  }

  m_tuple->eve_num = eventInfo->eventNumber();
  m_tuple->eve_run = eventInfo->runNumber();
  m_tuple->eve_mu = eventInfo->averageInteractionsPerCrossing();

  ///pile-up distribution
  HPileUp->Fill(m_tuple->eve_mu);

  ///MC quantities
  m_tuple->eve_mc_w = 1.0;
  m_tuple->eve_mc_num = 0;
  m_tuple->eve_mc_chan = 0;
  m_tuple->eve_isMC = m_superDecorator.get(eventInfo,EventInfoIntProps::isMC);

  if(m_tuple->eve_isMC){
    m_tuple->eve_mc_w = m_superDecorator.get(eventInfo,EventInfoFloatProps::MCEventWeight);
    m_tuple->eve_mc_num = eventInfo->mcEventNumber();
    m_tuple->eve_mc_chan = eventInfo->mcChannelNumber();

  }

  //pile-up weights, for data will just be set to 1.
  if( fillPileUpWeights() == EL::StatusCode::FAILURE ) return EL::StatusCode::FAILURE;  
  incrementCounter("fillPileUpWeightsCounter");

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode  BaseTupleMaker :: fillPileUpWeights(){
  //init the weights
  for(int i=0;i<m_tuple->nmcpuw;i++)
    m_tuple->eve_mc_puw[i] = 1.0;

  if(m_tuple->eve_isMC){
    //pu weight
    //m_Pileup->apply(eventInfo); // produces a decoration in Eventinfo
    //m_tuple->eve_mc_puw = eventInfo->auxdata< double >( "PileupWeight" );

    for(int i=0;i<m_tuple->nmcpuw;i++){

      if(!PileUpRatios[i]) return EL::StatusCode::FAILURE;
      int mubin= 1 + int(m_tuple->eve_mu);
      if(mubin<1 || mubin>PileUpRatios[i]->GetNbinsX())
	return EL::StatusCode::FAILURE;

      m_tuple->eve_mc_puw[i] = PileUpRatios[i]->GetBinContent(mubin);
    }    
  }

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode BaseTupleMaker :: processMCTruth() {
  if(! m_tuple->eve_isMC){
    cout<<" Calling processMCTruth() for Data. "<<endl;
    return EL::StatusCode::FAILURE;
  }
  
  //printMCTruth();
  
  const xAOD::TruthParticleContainer* Truth = 0;
  if( ! m_event->retrieve( Truth , m_MCTruthIn.c_str() ).isSuccess() ){
    Error("execute()", "Failed to retrieve  TruthParticle collection. Exiting." );
    return EL::StatusCode::FAILURE;
  }

  m_tuple->ntruth = 0;
  for (unsigned int i = 0 ; i < Truth->size(); ++i) {
    if(i == BaseTuple::MAXTRUTH){
      cout<<"processMCTruth(): number of truth particles is at max "<<BaseTuple::MAXTRUTH<<endl;
      break;
    }
    const xAOD::TruthParticle* part = Truth->at(i);
    
    fillTruthParticle(i,part->p4(),part->status(),part->pdgId());

    // m_tuple->truth_m[i]= part->p4().M();
    // m_tuple->truth_p[i]= part->p4().P();
    // m_tuple->truth_pt[i]= part->p4().Pt();
    // if(m_tuple->truth_pt[i] > 0. ) m_tuple->truth_eta[i]= part->p4().Eta();
    // else m_tuple->truth_eta[i] = -9999;
    // m_tuple->truth_phi[i]= part->p4().Phi();
    // m_tuple->truth_status[i]= part->status();
    // m_tuple->truth_pdg[i]= part->pdgId();

    m_tuple->ntruth++;    
  }  


  fillMCProcesses();
  fillGenHistograms();
 

  return EL::StatusCode::SUCCESS;
}


void BaseTupleMaker :: fillTruthParticle(int index, TLorentzVector P, int status, int pdg){
  m_tuple->truth_m[index]= P.M();
  m_tuple->truth_p[index]= P.P();
  m_tuple->truth_pt[index]= P.Pt();
  if(m_tuple->truth_pt[index] > 1 ) m_tuple->truth_eta[index]= P.Eta();
    else m_tuple->truth_eta[index] = -9999;
  m_tuple->truth_phi[index]= P.Phi();
  m_tuple->truth_status[index]= status;
  m_tuple->truth_pdg[index]= pdg;
}


void BaseTupleMaker :: fillMCProcesses(){
  if(! m_tuple->eve_isMC){
    cout<<" Calling fillMCProcesses() for Data. "<<endl;
    return;
  }

  
  ////////////////////////
  //Find Z-->mm
  ///////////////////////
  m_tuple->truth_Zmm=-1;
  m_tuple->truth_Zmm_m1=-1;
  m_tuple->truth_Zmm_m2=-1;

  ///First loop in case the Z is not stored (Sherpa samples)
  for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
    for (int l2 = 0 ; l2 < m_tuple->ntruth; ++l2)
      if(m_tuple->truth_status[l1]==3 && m_tuple->truth_pdg[l1] == -13 //mu+
	 && m_tuple->truth_status[l2]==3  && m_tuple->truth_pdg[l2] == 13 //m-
	 ){
	if(m_tuple->truth_pt[l1] > m_tuple->truth_pt[l2]){
	  m_tuple->truth_Zmm_m1=l1;
	  m_tuple->truth_Zmm_m2=l2;
	}else{
	  m_tuple->truth_Zmm_m1=l2;
	  m_tuple->truth_Zmm_m2=l1;
	}	
      }


  for (int i = 0 ; i < m_tuple->ntruth; ++i) 
    if(m_tuple->truth_status[i]==62 && m_tuple->truth_pdg[i]==23){
      m_tuple->truth_Zmm=i;//Fill the Z index here, the leptons are not always there
      
      //for each Z check if the leptons are there, Note only the last Z will be saved
      for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
	for (int l2 = 0 ; l2 < m_tuple->ntruth; ++l2)
	  if(m_tuple->truth_status[l1]==3 && m_tuple->truth_pdg[l1] == -13 //mu+
	     && m_tuple->truth_status[l2]==3  && m_tuple->truth_pdg[l2] == 13 //m-
	     ){
	    TLorentzVector l1P4;
	    l1P4.SetPtEtaPhiM(m_tuple->truth_pt[l1],m_tuple->truth_eta[l1],m_tuple->truth_phi[l1],m_tuple->truth_m[l1]);
	    TLorentzVector l2P4;
	    l2P4.SetPtEtaPhiM(m_tuple->truth_pt[l2],m_tuple->truth_eta[l2],m_tuple->truth_phi[l2],m_tuple->truth_m[l2]);
	    if( fabs( m_tuple->truth_pt[i] - (l1P4+l2P4).Pt() ) < 1e-2 ){
	      //order by pt
	      if(m_tuple->truth_pt[l1] > m_tuple->truth_pt[l2]){
		m_tuple->truth_Zmm_m1=l1;
		m_tuple->truth_Zmm_m2=l2;
	      }else{
		m_tuple->truth_Zmm_m1=l2;
		m_tuple->truth_Zmm_m2=l1;
	      }	
	      
	    }
	  }
    }


  ///////////////////////
  //Find Z-->ee
  ///////////////////////
  m_tuple->truth_Zee=-1;
  m_tuple->truth_Zee_e1=-1;
  m_tuple->truth_Zee_e2=-1;
    
  ///First loop in case the Z is not stored (Sherpa samples)
  for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
    for (int l2 = 0 ; l2 < m_tuple->ntruth; ++l2)
      if(m_tuple->truth_status[l1]==3 && m_tuple->truth_pdg[l1] == -11
	 && m_tuple->truth_status[l2]==3  && m_tuple->truth_pdg[l2] == 11
	 ){
	if(m_tuple->truth_pt[l1] > m_tuple->truth_pt[l2]){
	  m_tuple->truth_Zee_e1=l1;
	  m_tuple->truth_Zee_e2=l2;
	}else{
	  m_tuple->truth_Zee_e1=l2;
	  m_tuple->truth_Zee_e2=l1;
	}	
      }

  for (int i = 0 ; i < m_tuple->ntruth; ++i) 
    if(m_tuple->truth_status[i]==62 && m_tuple->truth_pdg[i]==23){
      m_tuple->truth_Zee=i;//Fill the Z index here, the leptons are not always there
      
      //for each Z found check if the leptons are there
      for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
	for (int l2 = 0 ; l2 < m_tuple->ntruth; ++l2)
	  if(m_tuple->truth_status[l1]==3 && m_tuple->truth_pdg[l1] == -11 
	     && m_tuple->truth_status[l2]==3  && m_tuple->truth_pdg[l2] == 11 
	     ){
	    TLorentzVector l1P4;
	    l1P4.SetPtEtaPhiM(m_tuple->truth_pt[l1],m_tuple->truth_eta[l1],m_tuple->truth_phi[l1],m_tuple->truth_m[l1]);
	    TLorentzVector l2P4;
	    l2P4.SetPtEtaPhiM(m_tuple->truth_pt[l2],m_tuple->truth_eta[l2],m_tuple->truth_phi[l2],m_tuple->truth_m[l2]);
	    if( fabs( m_tuple->truth_pt[i] - (l1P4+l2P4).Pt() ) < 1e-2 ){
	      if(m_tuple->truth_pt[l1] > m_tuple->truth_pt[l2]){
		m_tuple->truth_Zee_e1=l1;
		m_tuple->truth_Zee_e2=l2; 
	      }else{
		m_tuple->truth_Zee_e1=l2;
		m_tuple->truth_Zee_e2=l1;
	      }	
	    }

	  }
    }


  ///////////////////////
  //Find W->mu nu
  ///////////////////////
  m_tuple->truth_Wmv=-1;
  m_tuple->truth_Wmv_m=-1;
  m_tuple->truth_Wmv_v=-1;

  ///First loop in case the W is not stored (Sherpa samples)
  for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
    if(m_tuple->truth_status[l1]==3 && abs(m_tuple->truth_pdg[l1]) == 13)
      m_tuple->truth_Wmv_m=l1;
  for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
    if(m_tuple->truth_status[l1]==3 && abs(m_tuple->truth_pdg[l1]) == 14)
      m_tuple->truth_Wmv_v=l1;
 
  ///This loop requires the W, will overwrite the above
  for (int i = 0 ; i < m_tuple->ntruth; ++i)
    if(m_tuple->truth_status[i]==62 && abs(m_tuple->truth_pdg[i])==24 ){
      m_tuple->truth_Wmv=i;//Fill the Z index here, the leptons are not always there
      for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
	for (int l2 = 0 ; l2 < m_tuple->ntruth; ++l2)
	  if(m_tuple->truth_status[l1]==3 && abs(m_tuple->truth_pdg[l1]) == 13 
	     && m_tuple->truth_status[l2]==3  && abs(m_tuple->truth_pdg[l2]) == 14
	     ){
	    TLorentzVector l1P4;
	    l1P4.SetPtEtaPhiM(m_tuple->truth_pt[l1],m_tuple->truth_eta[l1],m_tuple->truth_phi[l1],m_tuple->truth_m[l1]);
	    TLorentzVector l2P4;
	    l2P4.SetPtEtaPhiM(m_tuple->truth_pt[l2],m_tuple->truth_eta[l2],m_tuple->truth_phi[l2],m_tuple->truth_m[l2]);
	    if( fabs( m_tuple->truth_pt[i] - (l1P4+l2P4).Pt() ) < 1e-2 ){
	      m_tuple->truth_Wmv_m=l1;
	      m_tuple->truth_Wmv_v=l2;
	    }

	  }
    }  


  ///////////////////////
  //Find W->e nu
  ///////////////////////
  m_tuple->truth_Wev=-1;
  m_tuple->truth_Wev_e=-1;
  m_tuple->truth_Wev_v=-1;

  ///First loop in case the W is not stored (Sherpa samples)
  for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
    if(m_tuple->truth_status[l1]==3 && abs(m_tuple->truth_pdg[l1]) == 11)
      m_tuple->truth_Wev_e=l1;
  for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
    if(m_tuple->truth_status[l1]==3 && abs(m_tuple->truth_pdg[l1]) == 12)
      m_tuple->truth_Wev_v=l1;
 
  ///This loop requires the W, will overwrite the above
  for (int i = 0 ; i < m_tuple->ntruth; ++i)
    if(m_tuple->truth_status[i]==62 && abs(m_tuple->truth_pdg[i])==24 ){
      m_tuple->truth_Wev=i;//Fill the Z index here, the leptons are not always there
      for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
	for (int l2 = 0 ; l2 < m_tuple->ntruth; ++l2)
	  if(m_tuple->truth_status[l1]==3 && abs(m_tuple->truth_pdg[l1]) == 11 
	     && m_tuple->truth_status[l2]==3  && abs(m_tuple->truth_pdg[l2]) == 12
	     ){
	    TLorentzVector l1P4;
	    l1P4.SetPtEtaPhiM(m_tuple->truth_pt[l1],m_tuple->truth_eta[l1],m_tuple->truth_phi[l1],m_tuple->truth_m[l1]);
	    TLorentzVector l2P4;
	    l2P4.SetPtEtaPhiM(m_tuple->truth_pt[l2],m_tuple->truth_eta[l2],m_tuple->truth_phi[l2],m_tuple->truth_m[l2]);
	    if( fabs( m_tuple->truth_pt[i] - (l1P4+l2P4).Pt() ) < 1e-2 ){
	      m_tuple->truth_Wev_e=l1;
	      m_tuple->truth_Wev_v=l2; 
	    }

	  }
    }  


  ////////////////////////
  //Find H->bb
  ///////////////////////
  m_tuple->truth_H0bb=-1;
  m_tuple->truth_H0bb_b1=-1;
  m_tuple->truth_H0bb_b2=-1;

  ///First loop in case the Z is not stored (Sherpa samples)
  for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
    for (int l2 = 0 ; l2 < m_tuple->ntruth; ++l2)
      if(m_tuple->truth_status[l1]==3 && m_tuple->truth_pdg[l1] == 5 //b
	 && m_tuple->truth_status[l2]==3  && m_tuple->truth_pdg[l2] == -5 //b-bar
	 ){
	if(m_tuple->truth_pt[l1] > m_tuple->truth_pt[l2]){
	  m_tuple->truth_H0bb_b1=l1;
	  m_tuple->truth_H0bb_b2=l2;
	}else{
	  m_tuple->truth_H0bb_b1=l2;
	  m_tuple->truth_H0bb_b2=l1;
	}	
      }


  for (int i = 0 ; i < m_tuple->ntruth; ++i) 
    if(m_tuple->truth_status[i]==62 && m_tuple->truth_pdg[i]==25){
      m_tuple->truth_H0bb=i;//Fill the index here, the daughters are not always there
      
      //for each Z found check if the leptons are there
      for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
	for (int l2 = 0 ; l2 < m_tuple->ntruth; ++l2)
	  if(m_tuple->truth_status[l1]==3 && m_tuple->truth_pdg[l1] == 5 //b
	     && m_tuple->truth_status[l2]==3  && m_tuple->truth_pdg[l2] == -5 //b-bar
	     ){
	    TLorentzVector l1P4;
	    l1P4.SetPtEtaPhiM(m_tuple->truth_pt[l1],m_tuple->truth_eta[l1],m_tuple->truth_phi[l1],m_tuple->truth_m[l1]);
	    TLorentzVector l2P4;
	    l2P4.SetPtEtaPhiM(m_tuple->truth_pt[l2],m_tuple->truth_eta[l2],m_tuple->truth_phi[l2],m_tuple->truth_m[l2]);
	    if( fabs( m_tuple->truth_pt[i] - (l1P4+l2P4).Pt() ) < 1e-2 ){
	      //order by pt
	      if(m_tuple->truth_pt[l1] > m_tuple->truth_pt[l2]){
		m_tuple->truth_H0bb_b1=l1;
		m_tuple->truth_H0bb_b2=l2;
	      }else{
		m_tuple->truth_H0bb_b1=l2;
		m_tuple->truth_H0bb_b2=l1;
	      }	
	      
	    }
	  }
    }
  


  //VH composites: V and H must be in the truth list (does not work for Sherpa samples)
  if(m_tuple->truth_Zmm>-1 && m_tuple->truth_H0bb>-1){
    if( m_tuple->ntruth == BaseTuple::MAXTRUTH){
      cout<<"fillMCProcesses(): number of truth particles is at max "<<BaseTuple::MAXTRUTH<<endl;
      return;
    }
    TLorentzVector P1;
    P1.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Zmm],m_tuple->truth_eta[m_tuple->truth_Zmm],
		    m_tuple->truth_phi[m_tuple->truth_Zmm],m_tuple->truth_m[m_tuple->truth_Zmm]);
    TLorentzVector P2;
    P2.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_H0bb],m_tuple->truth_eta[m_tuple->truth_H0bb],
		    m_tuple->truth_phi[m_tuple->truth_H0bb],m_tuple->truth_m[m_tuple->truth_H0bb]);
    fillTruthParticle(m_tuple->ntruth,P1+P2,-1,131355);//use this coding pdg=[muon][muon][b][b]
    m_tuple->truth_ZHmmbb=m_tuple->ntruth;
    m_tuple->ntruth++;
  }

  if(m_tuple->truth_Zee>-1 && m_tuple->truth_H0bb>-1){
    if( m_tuple->ntruth == BaseTuple::MAXTRUTH){
      cout<<"fillMCProcesses(): number of truth particles is at max "<<BaseTuple::MAXTRUTH<<endl;
      return;
    }
    TLorentzVector P1;
    P1.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Zee],m_tuple->truth_eta[m_tuple->truth_Zee],
		    m_tuple->truth_phi[m_tuple->truth_Zee],m_tuple->truth_m[m_tuple->truth_Zee]);
    TLorentzVector P2;
    P2.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_H0bb],m_tuple->truth_eta[m_tuple->truth_H0bb],
		    m_tuple->truth_phi[m_tuple->truth_H0bb],m_tuple->truth_m[m_tuple->truth_H0bb]);
    fillTruthParticle(m_tuple->ntruth,P1+P2,-1,111155);
    m_tuple->truth_ZHeebb=m_tuple->ntruth;
    m_tuple->ntruth++;
  }

  if(m_tuple->truth_Wmv>-1 && m_tuple->truth_H0bb>-1){
    if( m_tuple->ntruth == BaseTuple::MAXTRUTH){
      cout<<"fillMCProcesses(): number of truth particles is at max "<<BaseTuple::MAXTRUTH<<endl;
      return;
    }
    TLorentzVector P1;
    P1.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Wmv],m_tuple->truth_eta[m_tuple->truth_Wmv],
		    m_tuple->truth_phi[m_tuple->truth_Wmv],m_tuple->truth_m[m_tuple->truth_Wmv]);
    TLorentzVector P2;
    P2.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_H0bb],m_tuple->truth_eta[m_tuple->truth_H0bb],
		    m_tuple->truth_phi[m_tuple->truth_H0bb],m_tuple->truth_m[m_tuple->truth_H0bb]);
    fillTruthParticle(m_tuple->ntruth,P1+P2,-1,131455);//use this coding pdg=[muon][muon][b][b]
    m_tuple->truth_WHmvbb=m_tuple->ntruth;
    m_tuple->ntruth++;
  }

  if(m_tuple->truth_Wev>-1 && m_tuple->truth_H0bb>-1){
    if( m_tuple->ntruth == BaseTuple::MAXTRUTH){
      cout<<"fillMCProcesses(): number of truth particles is at max "<<BaseTuple::MAXTRUTH<<endl;
      return;
    }
    TLorentzVector P1;
    P1.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Wev],m_tuple->truth_eta[m_tuple->truth_Wev],
		    m_tuple->truth_phi[m_tuple->truth_Wev],m_tuple->truth_m[m_tuple->truth_Wev]);
    TLorentzVector P2;
    P2.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_H0bb],m_tuple->truth_eta[m_tuple->truth_H0bb],
		    m_tuple->truth_phi[m_tuple->truth_H0bb],m_tuple->truth_m[m_tuple->truth_H0bb]);
    fillTruthParticle(m_tuple->ntruth,P1+P2,-1,111255);
    m_tuple->truth_WHevbb=m_tuple->ntruth;
    m_tuple->ntruth++;
  }




  ////////////////////////
  //Find R->VH (V=Z/W)
  ///////////////////////
  m_tuple->truth_RToVH=-1;
  m_tuple->truth_RToVH_V=-1;
  m_tuple->truth_RToVH_H=-1;
  m_tuple->truth_RToVH_H_b1=-1;
  m_tuple->truth_RToVH_H_b2=-1;
  
  for (int i = 0 ; i < m_tuple->ntruth; ++i){
    if(m_tuple->truth_status[i]==62 && abs(m_tuple->truth_pdg[i])==9000001)
      m_tuple->truth_RToVH=i;
 
    if(m_tuple->truth_status[i]==22 && ( abs(m_tuple->truth_pdg[i])==23 ||  abs(m_tuple->truth_pdg[i])==24) )
      m_tuple->truth_RToVH_V=i;
 
    if(m_tuple->truth_status[i]==22 && abs(m_tuple->truth_pdg[i])==25)
      m_tuple->truth_RToVH_H=i;
 
  }
  //pT order the b's
  for (int l1 = 0 ; l1 < m_tuple->ntruth; ++l1)
    for (int l2 = 0 ; l2 < m_tuple->ntruth; ++l2)
      if(m_tuple->truth_status[l1]==23 && m_tuple->truth_pdg[l1] == 5 //b
	 && m_tuple->truth_status[l2]==23  && m_tuple->truth_pdg[l2] == -5 //b-bar
	 ){
	if(m_tuple->truth_pt[l1] > m_tuple->truth_pt[l2]){
	  m_tuple->truth_RToVH_H_b1=l1;
	  m_tuple->truth_RToVH_H_b2=l2;
	}else{
	  m_tuple->truth_RToVH_H_b1=l2;
	  m_tuple->truth_RToVH_H_b2=l1;
	}	
      }
  
  if(m_tuple->truth_RToVH_H_b1>-1 && m_tuple->truth_RToVH_H_b2>-1)
    m_tuple->truth_RToVH_H_dR = deltaR(m_tuple->truth_eta[m_tuple->truth_RToVH_H_b1],m_tuple->truth_phi[m_tuple->truth_RToVH_H_b1],
				       m_tuple->truth_eta[m_tuple->truth_RToVH_H_b2],m_tuple->truth_phi[m_tuple->truth_RToVH_H_b2]);



  ////Leave this for later
  // m_tuple->truth_top=-1;
  // m_tuple->truth_top_mm_m1=-1;
  // m_tuple->truth_top_mm_m2=-1;
  // m_tuple->truth_top_ee_e1=-1;
  // m_tuple->truth_top_ee_e2=-1;
  // m_tuple->truth_top_em_e=-1;
  // m_tuple->truth_top_em_m=-1;

}


EL::StatusCode BaseTupleMaker :: bookGenHistograms(TFile *f ){

  ///NOTE: should set Sumw2() otherwise cannot use bin errors later

  HGen_Zmm_m = new TH1F("HGen_Zmm_m","HGen_Zmm_m",1000,0,1000);//in GeV
  HGen_Zmm_pt= new TH1F("HGen_Zmm_pt","HGen_Zmm_pt",1000,0,1000);
  HGen_Zmm_eta = new TH1F("HGen_Zmm_eta","HGen_Zmm_eta",200,-10,10);
  HGen_Zmm_m1_pt = new TH1F("HGen_Zmm_m1_pt","HGen_Zmm_m1_pt",1000,0,1000);
  HGen_Zmm_m1_eta = new TH1F("HGen_Zmm_m1_eta","HGen_Zmm_m1_eta",200,-10,10);
  HGen_Zmm_m2_pt = new TH1F("HGen_Zmm_m2_pt","HGen_Zmm_m2_pt",1000,0,1000);
  HGen_Zmm_m2_eta = new TH1F("HGen_Zmm_m2_eta","HGen_Zmm_m2_eta",200,-10,10);
  HGen_Zmm_m->SetDirectory(f);
  HGen_Zmm_pt->SetDirectory(f);
  HGen_Zmm_eta->SetDirectory(f);
  HGen_Zmm_m1_pt->SetDirectory(f);
  HGen_Zmm_m1_eta->SetDirectory(f);
  HGen_Zmm_m2_pt->SetDirectory(f);
  HGen_Zmm_m2_eta->SetDirectory(f);

  HGen_Zee_m = new TH1F("HGen_Zee_m","HGen_Zee_m",1000,0,1000);//in GeV
  HGen_Zee_pt= new TH1F("HGen_Zee_pt","HGen_Zee_pt",1000,0,1000);
  HGen_Zee_eta = new TH1F("HGen_Zee_eta","HGen_Zee_eta",200,-10,10);
  HGen_Zee_e1_pt = new TH1F("HGen_Zee_e1_pt","HGen_Zee_e1_pt",1000,0,1000);
  HGen_Zee_e1_eta = new TH1F("HGen_Zee_e1_eta","HGen_Zee_e1_eta",200,-10,10);
  HGen_Zee_e2_pt = new TH1F("HGen_Zee_e2_pt","HGen_Zee_e2_pt",1000,0,1000);
  HGen_Zee_e2_eta = new TH1F("HGen_Zee_e2_eta","HGen_Zee_e2_eta",200,-10,10);
  HGen_Zee_m->SetDirectory(f);
  HGen_Zee_pt->SetDirectory(f);
  HGen_Zee_eta->SetDirectory(f);
  HGen_Zee_e1_pt->SetDirectory(f);
  HGen_Zee_e1_eta->SetDirectory(f);
  HGen_Zee_e2_pt->SetDirectory(f);
  HGen_Zee_e2_eta->SetDirectory(f);


  HGen_Wmv_m = new TH1F("HGen_Wmv_m","HGen_Wmv_m",1000,0,1000);//in GeV
  HGen_Wmv_pt= new TH1F("HGen_Wmv_pt","HGen_Wmv_pt",1000,0,1000);
  HGen_Wmv_eta = new TH1F("HGen_Wmv_eta","HGen_Wmv_eta",200,-10,10);
  HGen_Wmv_m_pt = new TH1F("HGen_Wmv_m_pt","HGen_Wmv_m_pt",1000,0,1000);
  HGen_Wmv_m_eta = new TH1F("HGen_Wmv_m_eta","HGen_Wmv_m_eta",200,-10,10);
  HGen_Wmv_v_pt = new TH1F("HGen_Wmv_v_pt","HGen_Wmv_v_pt",1000,0,1000);
  HGen_Wmv_v_eta = new TH1F("HGen_Wmv_v_eta","HGen_Wmv_v_eta",200,-10,10);
  HGen_Wmv_m->SetDirectory(f);
  HGen_Wmv_pt->SetDirectory(f);
  HGen_Wmv_eta->SetDirectory(f);
  HGen_Wmv_m_pt->SetDirectory(f);
  HGen_Wmv_m_eta->SetDirectory(f);
  HGen_Wmv_v_pt->SetDirectory(f);
  HGen_Wmv_v_eta->SetDirectory(f);

  HGen_Wev_m = new TH1F("HGen_Wev_m","HGen_Wev_m",1000,0,1000);//in GeV
  HGen_Wev_pt= new TH1F("HGen_Wev_pt","HGen_Wev_pt",1000,0,1000);
  HGen_Wev_eta = new TH1F("HGen_Wev_eta","HGen_Wev_eta",200,-10,10);
  HGen_Wev_e_pt = new TH1F("HGen_Wev_e_pt","HGen_Wev_e_pt",1000,0,1000);
  HGen_Wev_e_eta = new TH1F("HGen_Wev_e_eta","HGen_Wev_e_eta",200,-10,10);
  HGen_Wev_v_pt = new TH1F("HGen_Wev_v_pt","HGen_Wev_v_pt",1000,0,1000);
  HGen_Wev_v_eta = new TH1F("HGen_Wev_v_eta","HGen_Wev_v_eta",200,-10,10);
  HGen_Wev_m->SetDirectory(f);
  HGen_Wev_pt->SetDirectory(f);
  HGen_Wev_eta->SetDirectory(f);
  HGen_Wev_e_pt->SetDirectory(f);
  HGen_Wev_e_eta->SetDirectory(f);
  HGen_Wev_v_pt->SetDirectory(f);
  HGen_Wev_v_eta->SetDirectory(f);

  HGen_H0bb_m = new TH1F("HGen_H0bb_m","HGen_H0bb_m",1000,0,1000);//in GeV
  HGen_H0bb_pt= new TH1F("HGen_H0bb_pt","HGen_H0bb_pt",1000,0,1000);
  HGen_H0bb_eta = new TH1F("HGen_H0bb_eta","HGen_H0bb_eta",200,-10,10);
  HGen_H0bb_b1_pt = new TH1F("HGen_H0bb_b1_pt","HGen_H0bb_b1_pt",1000,0,1000);
  HGen_H0bb_b1_eta = new TH1F("HGen_H0bb_b1_eta","HGen_H0bb_b1_eta",200,-10,10);
  HGen_H0bb_b2_pt = new TH1F("HGen_H0bb_b2_pt","HGen_H0bb_b2_pt",1000,0,1000);
  HGen_H0bb_b2_eta = new TH1F("HGen_H0bb_b2_eta","HGen_H0bb_b2_eta",200,-10,10);
  HGen_H0bb_m->SetDirectory(f);
  HGen_H0bb_pt->SetDirectory(f);
  HGen_H0bb_eta->SetDirectory(f);
  HGen_H0bb_b1_pt->SetDirectory(f);
  HGen_H0bb_b1_eta->SetDirectory(f);
  HGen_H0bb_b2_pt->SetDirectory(f);
  HGen_H0bb_b2_eta->SetDirectory(f);


  ///These will be filled with either ZH-->mmbb or ZH-->eebb (assume only one is created per event)
  HGen_ZH_m = new TH1F("HGen_ZH_m","HGen_ZH_m",1000,0,10000);//in GeV
  HGen_ZH_pt= new TH1F("HGen_ZH_pt","HGen_ZH_pt",1000,0,1000);
  HGen_ZH_eta = new TH1F("HGen_ZH_eta","HGen_ZH_eta",200,-10,10);
  HGen_ZH_m->SetDirectory(f);
  HGen_ZH_pt->SetDirectory(f);
  HGen_ZH_eta->SetDirectory(f);

  HGen_WH_m = new TH1F("HGen_WH_m","HGen_WH_m",1000,0,10000);//in GeV
  HGen_WH_pt= new TH1F("HGen_WH_pt","HGen_WH_pt",1000,0,1000);
  HGen_WH_eta = new TH1F("HGen_WH_eta","HGen_WH_eta",200,-10,10);
  HGen_WH_m->SetDirectory(f);
  HGen_WH_pt->SetDirectory(f);
  HGen_WH_eta->SetDirectory(f);


  //VH Resonance analysis
  HGen_RToVH_m = new TH1F("HGen_RToVH_m","HGen_RToVH_m",1000,0,10000);//in 10 GeV
  HGen_RToVH_pt= new TH1F("HGen_RToVH_pt","HGen_RToVH_pt",1000,0,1000);
  HGen_RToVH_eta = new TH1F("HGen_RToVH_eta","HGen_RToVH_eta",200,-10,10);
  HGen_RToVH_m->SetDirectory(f);
  HGen_RToVH_pt->SetDirectory(f);
  HGen_RToVH_eta->SetDirectory(f);

  HGen_RToVH_V_m = new TH1F("HGen_RToVH_V_m","HGen_RToVH_V_m",1000,0,1000);//in GeV
  HGen_RToVH_V_pt= new TH1F("HGen_RToVH_V_pt","HGen_RToVH_V_pt",1000,0,1000);
  HGen_RToVH_V_eta = new TH1F("HGen_RToVH_V_eta","HGen_RToVH_V_eta",200,-10,10);
  HGen_RToVH_V_m->SetDirectory(f);
  HGen_RToVH_V_pt->SetDirectory(f);
  HGen_RToVH_V_eta->SetDirectory(f);

  HGen_RToVH_H_m = new TH1F("HGen_RToVH_H_m","HGen_RToVH_H_m",1000,0,1000);//in GeV
  HGen_RToVH_H_pt= new TH1F("HGen_RToVH_H_pt","HGen_RToVH_H_pt",1000,0,1000);
  HGen_RToVH_H_eta = new TH1F("HGen_RToVH_H_eta","HGen_RToVH_H_eta",200,-10,10);
  HGen_RToVH_H_m->SetDirectory(f);
  HGen_RToVH_H_pt->SetDirectory(f);
  HGen_RToVH_H_eta->SetDirectory(f);

  HGen_RToVH_H_b1_m = new TH1F("HGen_RToVH_H_b1_m","HGen_RToVH_H_b1_m",1000,0,1000);//in GeV
  HGen_RToVH_H_b1_pt= new TH1F("HGen_RToVH_H_b1_pt","HGen_RToVH_H_b1_pt",1000,0,1000);
  HGen_RToVH_H_b1_eta = new TH1F("HGen_RToVH_H_b1_eta","HGen_RToVH_H_b1_eta",200,-10,10);
  HGen_RToVH_H_b1_m->SetDirectory(f);
  HGen_RToVH_H_b1_pt->SetDirectory(f);
  HGen_RToVH_H_b1_eta->SetDirectory(f);

  HGen_RToVH_H_b2_m = new TH1F("HGen_RToVH_H_b2_m","HGen_RToVH_H_b2_m",1000,0,1000);//in GeV
  HGen_RToVH_H_b2_pt= new TH1F("HGen_RToVH_H_b2_pt","HGen_RToVH_H_b2_pt",1000,0,1000);
  HGen_RToVH_H_b2_eta = new TH1F("HGen_RToVH_H_b2_eta","HGen_RToVH_H_b2_eta",200,-10,10);
  HGen_RToVH_H_b2_m->SetDirectory(f);
  HGen_RToVH_H_b2_pt->SetDirectory(f);
  HGen_RToVH_H_b2_eta->SetDirectory(f);

  HGen_RToVH_H_p= new TH1F("HGen_RToVH_H_p","HGen_RToVH_H_p",1000,0,10000);
  HGen_RToVH_H_dR= new TH1F("HGen_RToVH_H_dR","HGen_RToVH_H_dR",100,0,10);
  HGen_RToVH_H_dRVsp= new TH2F("HGen_RToVH_H_dRVsp","HGen_RToVH_H_dRVsp",1000,0,10000,100,0,10);
  HGen_RToVH_H_p->SetDirectory(f);
  HGen_RToVH_H_dR->SetDirectory(f);
  HGen_RToVH_H_dRVsp->SetDirectory(f);



  return EL::StatusCode::SUCCESS;
}

void BaseTupleMaker :: fillGenHistograms(){
  if(! m_tuple->eve_isMC){
    cout<<" Calling fillGenHistograms() for Data. "<<endl;
    return;
  }

  if(m_tuple->truth_Zmm>-1) HGen_Zmm_m->Fill(m_tuple->truth_m[m_tuple->truth_Zmm]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Zmm>-1) HGen_Zmm_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Zmm]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Zmm>-1) HGen_Zmm_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Zmm],m_tuple->eve_mc_w);
  if(m_tuple->truth_Zmm_m1>-1) HGen_Zmm_m1_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Zmm_m1]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Zmm_m1>-1) HGen_Zmm_m1_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Zmm_m1],m_tuple->eve_mc_w);
  if(m_tuple->truth_Zmm_m2>-1) HGen_Zmm_m2_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Zmm_m2]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Zmm_m2>-1) HGen_Zmm_m2_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Zmm_m2],m_tuple->eve_mc_w);

  //for sherpa samples need to calculate the parent quantities from the decay products
  if(m_tuple->truth_Zmm == -1 && m_tuple->truth_Zmm_m1>-1 && m_tuple->truth_Zmm_m2>-1 ){
    TLorentzVector L1; 
    L1.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Zmm_m1],
		    m_tuple->truth_eta[m_tuple->truth_Zmm_m1],
		    m_tuple->truth_phi[m_tuple->truth_Zmm_m1],
		    m_tuple->truth_m[m_tuple->truth_Zmm_m1]);

    TLorentzVector L2; 
    L2.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Zmm_m2],
		    m_tuple->truth_eta[m_tuple->truth_Zmm_m2],
		    m_tuple->truth_phi[m_tuple->truth_Zmm_m2],
		    m_tuple->truth_m[m_tuple->truth_Zmm_m2]);
    
    HGen_Zmm_m->Fill((L1+L2).M()/1000,m_tuple->eve_mc_w);
    HGen_Zmm_pt->Fill((L1+L2).Pt()/1000,m_tuple->eve_mc_w);
    if((L1+L2).Pt()>1.)
      HGen_Zmm_eta->Fill((L1+L2).Eta(),m_tuple->eve_mc_w);
    else HGen_Zmm_eta->Fill(-999,m_tuple->eve_mc_w);
  }



  if(m_tuple->truth_Zee>-1) HGen_Zee_m->Fill(m_tuple->truth_m[m_tuple->truth_Zee]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Zee>-1) HGen_Zee_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Zee]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Zee>-1) HGen_Zee_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Zee],m_tuple->eve_mc_w);
  if(m_tuple->truth_Zee_e1>-1) HGen_Zee_e1_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Zee_e1]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Zee_e1>-1) HGen_Zee_e1_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Zee_e1],m_tuple->eve_mc_w);
  if(m_tuple->truth_Zee_e2>-1) HGen_Zee_e2_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Zee_e2]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Zee_e2>-1) HGen_Zee_e2_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Zee_e2],m_tuple->eve_mc_w);

  if(m_tuple->truth_Zee == -1 && m_tuple->truth_Zee_e1>-1 && m_tuple->truth_Zee_e2>-1 ){
    TLorentzVector L1; 
    L1.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Zee_e1],
		    m_tuple->truth_eta[m_tuple->truth_Zee_e1],
		    m_tuple->truth_phi[m_tuple->truth_Zee_e1],
		    m_tuple->truth_m[m_tuple->truth_Zee_e1]);

    TLorentzVector L2; 
    L2.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Zee_e2],
		    m_tuple->truth_eta[m_tuple->truth_Zee_e2],
		    m_tuple->truth_phi[m_tuple->truth_Zee_e2],
		    m_tuple->truth_m[m_tuple->truth_Zee_e2]);
    
    HGen_Zee_m->Fill((L1+L2).M()/1000,m_tuple->eve_mc_w);
    HGen_Zee_pt->Fill((L1+L2).Pt()/1000,m_tuple->eve_mc_w);
    if((L1+L2).Pt()>1.)
      HGen_Zee_eta->Fill((L1+L2).Eta(),m_tuple->eve_mc_w);
    else HGen_Zmm_eta->Fill(-999,m_tuple->eve_mc_w);
  }

  if(m_tuple->truth_Wmv>-1) HGen_Wmv_m->Fill(m_tuple->truth_m[m_tuple->truth_Wmv]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Wmv>-1) HGen_Wmv_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Wmv]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Wmv>-1) HGen_Wmv_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Wmv],m_tuple->eve_mc_w);
  if(m_tuple->truth_Wmv_m>-1) HGen_Wmv_m_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Wmv_m]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Wmv_m>-1) HGen_Wmv_m_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Wmv_m],m_tuple->eve_mc_w);
  if(m_tuple->truth_Wmv_v>-1) HGen_Wmv_v_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Wmv_v]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Wmv_v>-1) HGen_Wmv_v_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Wmv_v],m_tuple->eve_mc_w);

  if(m_tuple->truth_Wmv == -1 && m_tuple->truth_Wmv_m>-1 && m_tuple->truth_Wmv_v>-1 ){
    TLorentzVector L1; 
    L1.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Wmv_m],
		    m_tuple->truth_eta[m_tuple->truth_Wmv_m],
		    m_tuple->truth_phi[m_tuple->truth_Wmv_m],
		    m_tuple->truth_m[m_tuple->truth_Wmv_m]);

    TLorentzVector L2; 
    L2.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Wmv_v],
		    m_tuple->truth_eta[m_tuple->truth_Wmv_v],
		    m_tuple->truth_phi[m_tuple->truth_Wmv_v],
		    m_tuple->truth_m[m_tuple->truth_Wmv_v]);
    
    HGen_Wmv_m->Fill((L1+L2).M()/1000,m_tuple->eve_mc_w);
    HGen_Wmv_pt->Fill((L1+L2).Pt()/1000,m_tuple->eve_mc_w);
    if((L1+L2).Pt()>1.)
      HGen_Wmv_eta->Fill((L1+L2).Eta(),m_tuple->eve_mc_w);
    else HGen_Zmm_eta->Fill(-999,m_tuple->eve_mc_w);
  }


  if(m_tuple->truth_Wev>-1) HGen_Wev_m->Fill(m_tuple->truth_m[m_tuple->truth_Wev]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Wev>-1) HGen_Wev_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Wev]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Wev>-1) HGen_Wev_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Wev],m_tuple->eve_mc_w);
  if(m_tuple->truth_Wev_e>-1) HGen_Wev_e_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Wev_e]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Wev_e>-1) HGen_Wev_e_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Wev_e],m_tuple->eve_mc_w);
  if(m_tuple->truth_Wev_v>-1) HGen_Wev_v_pt->Fill(m_tuple->truth_pt[m_tuple->truth_Wev_v]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_Wev_v>-1) HGen_Wev_v_eta->Fill(m_tuple->truth_eta[m_tuple->truth_Wev_v],m_tuple->eve_mc_w);

  if(m_tuple->truth_Wev == -1 && m_tuple->truth_Wev_e>-1 && m_tuple->truth_Wev_v>-1 ){
    TLorentzVector L1; 
    L1.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Wev_e],
		    m_tuple->truth_eta[m_tuple->truth_Wev_e],
		    m_tuple->truth_phi[m_tuple->truth_Wev_e],
		    m_tuple->truth_m[m_tuple->truth_Wev_e]);

    TLorentzVector L2; 
    L2.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_Wev_v],
		    m_tuple->truth_eta[m_tuple->truth_Wev_v],
		    m_tuple->truth_phi[m_tuple->truth_Wev_v],
		    m_tuple->truth_m[m_tuple->truth_Wev_v]);
    
    HGen_Wev_m->Fill((L1+L2).M()/1000,m_tuple->eve_mc_w);
    HGen_Wev_pt->Fill((L1+L2).Pt()/1000,m_tuple->eve_mc_w);
    if((L1+L2).Pt()>1.)
      HGen_Wev_eta->Fill((L1+L2).Eta(),m_tuple->eve_mc_w);
    else HGen_Zmm_eta->Fill(-999,m_tuple->eve_mc_w);
  }


  if(m_tuple->truth_H0bb>-1) HGen_H0bb_m->Fill(m_tuple->truth_m[m_tuple->truth_H0bb]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_H0bb>-1) HGen_H0bb_pt->Fill(m_tuple->truth_pt[m_tuple->truth_H0bb]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_H0bb>-1) HGen_H0bb_eta->Fill(m_tuple->truth_eta[m_tuple->truth_H0bb],m_tuple->eve_mc_w);
  if(m_tuple->truth_H0bb_b1>-1) HGen_H0bb_b1_pt->Fill(m_tuple->truth_pt[m_tuple->truth_H0bb_b1]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_H0bb_b1>-1) HGen_H0bb_b1_eta->Fill(m_tuple->truth_eta[m_tuple->truth_H0bb_b1],m_tuple->eve_mc_w);
  if(m_tuple->truth_H0bb_b2>-1) HGen_H0bb_b2_pt->Fill(m_tuple->truth_pt[m_tuple->truth_H0bb_b2]/1000,m_tuple->eve_mc_w);
  if(m_tuple->truth_H0bb_b2>-1) HGen_H0bb_b2_eta->Fill(m_tuple->truth_eta[m_tuple->truth_H0bb_b2],m_tuple->eve_mc_w);

  if(m_tuple->truth_H0bb == -1 && m_tuple->truth_H0bb_b1>-1 && m_tuple->truth_H0bb_b2>-1 ){
    TLorentzVector L1; 
    L1.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_H0bb_b1],
		    m_tuple->truth_eta[m_tuple->truth_H0bb_b1],
		    m_tuple->truth_phi[m_tuple->truth_H0bb_b1],
		    m_tuple->truth_m[m_tuple->truth_H0bb_b1]);

    TLorentzVector L2; 
    L2.SetPtEtaPhiM(m_tuple->truth_pt[m_tuple->truth_H0bb_b2],
		    m_tuple->truth_eta[m_tuple->truth_H0bb_b2],
		    m_tuple->truth_phi[m_tuple->truth_H0bb_b2],
		    m_tuple->truth_m[m_tuple->truth_H0bb_b2]);
    
    HGen_H0bb_m->Fill((L1+L2).M()/1000,m_tuple->eve_mc_w);
    HGen_H0bb_pt->Fill((L1+L2).Pt()/1000,m_tuple->eve_mc_w);
    if((L1+L2).Pt()>1.)
      HGen_H0bb_eta->Fill((L1+L2).Eta(),m_tuple->eve_mc_w);
    else HGen_Zmm_eta->Fill(-999,m_tuple->eve_mc_w);
  }

  
  if(m_tuple->truth_ZHmmbb>-1){
    HGen_ZH_m->Fill(m_tuple->truth_m[m_tuple->truth_ZHmmbb]/1000,m_tuple->eve_mc_w);
    HGen_ZH_pt->Fill(m_tuple->truth_pt[m_tuple->truth_ZHmmbb]/1000,m_tuple->eve_mc_w);
    HGen_ZH_eta->Fill(m_tuple->truth_eta[m_tuple->truth_ZHmmbb],m_tuple->eve_mc_w);
  }else if(m_tuple->truth_ZHeebb>-1){
    HGen_ZH_m->Fill(m_tuple->truth_m[m_tuple->truth_ZHeebb]/1000,m_tuple->eve_mc_w);
    HGen_ZH_pt->Fill(m_tuple->truth_pt[m_tuple->truth_ZHeebb]/1000,m_tuple->eve_mc_w);
    HGen_ZH_eta->Fill(m_tuple->truth_eta[m_tuple->truth_ZHeebb],m_tuple->eve_mc_w);
  }

  if(m_tuple->truth_WHmvbb>-1){
    HGen_WH_m->Fill(m_tuple->truth_m[m_tuple->truth_WHmvbb]/1000,m_tuple->eve_mc_w);
    HGen_WH_pt->Fill(m_tuple->truth_pt[m_tuple->truth_WHmvbb]/1000,m_tuple->eve_mc_w);
    HGen_WH_eta->Fill(m_tuple->truth_eta[m_tuple->truth_WHmvbb],m_tuple->eve_mc_w);
  }else if(m_tuple->truth_WHevbb>-1){
    HGen_WH_m->Fill(m_tuple->truth_m[m_tuple->truth_WHevbb]/1000,m_tuple->eve_mc_w);
    HGen_WH_pt->Fill(m_tuple->truth_pt[m_tuple->truth_WHevbb]/1000,m_tuple->eve_mc_w);
    HGen_WH_eta->Fill(m_tuple->truth_eta[m_tuple->truth_WHevbb],m_tuple->eve_mc_w);
  }



  ///Resonance analysis
  if(m_tuple->truth_RToVH>-1){
    HGen_RToVH_m->Fill(m_tuple->truth_m[m_tuple->truth_RToVH]/1000,m_tuple->eve_mc_w);
    HGen_RToVH_pt->Fill(m_tuple->truth_pt[m_tuple->truth_RToVH]/1000,m_tuple->eve_mc_w);
    HGen_RToVH_eta->Fill(m_tuple->truth_eta[m_tuple->truth_RToVH],m_tuple->eve_mc_w);
    
    if(m_tuple->truth_RToVH_V>-1){
      HGen_RToVH_V_m->Fill(m_tuple->truth_m[m_tuple->truth_RToVH_V]/1000,m_tuple->eve_mc_w);
      HGen_RToVH_V_pt->Fill(m_tuple->truth_pt[m_tuple->truth_RToVH_V]/1000,m_tuple->eve_mc_w);
      HGen_RToVH_V_eta->Fill(m_tuple->truth_eta[m_tuple->truth_RToVH_V],m_tuple->eve_mc_w);
    }
    if(m_tuple->truth_RToVH_H>-1){
      HGen_RToVH_H_m->Fill(m_tuple->truth_m[m_tuple->truth_RToVH_H]/1000,m_tuple->eve_mc_w);
      HGen_RToVH_H_pt->Fill(m_tuple->truth_pt[m_tuple->truth_RToVH_H]/1000,m_tuple->eve_mc_w);
      HGen_RToVH_H_eta->Fill(m_tuple->truth_eta[m_tuple->truth_RToVH_H],m_tuple->eve_mc_w);

      HGen_RToVH_H_p->Fill(m_tuple->truth_p[m_tuple->truth_RToVH_H]/1000,m_tuple->eve_mc_w);
    }
    if(m_tuple->truth_RToVH_H_b1>-1){
      HGen_RToVH_H_b1_m->Fill(m_tuple->truth_m[m_tuple->truth_RToVH_H_b1]/1000,m_tuple->eve_mc_w);
      HGen_RToVH_H_b1_pt->Fill(m_tuple->truth_pt[m_tuple->truth_RToVH_H_b1]/1000,m_tuple->eve_mc_w);
      HGen_RToVH_H_b1_eta->Fill(m_tuple->truth_eta[m_tuple->truth_RToVH_H_b1],m_tuple->eve_mc_w);
    }
    if(m_tuple->truth_RToVH_H_b2>-1){
      HGen_RToVH_H_b2_m->Fill(m_tuple->truth_m[m_tuple->truth_RToVH_H_b2]/1000,m_tuple->eve_mc_w);
      HGen_RToVH_H_b2_pt->Fill(m_tuple->truth_pt[m_tuple->truth_RToVH_H_b2]/1000,m_tuple->eve_mc_w);
      HGen_RToVH_H_b2_eta->Fill(m_tuple->truth_eta[m_tuple->truth_RToVH_H_b2],m_tuple->eve_mc_w);
    }

    if(m_tuple->truth_RToVH_H_b1>-1 && m_tuple->truth_RToVH_H_b2>-1){
      HGen_RToVH_H_dR->Fill(m_tuple->truth_RToVH_H_dR,m_tuple->eve_mc_w);
      HGen_RToVH_H_dRVsp->Fill(m_tuple->truth_p[m_tuple->truth_RToVH_H]/1000, m_tuple->truth_RToVH_H_dR, m_tuple->eve_mc_w);
    }
    
  }


}




void BaseTupleMaker :: printMCTruth(){

  const xAOD::TruthParticleContainer* Truth = 0;
  if( ! m_event->retrieve( Truth , m_MCTruthIn.c_str() ).isSuccess() ){
    Error("execute()", "Failed to retrieve  TruthParticle collection. Exiting." );
    return;
  }

  cout<<"MC Truth List : List Size = "<<Truth->size()<<endl;
  for (unsigned int i = 0 ; i < Truth->size(); ++i) {
    const xAOD::TruthParticle * part = Truth->at(i);
    cout<<"Status="<<part->status() 
	<<",  PDG="<<part->pdgId()
	<<",  M="<<part->p4().M()
	<<",  Pt="<<part->p4().Pt();
    if(part->p4().Pt()>1)cout<<",  Eta="<<part->p4().Eta();
    cout<<",  Phi="<<part->p4().Phi()
	<<endl;
  }  

}



///////////////////
EL::StatusCode BaseTupleMaker :: postExecute ()
{
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode BaseTupleMaker :: finalize ()
{  
  printCounters();
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode BaseTupleMaker :: histFinalize ()
{
  TFile * f = wk()->getOutputFile(m_filename);
  f->ls();
  return EL::StatusCode::SUCCESS;
}

//////////////////////////////////
void  BaseTupleMaker::incrementCounter(const char * name, float w){
  //check if counter is already registered:
  bool registered=0;
  unsigned int i=0;
  for(;i<counterNames.size();i++){
    if(counterNames[i]==name){
      counters[i]+=w;
      registered=1;
      break;
    }
  }
  if(!registered){
    counterNames.push_back(name);
    float * counter=new float(w);
    counters.push_back(*counter);
  }

}

float  BaseTupleMaker::getCounter(const char * name){  
  for(unsigned int i=0;i<counterNames.size();i++){
    if(counterNames[i]==name)
      return counters[i];
  }
  return 0.;
}

void BaseTupleMaker::printCounters(){
  for(unsigned int i=0;i<counterNames.size();i++){
    cout<<counterNames[i]<<" = "<<counters[i]<<endl;
  }
}


//////////////

EL::StatusCode BaseTupleMaker :: initPileUpWeights(TFile * f){

  //////////////////////////////////////////////////
  //////////////////Pile Up
  //////////////////////////////////////////////////
  // // configuration and initialization example
  // m_Pileup  = new CP::PileupReweightingTool("Pileup");
  // std::vector<std::string> confFiles;
  // confFiles.push_back("data/HbbAnalysis/mc12ab_defaults.prw.root"); 
  // m_Pileup->setProperty( "ConfigFiles", confFiles);
  // //std::vector<std::string> lcalcFiles;
  // //lcalcFiles.push_back("MyDir/ilumicalc_histograms_xxxxx.root");
  // //m_Pileup->setProperty( "LumiCalcFiles", lcalcFiles);
  // m_Pileup->initialize();

  ///This is some other tool
  //Root::TPileupReweighting* PileUpTool = new Root::TPileupReweighting( "PileupReweightingTool" );

  ///Save the pile up distribution
  HPileUp=new TH1F("HPileUp","HPileUp",100,0,100);
  //wk()->addOutput(HPileUp); //This puts the histogram in a separate file
  HPileUp->SetDirectory(f);

  //////////////////////////////////////////////////////
  //fill the files
  pileUpDataFiles.push_back(std::string(gSystem->Getenv("ROOTCOREBIN"))+"/data/HbbAnalysis/pileup_data_8TeV_PeriodB.root");
  pileUpMCFiles.push_back(std::string(gSystem->Getenv("ROOTCOREBIN"))+"/data/HbbAnalysis/pileup_mc14_8TeV.root");

  //create the historgrams here outside the files
  // m_tuple->nmcpuw=0;
  // for(unsigned int i=0;i<pileUpMCFiles.size();i++){
  //   for(unsigned int j=0;j<pileUpDataFiles.size();j++){
  //     PileUpRatios[m_tuple->nmcpuw]=new TH1F(std::string("PileUpRatios")+(long)(m_tuple->nmcpuw),"pileup",100,0,100);
  //     PileUpRatios[m_tuple->nmcpuw]->SetDirectory(f);
  //     cout<<"PileUpWeight: "<<m_tuple->nmcpuw<<"  "<<pileUpMCFiles[i].c_str()<<" "<<pileUpDataFiles[j].c_str()<<endl;
  //     m_tuple->nmcpuw++;
  //   }
  // }

  //now fill weight the histograms
  m_tuple->nmcpuw=0;
  for(unsigned int i=0;i<pileUpMCFiles.size();i++){
    TFile FMC(pileUpMCFiles[i].c_str(),"READ");
    TH1F* HMC=(TH1F*)FMC.Get("pileup");
    if(!HMC){
      Error("initPileUpWeights()", "No MC PileUp Histo found");
      return EL::StatusCode::FAILURE;
    }

    //check the histogram:
    for(int b=1;b<=HMC->GetNbinsX();b++)
      if(HMC->GetBinContent(b) < 0. //can't be negative
	 || HMC->GetBinContent(b) > 1.0 //can't be >1 because histo integral is 1.
	 ){
	cout<<"Pileup bin content is bad in "<<pileUpMCFiles[i].c_str()<<endl;
      }

    for(unsigned int j=0;j<pileUpDataFiles.size();j++){
      TFile FData(pileUpDataFiles[j].c_str(),"READ");
      TH1F* HData=(TH1F*)FData.Get("pileup");
      if(!HData){
	Error("initPileUpWeights()", "No Data PileUp Histo found");
	return EL::StatusCode::FAILURE;
      }


      if(HData->GetNbinsX()!=HMC->GetNbinsX()){
	Error("initPileUpWeights()", "PileUp Bins don't match");
	return EL::StatusCode::FAILURE;
      }

      //check the histogram:
      for(int b=1;b<=HData->GetNbinsX();b++)
	if(HData->GetBinContent(b)<0. //can't be negative
	   || HData->GetBinContent(b) >1.0 //can't be >1 because histo integral is 1.
	   ){
	  Error("initPileUpWeights()", "Pileup bin contents are bad");
	  return EL::StatusCode::FAILURE;
	}


      //Create the ratios and link them to the output file
      PileUpRatios[m_tuple->nmcpuw]=new TH1F(std::string("PileUpRatios")+(long)(m_tuple->nmcpuw),"pileup",
					     HPileUp->GetNbinsX(),
					     HPileUp->GetXaxis()->GetXmin(),
					     HPileUp->GetXaxis()->GetXmax());
      PileUpRatios[m_tuple->nmcpuw]->SetDirectory(f);

      //Calculate the ratio Data/MC
      //Also calculate the MC integral after reweighting
      float mcIntegral=0.;
      for(int b=1;b<=HMC->GetNbinsX();b++){
	if(HMC->GetBinContent(b)<=0. || HData->GetBinContent(b)<=0.)
	  PileUpRatios[m_tuple->nmcpuw]->SetBinContent(b,0.);
	else PileUpRatios[m_tuple->nmcpuw]->SetBinContent(b,HData->GetBinContent(b)/HMC->GetBinContent(b));
	
	mcIntegral+= PileUpRatios[m_tuple->nmcpuw]->GetBinContent(b) * HMC->GetBinContent(b) ;
      }

      //rescale ratio to correct MC integral
      if(mcIntegral>0.) PileUpRatios[m_tuple->nmcpuw]->Scale(1./mcIntegral);
      else {
	Error("initPileUpWeights()", "Failed to rescale PileUpRatio");
	return EL::StatusCode::FAILURE;
      }

      cout<<"PileUpWeight: "<<m_tuple->nmcpuw<<"  "<<pileUpMCFiles[i].c_str()<<" "<<pileUpDataFiles[j].c_str()<<endl;
      
      m_tuple->nmcpuw++;
      FData.Close();
    }
    FMC.Close();
  }

  return EL::StatusCode::SUCCESS;
}
