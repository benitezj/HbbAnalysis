#include "Plotter.h"

// #include <memory>
#include <iostream>
#include <iomanip>
// #include <sys/stat.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>


#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TList.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TPaveText.h>

// #include <TROOT.h>
// #include <TSystem.h>
// #include <TTree.h>
// #include <TFile.h>
// #include <TH2F.h>

// #include <TF1.h>
// #include <TGraph.h>
// #include <TVector3.h>
// #include <TLorentzVector.h>

// #include <TVectorD.h>
// #include <TLatex.h>
// #include <TText.h>

// #include <TGraphAsymmErrors.h>


ClassImp(Plotter)

Plotter::Plotter(): TNamed("",""){}

Plotter::Plotter(const char * name, const char * title):
  TNamed(name,title),
  eventWeight_("1"),
  selection_("1"),
  plotvar_(""),
  nbins_(10),
  xmin_(0.),
  xmax_(1.),
  nbinsVariable_(0),
  xbinsVariable_(0),
  lumisFile_(""),
  crossectionsFile_("")
{

}

Plotter::~Plotter(){
}

float Plotter::getSampleLumi(TString sample){
  float lumi=0.;
  std::ifstream infile(lumisFile_.Data());
  std::string line;
  while (std::getline(infile, line)){
    //cout<<line<<endl;
    std::istringstream iss(line);
    float LUM;
    string name;
    iss >> LUM;
    iss >> name;
    //cout<<"="<<LUM<<"= ="<<name<<"="<<endl;
    if(sample.CompareTo(name.c_str()) == 0){ lumi=LUM; break;}
  }
  if(lumi==0.)
    cout<<"Plotter::getSampleLumi Warning : lumi for "<<sample<<" was not found or is 0 in "<<lumisFile_<<endl;

  return lumi/1000000.;
}


float Plotter::findCrossection(Sample * sample){
  
  float crossection=0.;
  std::ifstream infile(crossectionsFile_.Data());
  std::string line;
  while (std::getline(infile, line)){
    std::istringstream iss(line);
    int run;
    iss >> run;
    float crosFinal;
    iss >> crosFinal;

    if(run == sample->getRun()){
      crossection=crosFinal;
      break;
    }
  }
  if(crossection==0.)
    cout<<"Plotter::findCrossection Warning : crossection for "<<sample->GetTitle()<<" was not found or is 0 in "<<crossectionsFile_<<endl;

  return crossection;
}



void Plotter::addData(TString path,TString sample){
  float lumi=getSampleLumi(sample);
  if(lumi<=0.){
    cout<<sample<<" has bad lumi. Sample will be removed."<<endl;
    return;
  }
  
  Sample* Data = new Sample(sample,sample,path);
  Data->setDataType("Data");
  
  if(Data->getNFiles()==0){//DataType needs to be set 
    cout<<sample<<" has no files. Sample will be removed."<<endl;
    return;
  }

  Data->setSampleLumi(lumi);
  this->addSample(Data);
}


vector<TString> Plotter::listDir(const char * path){
  vector<TString> samples;
  TSystemDirectory dir(path,path);
  TList *files = dir.GetListOfFiles();
  if (files) {
    TSystemFile *file;    
    TIter next(files);
    while ((file=(TSystemFile*)next())) {
      TString fname = file->GetName();
      if (file->IsDirectory()) {
	samples.push_back(fname);
      }
    }
  }

  return samples;
}


void Plotter::addAllData(TString path){
  vector<TString> samples = listDir(path.Data());
  for( std::vector<TString>::const_iterator s=samples.begin(); s!=samples.end(); ++s){
    if((*s).BeginsWith("data")){
      addData(path,*s);
    }
  }
}

