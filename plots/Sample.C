#include "Sample.h"
#include <fstream>
#include <sstream>

Sample::Sample():
  TNamed("Sample","Sample")
{}

Sample::Sample(const char * name, const char * title, const char * path):
  TNamed(name,title),
  crossection_(1.0),
  lumi_(0.0),
  genEvents_(0.),
  genEventsSumW_(0.),
  eventWeight_("1"),
  path_(path),
  nNames_(0),
  filename_("tuple"),
  ntpname_("tuple"),
  ntpChain_(NULL),
  NMAXFILES_(10000),
  NMAXNONEXISTENT_(5),
  dataType_("MC"),
  title_(""),
  color_(0),
  lcolor_(0),
  lstyle_(0),
  normFactor_(1),
  init_(0),
  signalMass_(0.)
{

  if(TString(title).CompareTo("")==0){
    cout<<"Invalid sample: name="<<name<<", title="<<title<<", path="<<path<<endl;
    exit(0);
  }
  
  //add the first directory containing ntuples
  addFileNames[nNames_]=path_+"/"+title; nNames_++; 

  //Determine the run number
  vector<string> tokens = split(title,'.');
  run_=atoi(tokens[1].c_str());
  dataSet_=tokens[2];
  //cout<<run_<<" "<<dataSet_<<endl;

}

Sample::~Sample(){
   if(ntpChain_!=NULL)  delete ntpChain_;
}



void Sample::fillHisto(TH1* h, TString xvar, TCut selection){
  if(!ntpChain_) openNtpFile();

  if(ntpChain_->GetNtrees()>0){
    ntpChain_->Draw(xvar+">>"+h->GetName(),TCut(eventWeight_)*selection);
    h->Scale(getNorm());
  }

}


TH1D* Sample::getHistoNtpFile(TString xvar,Int_t xnbins,Float_t xmin,Float_t xmax,TCut selection){
  if(!ntpChain_) openNtpFile();    
  TH1D* h=new TH1D(GetName(),"",xnbins,xmin,xmax);
  setHistoAttr(h);
  h->GetXaxis()->SetTitle(xvar);
  h->Sumw2();
  fillHisto(h,xvar,selection);
  return h;
}

TH1D * Sample::getHistoNtpFile(TString xvar,Int_t Nbins, Float_t * Xbins, TCut selection){
  if(!ntpChain_) openNtpFile();
  TH1D* h=new TH1D(GetName(),"",Nbins,Xbins);
  setHistoAttr(h);
  h->GetXaxis()->SetTitle(xvar);
  h->Sumw2();
  fillHisto(h,xvar,selection);
  return h;
}


TH2D* Sample::getHistoNtpFile(TString xvar, Int_t xnbins, Float_t xmin, Float_t xmax, TString yvar, Int_t ynbins, Float_t ymin, Float_t ymax, TCut selection){
  if(!ntpChain_) openNtpFile();
  TH2D* h=new TH2D(GetName(),"",xnbins,xmin,xmax,ynbins,ymin,ymax);
  setHistoAttr(h);
  h->GetXaxis()->SetTitle(xvar);
  h->GetYaxis()->SetTitle(yvar);
  h->Sumw2();
  fillHisto(h,yvar+":"+xvar,selection);
  return h;
}

int Sample::getNProcEvents(TString logfile){
  int Nevents=0;

  ifstream InputStream;
  InputStream.open((const char*)(logfile));
  if(!InputStream.is_open()){
    cout<<"Sample::getNProcEvents Error: log file not found:"<<endl;
    cout<<logfile<<endl;
    return -1;
  }
  
  //skip to the end of the file
  //-note MC has longer end of log file than Data due to vertex weight modules
  //-if one uses too large number it gets stuck with files which did not process any events
  InputStream.seekg(0,ios_base::end);//go to end
  //cout<<logfile<<" "<<InputStream.tellg()<<endl;
  if(InputStream.tellg()<1000){
    cout<<"Sample::getNProcEvents Error: log file size is too small:"<<endl;
    cout<<logfile<<endl;
    return -1;
  }
  //if(InputStream.tellg() > 22000 ) InputStream.seekg(-22000 , ios_base::end);
  if(InputStream.tellg() > 100000 ) InputStream.seekg(-100000 , ios_base::end);
  else InputStream.seekg(0, ios_base::beg);


  TString logreport;
  while(Nevents==0&&!InputStream.eof()){
    InputStream>>logreport;
    if(logreport=="END") break;
    //Look for this in the log file:
    //inputCounter = 2078831
    if(logreport=="inputCounter"){
      InputStream>>logreport;
      InputStream>>Nevents;
      break;
    }


  }

  if(Nevents==0){//Note that Nevents can be 0 for a good job
    cout<<" Sample::getNProcEvents Warning:  summary reports 0 events processed"<<endl;
    cout<<logfile<<endl;
  }

  //cout<<" ***** "<<logfile<<"   "<<Nevents<<endl;
  return Nevents;
}

