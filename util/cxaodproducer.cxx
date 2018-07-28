#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/SampleLocal.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/DiskListLocal.h"
#include <TRegexp.h>
#include <RootCoreUtils/StringUtil.h>
#include "EventLoop/Job.h"
#include "EventLoop/Driver.h"
#include "EventLoop/DirectDriver.h"
#include "EventLoopGrid/PrunDriver.h"

#include <stdlib.h> 

#include "CxAODMaker/AnalysisBase.h"
#include "CxAODTools/ConfigStore.h"

#include "HbbAnalysis/CxAODAddContent.h"

#include "HbbAnalysis/tools.h"

using namespace std;

int main(int argc, char* argv[]) {
  if(argc < 2 ){ 
    cout<<"You need to provide an action"<<endl;
    exit(0);
  }
  std::string action = argv[1];
  cout<<"action "<<action<<endl;

  //  
  std::string XAODCONFIG(getenv("XAODCONFIG"));//algorithm configuration
  cout<<"XAODCONFIG  "<<XAODCONFIG.c_str()<<endl;
  
  std::string XAODSAMPLENAME(getenv("XAODSAMPLENAME"));//name of the sample
  cout<<"XAODSAMPLENAME  "<<XAODSAMPLENAME.c_str()<<endl;

  std::string XAODOUTPATH(getenv("XAODOUTPATH")); //path where output will be written
  cout<<"XAODOUTPATH  "<<XAODOUTPATH.c_str()<<endl;

  // set up the job for xAOD access:
  xAOD::Init().ignore();
  
  // Construct the sample to run on:
  SH::SampleHandler sampleHandler;

  //local sample
  if(action == "local" ){
    std::string samplePath(getenv("XAODSAMPLEPATH"));//for local samples only
    cout<<"XAODSAMPLEPATH  "<<samplePath.c_str()<<endl;

    int XAODNFILES = 1000000;
    if(getenv("XAODNFILES")){
      XAODNFILES = atoi(getenv("XAODNFILES"));
      cout<<"XAODNFILES  "<<XAODNFILES<<endl;
    }

    SH::SampleLocal* sample = new SH::SampleLocal("outputLabel");
    SH::DiskListLocal list(samplePath + "/" + XAODSAMPLENAME);
    int counter=0;
    while(list.next() && counter<XAODNFILES){
      if(RCU::match_expr(RCU::glob_to_regexp("*AOD*.root*"),list.fileName())){
	sample->add(list.path());
	counter++;
      }
    }
    sampleHandler.add(sample);
  }

  //grid sample
  if(action == "grid"){
    SH::scanDQ2(sampleHandler,XAODSAMPLENAME);
  }  


  sampleHandler.setMetaString("nc_tree", "CollectionTree");
  sampleHandler.print();

  // create analysisBase, set job options, maniplate members and add our analysis to the job:
  AnalysisBase* analysisBase = new AnalysisBase();
  analysisBase->setConfig(XAODCONFIG);

  if(getenv("XAODNEVENTS")){ 
    int XAODNEVENTS = atoi(getenv("XAODNEVENTS"));
    cout<<"XAODNEVENTS  "<<XAODNEVENTS<<endl;    
    analysisBase->m_maxEvent = XAODNEVENTS;
  }

  ///Add additional content to CxAOD
  CxAODAddContent * AddContent = new CxAODAddContent(XAODCONFIG);


  // Create an EventLoop job:
  EL::Job job;
  job.useXAOD ();
  job.sampleHandler(sampleHandler);
  job.options()->setDouble (EL::Job::optMaxEvents, analysisBase->m_maxEvent ) ; 
  job.options()->setString( EL::Job::optXaodAccessMode, EL::Job::optXaodAccessMode_branch );


  // set job algorithms, order matters because m_event->fill() needs to be called only once and at the end 
  job.algsAdd(AddContent);  
  job.algsAdd(analysisBase);
 

  if( action == "local" ){//SUBMIT LOCAL
    EL::DirectDriver driver;
    driver.submit(job,XAODOUTPATH + "/" + XAODSAMPLENAME);
  }else if( action == "grid" ){///SUBMIT GRID 
    EL::PrunDriver driver;

    std::string outpath=XAODOUTPATH + "/" + XAODSAMPLENAME;
       
    vector<string> tokens = HbbAnalysis::split(XAODSAMPLENAME,'.');
    std::string OUTPUTNAME=tokens[0]+"."+tokens[1]+"."+tokens[2];
    std::string outDS=std::string("user.")+getenv("USER")+"."+OUTPUTNAME;
    if(getenv("XAODOUTTAG")){
      std::string XAODOUTTAG = getenv("XAODOUTTAG");
      if(XAODOUTTAG.compare("") != 0){
	cout<<"XAODOUTTAG  "<<XAODOUTTAG.c_str()<<endl;      
	outDS+="_"+XAODOUTTAG;
	outpath+="_"+XAODOUTTAG;
      }
    }
    //driver.options()->setString("nc_outDS",outDS.c_str());//does not work
    //driver.options()->setString(EL::Job::optGridOutDS,outDS);//not available
    //option from here /cvmfs/atlas.cern.ch/repo/sw/ASG/AnalysisBase/2.0.21/EventLoopGrid/Root/PrunDriver.cxx
    driver.options()->setString("nc_outputSampleName",outDS);


    if(getenv("XAODNFILES")){ 
      int XAODNFILES = atoi(getenv("XAODNFILES"));
      cout<<"XAODNFILES  "<<XAODNFILES<<endl;
      driver.options()->setDouble(EL::Job::optGridNFilesPerJob,XAODNFILES);
    }

    if(getenv("XAODBLACKLIST")){
      std::string XAODBLACKLIST = getenv("XAODBLACKLIST");
      cout<<"XAODBLACKLIST  "<<XAODBLACKLIST.c_str()<<endl;
      driver.options()->setString(EL::Job::optGridExcludedSite,XAODBLACKLIST);
    }

    if(getenv("XAODNOSUBMIT") && atoi(getenv("XAODNOSUBMIT")) == 1){
      //was having trouble with value option value set to 0 so better to do like this.
      driver.options()->setDouble(EL::Job::optGridNoSubmit,1);
      driver.options()->setDouble("nc_showCmd",1);
    }

    if(getenv("XAODNGBPERJOB")){
      int XAODNGBPERJOB = atoi(getenv("XAODNGBPERJOB"));
      cout<<"XAODNGBPERJOB  "<<XAODNGBPERJOB<<endl; 
      driver.options()->setDouble(EL::Job::optGridNGBPerJob,XAODNGBPERJOB);
    }
    
    driver.options()->setString("nc_mergeOutput","false"); 

 
    driver.submitOnly(job,outpath);
  }else cout<<"Invalid action: "<<action<<endl;

  return 0;
}