bool Plotter::scaleSamplesLumi(){

  cout<<"---------> Scaling all MC samples to Lumi "<<endl;
  for( std::vector<Sample*>::const_iterator s=samples_.begin(); s!=samples_.end(); ++s)
    (*s)->resetScale();

  float totalDataLumi=getTotalDataLumi();
  cout<<"totalDataLumi = "<<totalDataLumi<<endl;

  for( std::vector<Sample*>::const_iterator s=samples_.begin(); s!=samples_.end(); ++s)
    if((*s)->getDataType()=="MC" 
       ){
      //cout<<(*s)->GetName()<<" lumi scale "<<totalDataLumi/(*s)->getLumi()<<endl;
      if((*s)->getLumi()>0.){
	cout<<"Scaling "<<(*s)->GetName()<<"  by "<<totalDataLumi/(*s)->getLumi()<<endl;
	(*s)->scale(totalDataLumi/(*s)->getLumi());
      } else{
	cout<<"Plotter::scaleSamplesLumi : "<<(*s)->GetName()<<" has a negative luminosity"<<endl;
	(*s)->scale(0.);
      }
    }


  return 1;
}


TH1D* Plotter::getSample(TString samplename){
  TH1D* h=getPlotHisto(samplename);
  TCut sel=TCut(eventWeight_)*TCut(selection_);//not have to use *, + will give an integer for the final event weight
  //cout<<sel<<endl;
  for( std::vector<Sample*>::const_iterator s=samples_.begin(); s!=samples_.end(); ++s)
    if(samplename.CompareTo((*s)->GetName()) == 0){
      (*s)->fillHisto(h,plotvar_,sel);
      return h;
    }  
  cout<<"Plotter::getSample : '"<<samplename<<"' not found"<<endl;
  return 0;
}

TH1D* Plotter::getTotalData(){
  TH1D* h=getPlotHisto("hData");
  for( std::vector<Sample*>::const_iterator s=samples_.begin(); s!=samples_.end(); ++s)
    if((*s)->getDataType()=="Data"){
      TH1D*hd=getSample((*s)->GetName());
      if(hd){
	h->Add(hd);
	delete hd;
      }
    }
  return h;
}

bool Plotter::printRawYields(TString selection){
  
  for( std::vector<Sample*>::const_iterator s=samples_.begin(); s!=samples_.end(); ++s){
    TH1D*h=(*s)->getHistoNtpFile("1",1,0,2,selection.Data());
    cout<<h->GetName()<<" "<<(int)(h->Integral())<<endl;
    delete h;
  }
  
  return 1;
}


TH1D * Plotter::getBackground(TString name){
  TH1D* H=0;
  int i=0;
  for( std::vector<TString>::const_iterator bkg=backgrounds_.begin(); bkg!=backgrounds_.end(); ++bkg){
    if(backgrounds_[i].CompareTo(name.Data()) == 0){
      H=getPlotHisto(name+"Bkg");
      H->SetTitle(backgroundTitles_[i]);
      H->SetFillColor(backgroundColors_[i]);
      
      //look for the samples that compose this background
      cout<<name<<": ";
      vector<string> samples = split(backgroundSampleNames_[i].Data(),',');
      for( std::vector<string>::const_iterator s=samples.begin(); s!=samples.end(); ++s){
	TH1D* h = getSample((*s).c_str());
	if(!h){cout<<"Plotter::getBackground :  sample "<<(*s)<<"  not found"<<endl; return 0;}
	H->Add(h);	
	cout<<*s<<" "<<(int)(h->Integral())<<",";
	delete h;
      }
      cout<<" TOTAL = "<<(int)(H->Integral())<<endl;
    }

    i++;
  }
  if(H==0){cout<<"Plotter::getBackground : "<<name<<" not found"<<endl; return 0;}
  return H;
}


TH1D * Plotter::getSignal(TString name){
  TH1D* H=0;
  int i=0;
  for( std::vector<TString>::const_iterator sig=signals_.begin(); sig!=signals_.end(); ++sig){
    if(signals_[i].CompareTo(name.Data()) == 0){
      H=getPlotHisto(name+"Sig");
      H->SetTitle(signalTitles_[i]
		  + (signalScaleFactors_[i]>1 ? TString("(x")+(long)signalScaleFactors_[i]+")" : ""));
      H->SetFillColor(signalColors_[i]);
      
      cout<<name<<": ";
      vector<string> samples = split(signalSampleNames_[i].Data(),',');
      for( std::vector<string>::const_iterator s=samples.begin(); s!=samples.end(); ++s){
	TH1D* h = getSample((*s).c_str());
	if(!h){cout<<"Plotter::getSignal :  sample "<<(*s)<<"  not found"<<endl; return 0;}
	h->Scale(signalScaleFactors_[i]);//Note this makes getSignal() different from getBackground()
	H->Add(h);	
	cout<<*s<<" "<<(int)(h->Integral())<<",";
	delete h;
      }
      cout<<" TOTAL = "<<(int)(H->Integral())<<endl;
    }

    i++;
  }
  if(H==0){cout<<"Plotter::getSignal : "<<name<<" not found"<<endl; return 0;}
  return H;
}