float Sample::getSumOfWeights(TFile * rootFile){
  float Nevents=0.;
  if(!rootFile){
    cout<<"getSumOfWeights(): No input file"<<endl;
    return 0.;
  }
  
  TH1* H=(TH1*)rootFile->Get("MetaData_EventCount");
  if(!H){
    cout<<"getSumOfWeights(): No input MetaData_EventCount histogram"<<endl;
    return 0.;
  }
  Nevents =  H->GetBinContent(8);
  if( Nevents<=0){
    cout<<"getSumOfWeights: Warning: sum of event weights is <=0"<<endl;
    return 0.;
  }


  return Nevents;
}


bool Sample::openNtpFile(){
  if(ntpChain_) return 0;

  ntpChain_=new TChain(ntpname_.Data());

  genEvents_=0.;
  Int_t nonExistentCounter=0;
  for(Int_t n=0;n<nNames_;n++){
    nonExistentCounter=0;
    int nadded=0;
    for(Int_t i=0;i<=NMAXFILES_ ;i++){

      if(nonExistentCounter==NMAXNONEXISTENT_){
	break;//go to the end of the input files
      }

      TString fname=TString(addFileNames[n])+"/"+filename_+"_"+(long)i;

      struct stat st;
      if(stat((fname+".root").Data(),&st) != 0){
	if(i==0) cout<<(fname+".root")<<" Not found"<<endl;
	nonExistentCounter++; 
	continue;
      }
   
      TFile file((fname+".root").Data(),"read");
      if(file.IsZombie()){
	cout<<(fname+".root")<<" is Zombie"<<endl;
	continue;
      }
      if(!file.GetListOfKeys()){
	cout<<(fname+".root")<<" has no Keys"<<endl;
	continue;
      }
      if(file.GetListOfKeys()->GetSize()==0){
	cout<<(fname+".root")<<" KeysSize = 0"<<endl;
	continue;            
      }

      genEvents_ += getNProcEvents((fname+".log").Data());
      if(dataType_!="Data") //fill sum of input weights
	genEventsSumW_ += getSumOfWeights(&file);

      ntpChain_->Add((fname+".root").Data());    
      
      nadded++;

      if(i==NMAXFILES_){
	cout<<"Number of files added for sample "<<GetName()<<" is at max "<<NMAXFILES_<<endl;
	return 0;
      }

    }
    
    cout<<addFileNames[n]<<" : "<<nadded<<" root files"<<endl;
    
  }
  gROOT->cd();
  
  if(ntpChain_->GetNtrees()==0){
    cout<<GetName()<<" 0 files chained. "<<endl;
    return 0;
  }

  cout<<GetName()
      <<" : files = "<<ntpChain_->GetNtrees()
      <<" , nProcEv ="<<genEvents_ 
      <<" , entries = "<<ntpChain_->GetEntries()
      <<endl;
  
  return 1;
}


TH1* Sample::getPileUp(){
  return getHisto("HPileUp");
}


