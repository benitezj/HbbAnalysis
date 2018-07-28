#include "/afs/cern.ch/user/b/benitezj/software/macros/plotOnCmdLine.C"

void plotPtEtaPhi(TTree*T,TString name,TCut sel="",TString index=""){

  TString op=">>";
  if(index.CompareTo("")!=0) 
    op=TString("[")+index+"]"+op;

  cout<<"******************name:"<<name<<",     sel:"<<(char*)sel<<",    index:"<<index<<"  *******************************************"<<endl;


  ///Disable as index may be chosen
  // TH1F hN("hN",TString("N ") +name + " per event",24,0,6);
  // T->Draw(TString("n")+name+op+"hN",sel);
  // plotOnCmdLine(&hN);

  TH1F hPt("hPt",name + " pT",50,0,100e3);
  T->Draw(name+"_pt"+op+"hPt",sel);
  plotOnCmdLine(&hPt);

  TH1F hEta("hEta",name + " eta",40,-5,5);
  T->Draw(name+"_eta"+op+"hEta",sel);
  plotOnCmdLine(&hEta);

  TH1F hPhi("hPhi",name + " phi",40,-5,5);
  T->Draw(name+"_phi"+op+"hPhi",sel);
  plotOnCmdLine(&hPhi);
 
}