void Plotter::plot(TString variable, Int_t nbins, Float_t xmin, Float_t xmax, TString sel,
		   TString xlabel, TString ylabel,Float_t* legendcoords, TString filetag, bool signal){

  plotvar_=variable;
  nbins_=nbins;
  xmin_=xmin;
  xmax_=xmax;
  selection_=sel;
 
  TH1D* hData=getTotalData();
  if(!hData){cout<<"No Data histo."<<endl; return;}
  hData->SetName(TString("hData")+filetag);

  ///Backgrounds
  THStack hBkgStack("hBkgStack","hBkgStack");//dont't set any of the regular histogram properties on the THStack, it will crash.
  for( std::vector<TString>::const_iterator bkg=backgrounds_.begin(); bkg!=backgrounds_.end(); ++bkg){
    TH1D*H=getBackground((*bkg).Data());
    if(!H) return;
    H->SetName((*bkg)+"_"+filetag);
    hBkgStack.Add(H,"hist");
  }

  //Signals
  TList* SignalList=0;
  if(signal){
    SignalList=new TList();
    for( std::vector<TString>::const_iterator sig=signals_.begin(); sig!=signals_.end(); ++sig){
      TH1D* H=getSignal((*sig).Data());
      if(!H) return;
      H->SetName((*sig)+"_"+filetag);
      SignalList->Add(H,"hist");
    }
  }


  makePlot(outputpath_+"/"+filetag,hData,&hBkgStack,xlabel,ylabel,legendcoords,SignalList);
}


