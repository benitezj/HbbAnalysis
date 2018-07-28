#ifndef Sample_H
#define Sample_H

#include <memory>
#include <iostream>
#include <iomanip>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h> 
using namespace std;

#include <TROOT.h>
#include <TNamed.h>
#include <TSystem.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2.h>
#include <TH2F.h>
#include <TH2D.h>
#include <TList.h>
#include <TIterator.h>
#include <TKey.h>
#include <TGraphErrors.h>


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

class Sample : public TNamed {
  
public:
  
  Sample();
  Sample(const char * name, const char * title, const char * path);
  virtual ~Sample();
  

  void addRootFiles(TString name,TString path){ //useful when one background is in multiple directories
    if(nNames_>=10){cout<<"Too many root file directories."<<endl; return;}
    addFileNames[nNames_]=path+"/"+name; nNames_++;
  }
  void setColor(Int_t color){color_=color;}
  void setLineColor(Int_t color){lcolor_=color;}
  void setLineStyle(Int_t lstyle){lstyle_=lstyle;}
  void setDataType(TString type){ dataType_=type;  }
  void setTitle(TString title){ title_=title;  }
  void setFileName(TString name){ filename_ = name;}
  void setNtupleName(TString name){ ntpname_ = name;}

  void setEventWeight(TString weight){eventWeight_ = weight;}
  void setCrossection(float crossection){crossection_=crossection;} //in pb
  void setSampleLumi(float lumi){lumi_=lumi;}
  void resetScale(){ normFactor_=1.;}
  void scale(Float_t factor){if(!ntpChain_) openNtpFile(); normFactor_ *= factor;}

  void setSignalMass(Float_t mass){signalMass_=mass;}
  float getSignalMass(){return signalMass_;}

  //access
  TChain * getTChain(){if(!ntpChain_) openNtpFile(); return ntpChain_; }
  float getCrossection(){return crossection_;}
  TString getDataType(){return dataType_;}
  int getRun(){return run_;}
  TString getDataSet(){return dataSet_;}
  float getSampleEvents(){return genEvents_;}
  float getSampleEventsSumW(){return genEventsSumW_;}
  float getLumi(){ 
    if(dataType_=="Data") return lumi_;    
    else if(crossection_>0.){
      if(!ntpChain_) if(!openNtpFile()) return 0.;
      return getSampleEventsSumW()/crossection_;
    }
    return 0.;
  }
  float getNorm(){return normFactor_;}
  
  Int_t getColor(){return color_;}
  Int_t getLineColor(){return lcolor_;}
  Int_t getLineStyle(){return lstyle_;}
  Int_t getNFiles(){ if(!ntpChain_) if(!openNtpFile()) return 0; return ntpChain_->GetNtrees(); }
  Int_t getEntries(){ if(!ntpChain_) if(!openNtpFile()) return 0; return ntpChain_->GetEntries(); }




  TH1D* getHistoNtpFile(TString xvar,Int_t xnbins,Float_t xmin,Float_t xmax,TCut selection="");
  TH1D* getHistoNtpFile(TString xvar,Int_t Nbins, Float_t * Xbins,TCut selection="");
  
  TH2D* getHistoNtpFile(TString xvar,Int_t xnbins,Float_t xmin,Float_t xmax,TString yvar,Int_t ynbins,Float_t ymin,Float_t ymax,TCut selection="");


  void fillHisto(TH1* h, TString xvar,TCut selection="");


  TH1* getPileUp();


  TH1* getHisto(TString histoName, int nbins=0, float xmin=0., float xmax=0.);


  void setHistoAttr(TH1* h){
    h->SetTitle(title_);
    h->SetLineWidth(1);
    h->SetLineColor(1);
    h->SetFillColor(color_);
  }


  bool addSkim(TString name, TString selection){
    if(skimCounter>=20){cout<<"Too many skims"<<endl; return 0;}
    skimName[skimCounter]=name;
    skimSelection[skimCounter]=selection;
    skimCounter++;
    return 1;
  }

  bool skim(TString selection){
    if(!ntpChain_) if(!openNtpFile()) return 0;
    if(ntpChain_->GetNtrees()>0){
      gROOT->cd();    
      TTree* t = ntpChain_->CopyTree(selection);
      if(!t){cout<<"Failed to skim:"<<GetName()<<endl; return 0;}

      delete ntpChain_;
      ntpChain_=(TChain*)t;
      return 1;
    }
    cout<<"Skim failed because TChain has no files"<<endl;
    return 0;
  }

  bool runSkims(){
    for(int i=0;i<skimCounter;i++) if(!skim(skimSelection[i])) return 0;
  }
  
  TGraphErrors * getCutFlow();
  

protected:


private:

  TString path_;
  int run_;
  TString dataSet_;
  float crossection_;
  float lumi_;
  float genEvents_;
  float genEventsSumW_;
  TString eventWeight_;

  Int_t  nNames_;
  TString addFileNames[10];

  TString filename_;
  TString ntpname_;
  TChain* ntpChain_;
  Int_t NMAXFILES_;
  Int_t NMAXNONEXISTENT_;

  TString dataType_;
  Int_t color_;
  Int_t lcolor_;
  Int_t lstyle_;
  TString title_;
  float normFactor_;
  bool init_;

  Float_t signalMass_;
  
  bool openNtpFile();

  int getNProcEvents(TString logfile);
  float getSumOfWeights(TFile * rootFile);

  int     skimCounter=0;
  TString skimName[20];
  TString skimSelection[20];


  ClassDef(Sample, 1);
};

#endif 
