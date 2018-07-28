#include "ZmmPlotter.h"

ClassImp(ZmmPlotter)

ZmmPlotter::ZmmPlotter(): Plotter("",""){}

ZmmPlotter::ZmmPlotter(const char * name, const char * title):
  Plotter(name,title)
{

}

ZmmPlotter::~ZmmPlotter(){}


// void ZmmPlotter::plot(TString variable, Int_t nbins, Float_t xmin, Float_t xmax, TString sel, 
// 		      TString xlabel, TString ylabel,Float_t* legendcoords, TString filetag){

//   plotvar_=variable;
//   nbins_=nbins;
//   xmin_=xmin;
//   xmax_=xmax;
//   selection_=TCut(sel.Data());

//   ////Total Data
//   TH1F* hData=getTotalData();
//   hData->SetName(TString("hData")+filetag);
//   if(!hData){cout<<" Total Data not determined "<<endl; return;}


//   THStack hMCStack("hBkgStack","BkgStack");

//   ///Z->mm
//   TH1F*hZmm=getBackground("Zmm");
//   if(hZmm){
//     hZmm->SetName(TString("Zmm_")+filetag);
//     hMCStack.Add(hZmm,"hist");
//   }else cout<<"Background Zmm not found"<<endl;

//   // TH1F*hZmm_c=getBackground("Zmm_c");
//   // if(hZmm_c){
//   //   hZmm_c->SetName(TString("Zmm_c_")+filetag);
//   //   hMCStack.Add(hZmm_c,"hist");
//   // }else cout<<"Background Zmm_c not found"<<endl;

//   // TH1F*hZmm_b=getBackground("Zmm_b");
//   // if(hZmm_b){
//   //   hZmm_b->SetName(TString("Zmm_b_")+filetag);
//   //   hMCStack.Add(hZmm_b,"hist");
//   // }else cout<<"Background Zmm_b not found"<<endl;

//   TH1F*hWmunu=getBackground("Wmunu");
//   if(hWmunu){
//     hWmunu->SetName(TString("Wmunu_")+filetag);
//     hMCStack.Add(hWmunu,"hist");
//   }else cout<<"Background Wmunu not found"<<endl;

//   TH1F*htt=getBackground("ttbar");
//   if(htt){
//     htt->SetName(TString("ttbar_")+filetag);
//     hMCStack.Add(htt,"hist");
//   }else cout<<"Background ttbar not found"<<endl;


//   makePlot(outputpath_+"/"+filetag,hData,&hMCStack,xlabel,ylabel,legendcoords);
// }