void Plotter::makePlot(TString filename, TH1D* Data, THStack * BkgStack, TString xlabel, TString ylabel,
		       Float_t* legendcoords,TList* signalList){

  TPaveText titlePaveText(.40,.90,.92,.999,"NDC");
  titlePaveText.SetBorderSize(   0 );
  titlePaveText.SetFillStyle(    0 );
  titlePaveText.SetTextAlign(   12 );
  titlePaveText.SetTextSize ( 0.034 ); //do not increase size power on fb will get separated
  titlePaveText.SetTextColor(    1 );
  titlePaveText.SetTextFont (   62 );

  char title[100];
  sprintf(title,GetTitle(),getTotalDataLumi()/1000.);
  titlePaveText.AddText(title);

  TLegend legend;
  legend.SetFillStyle (0);
  legend.SetFillColor (0);
  legend.SetBorderSize(0);
  legend.SetTextSize(.04);


  cout<<"Total Data "<<(int)(Data->Integral())<<endl; 
  Data->SetMarkerSize(1);
  legend.AddEntry(Data,"Observed","P");  

  //create a histo with the total Background
  TH1D* hBkg=getPlotHisto("hBkg");
  hBkg->SetFillColor(0);
  hBkg->SetLineColor(1);
  TList* histList= BkgStack->GetHists();
  for(Int_t i=0;i<histList->GetSize();i++){
    hBkg->Add((TH1D*)(histList->At(i)));
    legend.AddEntry((TH1D*)(histList->At(i)),((TH1D*)(histList->At(i)))->GetTitle(),"F");
  }
  cout<<"Total Bkg "<<(int)(hBkg->Integral())<<endl;  


  //Add the total background to the signals so they show on top
  if(signalList)
    for(Int_t i=0;i<signalList->GetSize();i++){
      ((TH1D*)(signalList->At(i)))->Add(hBkg);
      legend.AddEntry((TH1D*)(signalList->At(i)),((TH1D*)(signalList->At(i)))->GetTitle(),"F");
    }

  TCanvas C("C",filename);  

  C.Clear();

  Data->SetTitle("");
  float maxyData=(Data->GetMaximum()+Data->GetBinError(Data->GetMaximumBin()))*1.25;
  float maxyMC=(hBkg->GetMaximum()+hBkg->GetBinError(hBkg->GetMaximumBin()))*1.25;
  Data->GetYaxis()->SetRangeUser(0,maxyData>maxyMC ? maxyData : maxyMC);
  Data->SetStats(0);
  Data->GetXaxis()->SetTitle(xlabel);
  Data->GetYaxis()->SetTitle(ylabel);

  Data->Draw("hist pe");
  if(signalList)
    for(Int_t i=0;i<signalList->GetSize();i++){
      ((TH1D*)(signalList->At(i)))->Draw("histsame");
    }
  BkgStack->Draw("hist same");  
  Data->Draw("hist pe same");//bring Data points back to front
  hBkg->Draw("histsame");//draw outline of MC on top of data        
  BkgStack->GetHistogram()->Draw("same");//bring axes back to front 

  if(legendcoords){
    legend.SetX1NDC(legendcoords[0]);
    legend.SetY1NDC(legendcoords[1]);
    legend.SetX2NDC(legendcoords[2]);
    legend.SetY2NDC(legendcoords[3]);
  }
  legend.Draw();

  titlePaveText.Draw(); //Add the title

  C.RedrawAxis();
  C.Update();
  C.Print(filename+".png");  

  Data->GetYaxis()->SetRangeUser(1,Data->GetMaximum()*100);
  C.Update();
  C.SetLogy(1);
  C.Print(filename+".log.png");   
  C.SetLogy(0);

  
  TLine line;


  //make the ratio plot
  TH1D* hRatio=getPlotHisto("hRatio");
  hRatio->Add(Data);
  hRatio->Divide(hBkg);
  
  TPad * pad1=new TPad("pad1","",0,0.2,1,1);
  TPad * pad2=new TPad("pad2","",0,0,1,0.2);
  
  pad1->cd();
  Data->GetYaxis()->SetRangeUser(0,maxyData>maxyMC ? maxyData : maxyMC);
  Data->Draw("hist pe");
  BkgStack->Draw("hist same");  
  Data->Draw("hist pe same");
  hBkg->Draw("histsame");
  BkgStack->GetHistogram()->Draw("same");
  legend.Draw();
  titlePaveText.Draw();
  
  pad2->cd();
  hRatio->SetStats(0);
  hRatio->SetTitle("");
  hRatio->GetYaxis()->SetTitle("Data/MC");
  hRatio->GetXaxis()->SetTitle("");
  hRatio->GetYaxis()->SetNdivisions(5);
  hRatio->GetYaxis()->SetLabelSize(0.15);
  hRatio->GetYaxis()->SetTitleSize(0.2);
  hRatio->GetYaxis()->SetTitleOffset(0.20);
  hRatio->GetXaxis()->SetNdivisions(-1);
  hRatio->GetXaxis()->SetLabelSize(0.0001);
  hRatio->GetYaxis()->SetRangeUser(0.8,1.2);
  hRatio->Draw("hist pe");
  line.DrawLine(xmin_,1,xmax_,1);
  
  C.Clear();
  pad1->Draw();
  pad2->Draw();
  C.Print(filename+".ratio.png");   



  // //make the difference plot  
  // TH1D* hDiff=getPlotHisto("hDiff");

  // //hDiff->SetStats(0);
  // hDiff->GetXaxis()->SetTitle(Data->GetXaxis()->GetTitle());
  // hDiff->GetYaxis()->SetTitle("Data - MC");
  // hDiff->Add(Data);
  // hDiff->Add(hBkg,-1);
  // float max=fabs(hDiff->GetMaximum());
  // if(fabs(max)<fabs(hDiff->GetMinimum())) max = fabs(hDiff->GetMinimum());
  // hDiff->GetYaxis()->SetRangeUser(-max,max);
  // C.Clear();
  // hDiff->Draw("hist pe");
  // line.DrawLine(xmin_,0,xmax_,0);
  // C.Print(filename+".ps");  
  //delete hDiff;
  

  for(Int_t i=0;i<histList->GetSize();i++)
    delete histList->At(i);

  delete hBkg;
  delete hRatio; 
}


