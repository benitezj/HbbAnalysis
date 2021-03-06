#include "/afs/cern.ch/user/b/benitezj/software/macros/plotOnCmdLine.C"

void plotCmdLineCxAOD(TString file=""){

  TFile F((const char*)file);
  gROOT->cd();
  TTree*T=(TTree*)F.Get("CollectionTree");

  //Event info
  TH1F hNVtx("hNVtx","N Vtx",25,0,25);
  T->Draw("EventInfo___NominalAuxDyn.NVtx3Trks>>hNVtx");
  plotOnCmdLine(&hNVtx);

  TH1F hVtxZ("hVtxZ","Prim Vtx Z",40,-200,200);
  T->Draw("EventInfo___NominalAuxDyn.zPV>>hVtxZ");
  plotOnCmdLine(&hVtxZ);
  
  //Muons
  TH1F hMuonPt("hMuonPt","Muon pT",50,0,100e3);
  T->Draw("Muons___NominalAuxDyn.pt>>hMuonPt");
  plotOnCmdLine(&hMuonPt);

  TH1F hMuonEta("hMuonEta","Muon Eta",40,-5,5);
  T->Draw("Muons___NominalAuxDyn.eta>>hMuonEta");
  plotOnCmdLine(&hMuonEta);
  
  ///Electrons
  TH1F hElectronPt("hElectronPt","Electron pT",50,0,100e3);
  T->Draw("ElectronCollection___NominalAuxDyn.pt>>hElectronPt");
  plotOnCmdLine(&hElectronPt);

  TH1F hElectronEta("hElectronEta","Electron Eta",40,-5,5);
  T->Draw("ElectronCollection___NominalAuxDyn.eta>>hElectronEta");
  plotOnCmdLine(&hElectronEta);

  
  //Jets
  TH1F hJetPt("hJetPt","Jet pT",50,0,100e3);
  T->Draw("AntiKt4EMTopoJets___NominalAuxDyn.pt>>hJetPt");
  plotOnCmdLine(&hJetPt);

  TH1F hJetEta("hJetEta","Jet Eta",40,-5,5);
  T->Draw("AntiKt4EMTopoJets___NominalAuxDyn.eta>>hJetEta");
  plotOnCmdLine(&hJetEta);

  ///MET 
  TH1F hMETPt("hMETPt","MET",50,0,100e3);
  T->Draw("MET_RefFinal___NominalAux.sumet>>hMETPt");
  plotOnCmdLine(&hMETPt);

//  TH1F hMETPhi("hMETPhi","MET Phi",40,-4,4);
//  T->Draw("MET_RefFinal___NominalAux.phi>>hMETPhi");
//  cout<<"MET phi "<<hMETPhi.Integral()<<endl;
//  plotOnCmdLine(&hMETPhi);

  

  
  gROOT->ProcessLine(".q");
}