TH1* Sample::getHisto(TString histoName, int nbins, float xmin, float xmax){

  if(!ntpChain_) openNtpFile();

  TList* Files = (TList*) ntpChain_->GetListOfFiles();
  if(Files->GetEntries()==0) return 0;

  TFile F0(Files->At(0)->GetTitle(),"READ");
  gROOT->cd();
  if(!F0.Get(histoName.Data())){cout<<"Sample::getHisto: "<<histoName<<"  not found"<<endl; return 0;}
  TH1 * H = (TH1*)(F0.Get(histoName.Data())) ->Clone(histoName.Data());  
  
  for(int i=1;i<Files->GetEntries();i++){
    TFile F(Files->At(i)->GetTitle(),"READ");
    H->Add((TH1*)(F.Get(histoName.Data())));
  }
  
  /////Rebin
  if(nbins>0){

    //check the original has an even number of bins
    if(H->GetXaxis()->GetNbins() % 2 != 0){
      cout<<"Sample::getHisto : Original histo does not have even number of bins :"<<H->GetXaxis()->GetNbins()<<endl;
      return 0;
    }


    float newBinSize=(xmax-xmin)/nbins;
    int rebin = int(newBinSize/H->GetBinWidth(1));

    //Check the requested rebinning is an even number
    if( rebin % 2 != 0 && rebin !=1 ){
      cout<<"Sample::getHisto : requested rebinning factor is not an even number:"<<rebin<<endl;
      return 0;
    }

    //Check the requested bin size is integer multiple of original 
    if(float(rebin) != float(newBinSize / H->GetBinWidth(1)) ){
      cout<<"Sample::getHisto : New bin size must be an integer multiple of the original."
	  <<", New = "<<newBinSize
	  <<", Original = "<<H->GetBinWidth(1)
	  <<endl;
      return 0;
    }

    
    //check the new limits are inside the old limits
    if(xmin<H->GetXaxis()->GetXmin() || xmax > H->GetXaxis()->GetXmax()){
      cout<<"Sample::getHisto : New histo limits are outside the original:"<<H->GetXaxis()->GetXmin()<<","<<H->GetXaxis()->GetXmax()<<endl;
      return 0;
    }

    //Rebin the original
    H->Rebin(rebin);

    //Copy onto a new histogram
    TH1D * Hrebin = new TH1D(histoName+"Rebin",histoName.Data(),nbins,xmin,xmax);
    for(int i=1;i<=H->GetXaxis()->GetNbins();i++)
      if(H->GetBinCenter(i) == Hrebin->GetBinCenter(1) ) {
	for(int b=0;b<nbins;b++)
	  Hrebin->SetBinContent(b+1,H->GetBinContent(i+b));
	break;
      }
      
    delete H;
    H=Hrebin;
  }

  return H;
}


TGraphErrors * Sample::getCutFlow(){
  TGraphErrors * graph=new TGraphErrors();
  
  //system(TString("cat ")+addFileNames[0]+"/counters.txt");

  //Currently only works if not adding additional root files
  std::ifstream infile(addFileNames[0]+"/counters.txt");
  std::string line;

  //Get the input events
  std::getline(infile, line);
  std::istringstream iss(line);
  string nameInput;
  iss >> nameInput;
  string equalInput;
  iss >> equalInput;
  float counterInput;
  iss >> counterInput;

  graph->SetPoint(0,0,1);
  graph->SetPointError(0,0,0);

  int N=1;
  while (std::getline(infile, line)){
    //cout<<line<<endl;
    std::istringstream iss(line);
    string name;
    iss >> name;
    string equal;
    iss >> equal;
    int counter=0;
    iss >> counter;
    //cout<<name<<equal<<counter<<endl;


    float eff=counter/counterInput;
    cout<<eff<<" "<<name<<endl;

    graph->SetPoint(N,N,eff);
    graph->SetPointError(N,0,0);

    N++;
  }
  
  //post processing cuts
  for(int i=0;i<skimCounter;i++) 
    if(!skim(skimSelection[i])) return 0;
    else {
      //cout<<skimName[i]<<endl;
      int counter = ntpChain_->GetEntries();
      float eff=counter/counterInput;
      cout<<eff<<" "<<skimName[i]<<endl;
      graph->SetPoint(N,N,eff);
      graph->SetPointError(N,0,0);
      N++;
    }
  
  graph->GetYaxis()->SetTitle("Efficiency");
  graph->GetXaxis()->SetTitle("Selection");
  return graph;
}
