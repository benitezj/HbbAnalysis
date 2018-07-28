#ifndef Plotter_H
#define Plotter_H

#include <vector>
using namespace std;

#include <TNamed.h>
#include <TString.h>
#include <TH1D.h>
#include <THStack.h>
#include <TList.h>

#include "Sample.h"

class Plotter : public TNamed {

public:
  
  Plotter();
  Plotter(const char * name, const char * title);
  virtual ~Plotter();
  
  virtual void plot(TString variable, Int_t nbins, Float_t xmin, Float_t xmax, TString sel="", 
		    TString xlabel="", TString ylabel="", Float_t* legendcoords=0, TString filetag="", bool signal=0);
  
  void setOutputPath(TString path){outputpath_=path;}
  void setLumisFile(TString file){lumisFile_=file;}
  void setCrossectionsFile(TString file){crossectionsFile_=file;}
  void addSample(Sample* sample){
    if(sample->getDataType().CompareTo("Data")!=0)
      sample->setCrossection(findCrossection(sample));
    cout<<"Adding: "<<sample->GetTitle()<<" L="<<sample->getLumi()<<" X="<<sample->getCrossection()<<endl;
    samples_.push_back(sample);
  }   
  void addData(TString path, TString sample);//lumi in /pb
  void addAllData(TString path);// will search directory for all data* samples, lumi in /pb

  void defineBackground(TString name,TString sampleNames,int color,TString title){
    for( std::vector<TString>::const_iterator bkg=backgrounds_.begin(); bkg!=backgrounds_.end(); ++bkg)
      if((*bkg).CompareTo(name.Data()) == 0){
	cout<<"Background "<<name<<" was already defined. "<<endl; return;
      }
    backgrounds_.push_back(name);
    backgroundSampleNames_.push_back(sampleNames);
    backgroundColors_.push_back(color);
    backgroundTitles_.push_back(title);
  }

  void defineSignal(TString name,TString sampleNames,int color,TString title,int factor=1){
    for( std::vector<TString>::const_iterator sig=signals_.begin(); sig!=signals_.end(); ++sig)
      if((*sig).CompareTo(name.Data()) == 0){
	cout<<"Signal "<<name<<" was already defined. "<<endl; return;
      }
    signals_.push_back(name);
    signalSampleNames_.push_back(sampleNames);
    signalColors_.push_back(color);
    signalTitles_.push_back(title);
    signalScaleFactors_.push_back(factor);
  }


  bool skimSamples(TString selection){
    cout<<"Skiming samples:"<<endl;
    for( std::vector<Sample*>::const_iterator s = samples_.begin(); s != samples_.end(); ++s){
      if(!((*s)->skim(selection))) return 0;
      cout<<(*s)->GetName()<<" entries :"<<(*s)->getEntries()<<endl;
    }
    return 1;
  }
  
  bool scaleSamplesLumi();  

  TH1D* getSample(TString samplename);
  TH1D* getTotalData();

  bool printRawYields(TString selection="");

  void setVariableBinning(Int_t nbins, Float_t * xbins){
    if(nbins<2||xbins==0)cout<<" bad variable bins"<<endl;
    nbinsVariable_=nbins;
    xbinsVariable_=xbins;
  }
  TH1D * getPlotHisto(TString hname){
    //cout<<"Making histo "<<hname<<endl;
    TH1D* h=0;
    if(nbins_>0) h=new TH1D(hname,hname,nbins_,xmin_,xmax_);
    else if(nbinsVariable_>0) h=new TH1D(hname,hname,nbinsVariable_,xbinsVariable_);
    else{ cout<<" histo binning not recognized"<<endl; return 0;}
    h->GetXaxis()->SetTitle(plotvar_);
    h->Sumw2();
    h->SetLineWidth(1);
    h->SetLineColor(1);
    return h;
  }

  Sample * findSample(TString sampleName){
    for( std::vector<Sample*>::const_iterator s=samples_.begin(); s!=samples_.end(); ++s)
      if( sampleName.CompareTo((*s)->GetName()) == 0){
	return *s;
      }  
    return NULL;
  }


  TH1D * getBackground(TString name);
  TH1D * getSignal(TString name);

  Float_t getTotalDataLumi(){
    float totalDataLumi=0;
    for( std::vector<Sample*>::const_iterator s=samples_.begin(); s!=samples_.end(); ++s)
      if((*s)->getDataType()=="Data")
	totalDataLumi+=(*s)->getLumi();
    //cout<<"Total Data lumi = "<<totalDataLumi<<endl;
    return totalDataLumi;
  }


  void makeDensityHisto(TH1D*h){
    for(Int_t b=1;b<=h->GetNbinsX();b++){
      h->SetBinContent(b,h->GetBinContent(b)/h->GetBinWidth(b));
      h->SetBinError(b,h->GetBinError(b)/h->GetBinWidth(b));//scale the error too
    }
  }


  //clean up
  void deleteSamples(){
    for(std::vector<Sample*>::const_iterator s=samples_.begin();s!=samples_.end();s++)
      delete *s;
    samples_.clear();
  }  


  //selections used for each plot made inside this class
  TString eventWeight_;
  TString selection_;

protected:
 
  TString plotvar_;
  Int_t nbins_;
  Float_t xmin_;
  Float_t xmax_;
   
  Int_t nbinsVariable_;
  Float_t* xbinsVariable_;

  TString outputpath_;

  TString lumisFile_;
  float getSampleLumi(TString sample);

  TString crossectionsFile_;
  float findCrossection(Sample * sample);

  std::vector<Sample*> samples_;   

  std::vector<TString> backgrounds_;
  std::vector<TString> backgroundSampleNames_;
  std::vector<int> backgroundColors_;
  std::vector<TString> backgroundTitles_;
 
  std::vector<TString> signals_;
  std::vector<TString> signalSampleNames_;
  std::vector<int> signalColors_;
  std::vector<TString> signalTitles_;
  std::vector<int> signalScaleFactors_;

  vector<TString> listDir(const char * path);
 
  void makePlot(TString filename,TH1D* hData, THStack * hStack, TString xlabel, TString ylabel,
		Float_t* legendcoords=0, TList* signalList=0);

  ClassDef(Plotter, 1);
};

#endif 
