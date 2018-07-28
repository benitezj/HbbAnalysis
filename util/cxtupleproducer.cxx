#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/DiskListLocal.h"
#include "SampleHandler/DiskListEOS.h"
#include "SampleHandler/SampleLocal.h"

#include <TRegexp.h>
#include <RootCoreUtils/StringUtil.h>

#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "EventLoop/ProofDriver.h"
#include "EventLoop/LSFDriver.h"
#include "EventLoopGrid/PrunDriver.h"

#include <stdlib.h> 

#include "CxAODTools/ConfigStore.h"

#include "HbbAnalysis/BaseTupleMaker.h"
#include "HbbAnalysis/RecoTupleMaker.h"
#include "HbbAnalysis/ZmmTupleMaker.h"
#include "HbbAnalysis/ZeeTupleMaker.h"
#include "HbbAnalysis/WmunuTupleMaker.h"
#include "HbbAnalysis/WenuTupleMaker.h"
#include "HbbAnalysis/ZHmmbbTupleMaker.h"
#include "HbbAnalysis/ZHeebbTupleMaker.h"
#include "HbbAnalysis/WHmnubbTupleMaker.h"
#include "HbbAnalysis/WHenubbTupleMaker.h"

using namespace std;

vector<string> split(const string &text, char sep) {
  vector<string> tokens;
  int start = 0, end = 0;
  while ((end = text.find(sep, start)) != int(string::npos) ) {
    string tok=text.substr(start, end - start);
    //cout<<tok<<endl;
    tokens.push_back(tok);
    start = end + 1;
  }
  tokens.push_back(text.substr(start));
  return tokens;
}

int main(int argc, char* argv[]) {

  if(argc < 2 ){ 
    std::cout<<"You need to provide an option"<<std::endl;
    exit(0);
  }
  std::string action = argv[1];

  std::string inPath(getenv("TUPLEINPATH"));
  cout<<"TUPLEINPATH  "<<inPath.c_str()<<endl;

  std::string sampleName(getenv("TUPLESAMPLENAME"));
  cout<<"TUPLESAMPLENAME  "<<sampleName.c_str()<<endl;

  std::string outPath(getenv("TUPLEOUTPATH"));
  cout<<"TUPLEOUTPATH  "<<outPath.c_str()<<endl;

  std::string tupleConfig(getenv("TUPLECONFIG"));
  cout<<"TUPLECONFIG  "<<tupleConfig.c_str()<<endl;

  std::string channel(getenv("TUPLECHANNEL"));
  cout<<"TUPLECHANNEL  "<<channel.c_str()<<endl;

  int filesperjob = atoi(getenv("TUPLENFILES"));
  cout<<"TUPLENFILES  "<<filesperjob<<endl;


  // Construct the sample to run on:
  SH::SampleHandler sampleHandler;

  std::string owner="user.benitezj.";//in case of grid job
  if(action == "local" ){
    //SH::DiskListLocal list(inPath + "/" + sampleName);
    //SH::scanSingleDir(sampleHandler,"tuple",list,"*outputLabel_*.root*");

    SH::SampleLocal* sample = new SH::SampleLocal("tuple");
    SH::DiskListLocal list(inPath + "/" + sampleName);
    int counter=0;
    while(list.next() && ( counter<filesperjob || filesperjob == -1 ) ){
      if(RCU::match_expr(RCU::glob_to_regexp("*outputLabel*.root*"),list.fileName())){
        sample->add(list.path());
        counter++;
      }
    }
    sampleHandler.add(sample);
  }else if(action=="grid"){
    SH::scanDQ2(sampleHandler,owner+sampleName+"_outputLabel.root*");
  }else cout<<"Invalid action required."<<endl;
  
  sampleHandler.setMetaString("nc_tree", "CollectionTree");
  sampleHandler.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler(sampleHandler);
  //job.options()->setDouble (EL::Job::optMaxEvents,-1);

  // create algorithm, set job options, and add our analysis to the job:
  BaseTupleMaker* tupleMaker =0;
  if(channel=="base")tupleMaker = new BaseTupleMaker(tupleConfig);
  if(channel=="reco")tupleMaker = new RecoTupleMaker(tupleConfig);
  if(channel=="Zmm")tupleMaker = new ZmmTupleMaker(tupleConfig);
  if(channel=="Zee")tupleMaker = new ZeeTupleMaker(tupleConfig);
  if(channel=="Wmunu")tupleMaker = new WmunuTupleMaker(tupleConfig);
  if(channel=="Wenu")tupleMaker = new WenuTupleMaker(tupleConfig);
  if(channel=="ZHmmbb")tupleMaker = new ZHmmbbTupleMaker(tupleConfig);
  if(channel=="ZHeebb")tupleMaker = new ZHeebbTupleMaker(tupleConfig);
  if(channel=="WHmnubb")tupleMaker = new WHmnubbTupleMaker(tupleConfig);
  if(channel=="WHenubb")tupleMaker = new WHenubbTupleMaker(tupleConfig);
  if(!tupleMaker){cout<<"Wrong channel"<<endl; exit(0);}
  job.algsAdd(tupleMaker);
  
  if(action=="local" ){//LOCAL/EOS in lxplus
    cout<<"Processing locally."<<endl;
    EL::DirectDriver driver;
    driver.submitOnly(job,outPath + "/" + sampleName);
  }else if(action=="grid"){//Submitt to grid trying to use CxAOD files from PANDA
    EL::PrunDriver driver;
    //driver.options()->setDouble("nc_nGBPerJob",8);
    driver.options()->setDouble("nc_nFilesPerJob",filesperjob);
    driver.options()->setDouble("nc_mergeOutput",0); // force to no merge
    driver.options()->setString("nc_outputSampleName",owner+sampleName+"_tup"); //there are problems with the length of this name
    driver.submitOnly(job,outPath + "/" + sampleName);
  }

  return 0;
}

