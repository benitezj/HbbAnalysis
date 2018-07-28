#ifndef CXAODADDCONTENT_H
#define CXAODADDCONTENT_H

// Event Loop includes
#include "EventLoop/Algorithm.h"
#include "EventLoop/StatusCode.h"
#include "xAODRootAccess/TEvent.h"

//CxAODMaker tools 
class ConfigStore;
//class EventInfoHandler;
//class JetHandler;


////// For rho value computation needed with JetCalibTools-00-04-30
#ifdef ROOTCORE
//#include "xAODRootAccess/Init.h"
//#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/TStore.h"
#include "xAODRootAccess/TActiveStore.h"
#endif
class EventDensityTool;
class PseudoJetGetter;


class CxAODAddContent : public EL::Algorithm
{
public:
  CxAODAddContent (); //Default Do not use. will crash
  CxAODAddContent (std::string m_configPath);
  virtual ~CxAODAddContent();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  
  // this is needed to distribute the algorithm to the workers
  ClassDef(CxAODAddContent, 1);


protected:
  ConfigStore * m_config; //!
  xAOD::TEvent * m_event; //!

  //  EventInfoHandler * m_eventInfoHandler; //!
  //  JetHandler* m_jetHandler; //!


private:

  EL::StatusCode fillTruthParticles();
  EL::StatusCode fillJets();

  EventDensityTool * edtool; //!
  PseudoJetGetter* lcgetter; //!
  xAOD::TStore* transDataStore; //!

};

#endif
