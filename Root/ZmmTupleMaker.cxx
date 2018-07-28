#include "HbbAnalysis/ZmmTupleMaker.h"


// this is needed to distribute the algorithm to the workers
ClassImp(ZmmTupleMaker)


ZmmTupleMaker :: ZmmTupleMaker ()
{
  ///Do not use this constructor
}

ZmmTupleMaker :: ZmmTupleMaker (std::string configPath) :
  ZllTupleMaker(configPath),
  m_tuple(0)
{
  

}

EL::StatusCode ZmmTupleMaker :: initialize ()
{

  //this is the top level, ntuple must be defined here
  m_tuple = new ZmmTuple();
  ZllTupleMaker::m_tuple = m_tuple;
    
  return ZllTupleMaker::initialize(); 
}

EL::StatusCode ZmmTupleMaker :: processEvent(){
  
  if( ZllTupleMaker :: processEvent()  == EL::StatusCode::FAILURE) 
    return EL::StatusCode::FAILURE;
  
  m_tuple->zll_ll=-1;
  std::vector<int> list;
  std::vector<int> listsel;

  //init loop
  for(int i=0;i<m_tuple->nmm;i++){
    list.push_back(i);
  }
  if(list.size()==0) return EL::StatusCode::FAILURE;
  incrementCounter("eventCounter_nmm");

  //leg1 id cut
  for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
    int m=m_tuple->mm_leg1[*it];
    if( m_tuple->muo_idVHl[m] == false ) continue;
    listsel.push_back(*it);
  }
  if(listsel.size()==0) return EL::StatusCode::FAILURE;
  list=listsel;
  listsel.clear();
  incrementCounter("eventCounter_leg1_id");
 
  ///leg1 pT cut
  for(std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
    int m=m_tuple->mm_leg1[*it];
    if( m_tuple->muo_pt[m] < 15000 ) continue;
    listsel.push_back(*it);
  }
  if(listsel.size()==0) return EL::StatusCode::FAILURE;
  list=listsel;
  listsel.clear();
  incrementCounter("eventCounter_leg1_pT");

  //leg1 eta cut
  for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
    int m=m_tuple->mm_leg1[*it];
    if( fabs(m_tuple->muo_eta[m]) > 2.5 ) continue;
    listsel.push_back(*it);
  }
  if(listsel.size()==0) return EL::StatusCode::FAILURE;
  list=listsel;
  listsel.clear();
  incrementCounter("eventCounter_leg1_eta");


  //leg1 iso cut
  for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
    int m=m_tuple->mm_leg1[*it];
    if( leptonIsoOption == 1 &&  m_tuple->muo_ptiso[m]/m_tuple->muo_pt[m] > 0.1 ) continue;
    listsel.push_back(*it);
  }
  if(listsel.size()==0) return EL::StatusCode::FAILURE;
  list=listsel;
  listsel.clear();
  incrementCounter("eventCounter_leg1_ptiso");

  // for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
  //   int m=m_tuple->mm_leg1[*it];
  //   if( m_tuple->muo_etiso[m]/m_tuple->muo_pt[m] > 0.1 ) continue;
  //   listsel.push_back(*it);
  // }
  // if(listsel.size()==0) return EL::StatusCode::FAILURE;
  // list=listsel;
  // listsel.clear();
  // incrementCounter("eventCounter_leg1_etiso");


  //leg2 id cut
  for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
    int m=m_tuple->mm_leg2[*it];
    if( m_tuple->muo_idVHl[m] == false ) continue;
    listsel.push_back(*it);
  }
  if(listsel.size()==0) return EL::StatusCode::FAILURE;
  list=listsel;
  listsel.clear();
  incrementCounter("eventCounter_leg2_id");

  ///leg2 pT cut
  for(std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
    int m=m_tuple->mm_leg2[*it];
    if( m_tuple->muo_pt[m] < 15000 ) continue;//use 2mu13 trigger
    listsel.push_back(*it);
  }
  if(listsel.size()==0) return EL::StatusCode::FAILURE;
  list=listsel;
  listsel.clear();
  incrementCounter("eventCounter_leg2_pT");


  //leg2 eta cut
  for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
    int m=m_tuple->mm_leg2[*it];
    if( fabs(m_tuple->muo_eta[m]) > 2.5 ) continue;
    listsel.push_back(*it);
  }
  if(listsel.size()==0) return EL::StatusCode::FAILURE;
  list=listsel;
  listsel.clear();
  incrementCounter("eventCounter_leg2_eta");


  //leg2 iso cut
  for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
    int m=m_tuple->mm_leg2[*it];
    if( leptonIsoOption == 1 &&  m_tuple->muo_ptiso[m]/m_tuple->muo_pt[m] > 0.1 ) continue;
    listsel.push_back(*it);
  }
  if(listsel.size()==0) return EL::StatusCode::FAILURE;
  list=listsel;
  listsel.clear();
  incrementCounter("eventCounter_leg2_ptiso");

  // for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
  //   int m=m_tuple->mm_leg2[*it];
  //   if( m_tuple->muo_etiso[m]/m_tuple->muo_pt[m] > 0.1 ) continue;
  //   listsel.push_back(*it);
  // }
  // if(listsel.size()==0) return EL::StatusCode::FAILURE;
  // list=listsel;
  // listsel.clear();
  // incrementCounter("eventCounter_leg2_etiso");

  
  ///Best candidate selection
  float bestcand=0.;
  for (std::vector<int>::iterator it = list.begin() ; it != list.end(); ++it){
    int m1=m_tuple->mm_leg1[*it];
    int m2=m_tuple->mm_leg2[*it];
    float sumpt =  m_tuple->muo_pt[m1] + m_tuple->muo_pt[m2];
    if(sumpt>bestcand){
      m_tuple->zll_ll=*it;
      bestcand=sumpt;
    }
  }

  
  //order the muons by pt
  if(m_tuple->muo_pt[m_tuple->mm_leg1[m_tuple->zll_ll]] 
     > m_tuple->muo_pt[m_tuple->mm_leg2[m_tuple->zll_ll]]  ){
    m_tuple->zll_l1 = m_tuple->mm_leg1[m_tuple->zll_ll];
    m_tuple->zll_l2 = m_tuple->mm_leg2[m_tuple->zll_ll];
  }  else{
    m_tuple->zll_l1 = m_tuple->mm_leg2[m_tuple->zll_ll];
    m_tuple->zll_l2 = m_tuple->mm_leg1[m_tuple->zll_ll];
  }

  //fill 4-vectors for later
  l1p4.SetPtEtaPhiM(m_tuple->muo_pt[m_tuple->zll_l1],
		    m_tuple->muo_eta[m_tuple->zll_l1],
		    m_tuple->muo_phi[m_tuple->zll_l1],
		    m_tuple->muo_m[m_tuple->zll_l1]);
  l2p4.SetPtEtaPhiM(m_tuple->muo_pt[m_tuple->zll_l2],
		    m_tuple->muo_eta[m_tuple->zll_l2],
		    m_tuple->muo_phi[m_tuple->zll_l2],
		    m_tuple->muo_m[m_tuple->zll_l2]);

  
  //Fill the jets
  fillJets();

  
  return EL::StatusCode::SUCCESS;
}
