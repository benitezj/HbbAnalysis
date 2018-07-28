#include "HbbAnalysis/WHlnubbTupleMaker.h"

// this is needed to distribute the algorithm to the workers
ClassImp(WHlnubbTupleMaker)


WHlnubbTupleMaker :: WHlnubbTupleMaker ()
{
  ///Do not use this constructor
}

WHlnubbTupleMaker :: WHlnubbTupleMaker (std::string configPath) :
  VHTupleMaker(configPath),
  m_tuple(0)
{
}

EL::StatusCode WHlnubbTupleMaker :: initialize ()
{
  if(!m_tuple){
    //tuple must be created in a fully defined TupleMaker
    cout<<"WHlnubbTupleMaker :: initialize() : Error, m_tuple should have been defined at this point"<<endl; 
    return EL::StatusCode::FAILURE;
  }
  VHTupleMaker::m_tuple = m_tuple;
  
  return VHTupleMaker::initialize();
}


EL::StatusCode WHlnubbTupleMaker :: processEvent(){
  return VHTupleMaker :: processEvent();
}


bool WHlnubbTupleMaker :: jetOverlap (int jetindex){
  if(deltaR(m_tuple->jet_eta[jetindex],m_tuple->jet_phi[jetindex],lp4.Eta(),lp4.Phi()) < 0.4) return 1;
  return 0; 
}
