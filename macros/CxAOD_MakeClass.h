//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Nov 15 23:07:33 2014 by ROOT version 5.34/22
// from TTree CollectionTree/xAOD event tree
// found on file: sampleCxAOD/data-outputLabel/AOD.root
//////////////////////////////////////////////////////////

#ifndef CollectionTree_h
#define CollectionTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector.dll"
#include "/var/build/releases/cand1/x86_64-slc6-gcc48-opt/projects/ROOT-5.34.22/src/ROOT/5.34.22/cint/cint/lib/prec_stl/vector"

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxEventInfo___NominalAux = 1;
   const Int_t kMaxTruthParticle___NominalAux = 1;
   const Int_t kMaxMuons___NominalAux = 1;
   const Int_t kMaxMuons___MUONS_ID__1downAux = 1;
   const Int_t kMaxMuons___MUONS_ID__1upAux = 1;
   const Int_t kMaxMuons___MUONS_MS__1downAux = 1;
   const Int_t kMaxMuons___MUONS_MS__1upAux = 1;
   const Int_t kMaxMuons___MUONS_SCALE__1downAux = 1;
   const Int_t kMaxMuons___MUONS_SCALE__1upAux = 1;
   const Int_t kMaxMuons___OriginalAux = 1;
   const Int_t kMaxElectronCollection___NominalAux = 1;
   const Int_t kMaxElectronCollection___EG_SCALE_ALL__1downAux = 1;
   const Int_t kMaxElectronCollection___EG_SCALE_ALL__1upAux = 1;
   const Int_t kMaxElectronCollection___OriginalAux = 1;
   const Int_t kMaxAntiKt4EMTopoJets___NominalAux = 1;
   const Int_t kMaxAntiKt4EMTopoJets___OriginalAux = 1;
   const Int_t kMaxCamKt12LCTopoJets___NominalAux = 1;
   const Int_t kMaxCamKt12LCTopoJets___OriginalAux = 1;
   const Int_t kMaxMET_RefFinal___NominalAux = 1;

class CollectionTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   xAOD::EventInfo_v1 *EventInfo___Nominal;
 //xAOD::AuxInfoBase *EventInfo___NominalAux_;
   string          EventInfo___NominalAux_m_name;
   Int_t           EventInfo___NominalAuxDyn_isMC;
   Float_t         EventInfo___NominalAuxDyn_MCEventWeight;
   Float_t         EventInfo___NominalAuxDyn_zPV;
   Int_t           EventInfo___NominalAuxDyn_NVtx3Trks;
   UInt_t          EventInfo___NominalAuxDyn_runNumber;
   ULong64_t       EventInfo___NominalAuxDyn_eventNumber;
   UInt_t          EventInfo___NominalAuxDyn_mcChannelNumber;
   ULong64_t       EventInfo___NominalAuxDyn_mcEventNumber;
   Float_t         EventInfo___NominalAuxDyn_averageInteractionsPerCrossing;
   DataVector<xAOD::TruthParticle_v1> *TruthParticle___Nominal;
 //xAOD::AuxContainerBase *TruthParticle___NominalAux_;
   string          TruthParticle___NominalAux_m_name;
   vector<float>   *TruthParticle___NominalAuxDyn_m;
   vector<float>   *TruthParticle___NominalAuxDyn_px;
   vector<int>     *TruthParticle___NominalAuxDyn_partIndex;
   vector<int>     *TruthParticle___NominalAuxDyn_pdgId;
   vector<float>   *TruthParticle___NominalAuxDyn_py;
   vector<int>     *TruthParticle___NominalAuxDyn_barcode;
   vector<float>   *TruthParticle___NominalAuxDyn_pz;
   vector<int>     *TruthParticle___NominalAuxDyn_status;
   vector<float>   *TruthParticle___NominalAuxDyn_e;
   DataVector<xAOD::Muon_v1> *Muons___Nominal;
 //xAOD::AuxContainerBase *Muons___NominalAux_;
   string          Muons___NominalAux_m_name;
   DataVector<xAOD::Muon_v1> *Muons___MUONS_ID__1down;
 //xAOD::ShallowAuxContainer *Muons___MUONS_ID__1downAux_;
   DataLink<SG::IConstAuxStore> Muons___MUONS_ID__1downAux_m_parentLink;
   DataVector<xAOD::Muon_v1> *Muons___MUONS_ID__1up;
 //xAOD::ShallowAuxContainer *Muons___MUONS_ID__1upAux_;
   DataLink<SG::IConstAuxStore> Muons___MUONS_ID__1upAux_m_parentLink;
   DataVector<xAOD::Muon_v1> *Muons___MUONS_MS__1down;
 //xAOD::ShallowAuxContainer *Muons___MUONS_MS__1downAux_;
   DataLink<SG::IConstAuxStore> Muons___MUONS_MS__1downAux_m_parentLink;
   DataVector<xAOD::Muon_v1> *Muons___MUONS_MS__1up;
 //xAOD::ShallowAuxContainer *Muons___MUONS_MS__1upAux_;
   DataLink<SG::IConstAuxStore> Muons___MUONS_MS__1upAux_m_parentLink;
   DataVector<xAOD::Muon_v1> *Muons___MUONS_SCALE__1down;
 //xAOD::ShallowAuxContainer *Muons___MUONS_SCALE__1downAux_;
   DataLink<SG::IConstAuxStore> Muons___MUONS_SCALE__1downAux_m_parentLink;
   DataVector<xAOD::Muon_v1> *Muons___MUONS_SCALE__1up;
 //xAOD::ShallowAuxContainer *Muons___MUONS_SCALE__1upAux_;
   DataLink<SG::IConstAuxStore> Muons___MUONS_SCALE__1upAux_m_parentLink;
   DataVector<xAOD::Muon_v1> *Muons___Original;
 //xAOD::ShallowAuxContainer *Muons___OriginalAux_;
   DataLink<SG::IConstAuxStore> Muons___OriginalAux_m_parentLink;
   DataVector<xAOD::Electron_v1> *ElectronCollection___Nominal;
 //xAOD::AuxContainerBase *ElectronCollection___NominalAux_;
   string          ElectronCollection___NominalAux_m_name;
   DataVector<xAOD::Electron_v1> *ElectronCollection___EG_SCALE_ALL__1down;
 //xAOD::ShallowAuxContainer *ElectronCollection___EG_SCALE_ALL__1downAux_;
   DataLink<SG::IConstAuxStore> ElectronCollection___EG_SCALE_ALL__1downAux_m_parentLink;
   DataVector<xAOD::Electron_v1> *ElectronCollection___EG_SCALE_ALL__1up;
 //xAOD::ShallowAuxContainer *ElectronCollection___EG_SCALE_ALL__1upAux_;
   DataLink<SG::IConstAuxStore> ElectronCollection___EG_SCALE_ALL__1upAux_m_parentLink;
   DataVector<xAOD::Electron_v1> *ElectronCollection___Original;
 //xAOD::ShallowAuxContainer *ElectronCollection___OriginalAux_;
   DataLink<SG::IConstAuxStore> ElectronCollection___OriginalAux_m_parentLink;
   DataVector<xAOD::Jet_v1> *AntiKt4EMTopoJets___Nominal;
 //xAOD::AuxContainerBase *AntiKt4EMTopoJets___NominalAux_;
   string          AntiKt4EMTopoJets___NominalAux_m_name;
   vector<float>   *AntiKt4EMTopoJets___NominalAuxDyn_pt;
   vector<float>   *AntiKt4EMTopoJets___NominalAuxDyn_eta;
   vector<float>   *AntiKt4EMTopoJets___NominalAuxDyn_phi;
   vector<float>   *AntiKt4EMTopoJets___NominalAuxDyn_m;
   vector<int>     *AntiKt4EMTopoJets___NominalAuxDyn_isVetoJet;
   vector<int>     *AntiKt4EMTopoJets___NominalAuxDyn_isSignalJet;
   vector<int>     *AntiKt4EMTopoJets___NominalAuxDyn_passOR;
   vector<int>     *AntiKt4EMTopoJets___NominalAuxDyn_partIndex;
   vector<int>     *AntiKt4EMTopoJets___NominalAuxDyn_TruthLabelID;
   DataVector<xAOD::Jet_v1> *AntiKt4EMTopoJets___Original;
 //xAOD::ShallowAuxContainer *AntiKt4EMTopoJets___OriginalAux_;
   DataLink<SG::IConstAuxStore> AntiKt4EMTopoJets___OriginalAux_m_parentLink;
   vector<float>   *AntiKt4EMTopoJets___OriginalAuxDyn_pt;
   vector<float>   *AntiKt4EMTopoJets___OriginalAuxDyn_eta;
   vector<float>   *AntiKt4EMTopoJets___OriginalAuxDyn_phi;
   vector<float>   *AntiKt4EMTopoJets___OriginalAuxDyn_m;
   vector<int>     *AntiKt4EMTopoJets___OriginalAuxDyn_isVetoJet;
   vector<int>     *AntiKt4EMTopoJets___OriginalAuxDyn_isSignalJet;
   vector<int>     *AntiKt4EMTopoJets___OriginalAuxDyn_TruthLabelID;
   DataVector<xAOD::Jet_v1> *CamKt12LCTopoJets___Nominal;
 //xAOD::AuxContainerBase *CamKt12LCTopoJets___NominalAux_;
   string          CamKt12LCTopoJets___NominalAux_m_name;
   vector<float>   *CamKt12LCTopoJets___NominalAuxDyn_pt;
   vector<float>   *CamKt12LCTopoJets___NominalAuxDyn_eta;
   vector<float>   *CamKt12LCTopoJets___NominalAuxDyn_phi;
   vector<float>   *CamKt12LCTopoJets___NominalAuxDyn_m;
   vector<int>     *CamKt12LCTopoJets___NominalAuxDyn_partIndex;
   DataVector<xAOD::Jet_v1> *CamKt12LCTopoJets___Original;
 //xAOD::ShallowAuxContainer *CamKt12LCTopoJets___OriginalAux_;
   DataLink<SG::IConstAuxStore> CamKt12LCTopoJets___OriginalAux_m_parentLink;
   vector<float>   *CamKt12LCTopoJets___OriginalAuxDyn_pt;
   vector<float>   *CamKt12LCTopoJets___OriginalAuxDyn_eta;
   vector<float>   *CamKt12LCTopoJets___OriginalAuxDyn_phi;
   vector<float>   *CamKt12LCTopoJets___OriginalAuxDyn_m;
   xAOD::MissingETContainer_v1 *MET_RefFinal___Nominal;
 //xAOD::MissingETAuxContainer_v1 *MET_RefFinal___NominalAux_;
   xAOD::MissingETAuxContainer_v1 *MET_RefFinal___NominalAux_xAOD__AuxContainerBase;
   vector<double>  MET_RefFinal___NominalAux_mpx;
   vector<double>  MET_RefFinal___NominalAux_mpy;
   vector<double>  MET_RefFinal___NominalAux_sumet;
   vector<string>  MET_RefFinal___NominalAux_name;
   vector<unsigned long long> MET_RefFinal___NominalAux_source;
   vector<int>     *ElectronCollection___NominalAuxDyn_partIndex;
   vector<float>   *ElectronCollection___NominalAuxDyn_eta;
   vector<float>   *ElectronCollection___NominalAuxDyn_phi;
   vector<int>     *ElectronCollection___NominalAuxDyn_isVeryTightLH;
   vector<float>   *ElectronCollection___NominalAuxDyn_m;
   vector<int>     *ElectronCollection___NominalAuxDyn_isVHLooseElectron;
   vector<int>     *ElectronCollection___NominalAuxDyn_isZHSignalElectron;
   vector<float>   *ElectronCollection___NominalAuxDyn_ptcone20;
   vector<int>     *ElectronCollection___NominalAuxDyn_isWHSignalElectron;
   vector<float>   *ElectronCollection___NominalAuxDyn_topoetcone30;
   vector<int>     *ElectronCollection___NominalAuxDyn_passOR;
   vector<float>   *ElectronCollection___NominalAuxDyn_pt;
   vector<int>     *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVHLooseElectron;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_pt;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_ptcone20;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_eta;
   vector<int>     *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isZHSignalElectron;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_phi;
   vector<int>     *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isWHSignalElectron;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_m;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_topoetcone30;
   vector<int>     *ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVeryTightLH;
   vector<int>     *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVHLooseElectron;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_pt;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_ptcone20;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_eta;
   vector<int>     *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isZHSignalElectron;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_phi;
   vector<int>     *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isWHSignalElectron;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_m;
   vector<float>   *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_topoetcone30;
   vector<int>     *ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVeryTightLH;
   vector<int>     *ElectronCollection___OriginalAuxDyn_isVHLooseElectron;
   vector<float>   *ElectronCollection___OriginalAuxDyn_pt;
   vector<float>   *ElectronCollection___OriginalAuxDyn_ptcone20;
   vector<float>   *ElectronCollection___OriginalAuxDyn_eta;
   vector<int>     *ElectronCollection___OriginalAuxDyn_isZHSignalElectron;
   vector<float>   *ElectronCollection___OriginalAuxDyn_phi;
   vector<int>     *ElectronCollection___OriginalAuxDyn_isWHSignalElectron;
   vector<float>   *ElectronCollection___OriginalAuxDyn_m;
   vector<float>   *ElectronCollection___OriginalAuxDyn_topoetcone30;
   vector<int>     *ElectronCollection___OriginalAuxDyn_isVeryTightLH;

   // List of branches
   TBranch        *b_EventInfo___Nominal;   //!
   TBranch        *b_EventInfo___NominalAux_m_name;   //!
   TBranch        *b_EventInfo___NominalAuxDyn_isMC;   //!
   TBranch        *b_EventInfo___NominalAuxDyn_MCEventWeight;   //!
   TBranch        *b_EventInfo___NominalAuxDyn_zPV;   //!
   TBranch        *b_EventInfo___NominalAuxDyn_NVtx3Trks;   //!
   TBranch        *b_EventInfo___NominalAuxDyn_runNumber;   //!
   TBranch        *b_EventInfo___NominalAuxDyn_eventNumber;   //!
   TBranch        *b_EventInfo___NominalAuxDyn_mcChannelNumber;   //!
   TBranch        *b_EventInfo___NominalAuxDyn_mcEventNumber;   //!
   TBranch        *b_EventInfo___NominalAuxDyn_averageInteractionsPerCrossing;   //!
   TBranch        *b_TruthParticle___Nominal;   //!
   TBranch        *b_TruthParticle___NominalAux_m_name;   //!
   TBranch        *b_TruthParticle___NominalAuxDyn_m;   //!
   TBranch        *b_TruthParticle___NominalAuxDyn_px;   //!
   TBranch        *b_TruthParticle___NominalAuxDyn_partIndex;   //!
   TBranch        *b_TruthParticle___NominalAuxDyn_pdgId;   //!
   TBranch        *b_TruthParticle___NominalAuxDyn_py;   //!
   TBranch        *b_TruthParticle___NominalAuxDyn_barcode;   //!
   TBranch        *b_TruthParticle___NominalAuxDyn_pz;   //!
   TBranch        *b_TruthParticle___NominalAuxDyn_status;   //!
   TBranch        *b_TruthParticle___NominalAuxDyn_e;   //!
   TBranch        *b_Muons___Nominal;   //!
   TBranch        *b_Muons___NominalAux_m_name;   //!
   TBranch        *b_Muons___MUONS_ID__1down;   //!
   TBranch        *b_Muons___MUONS_ID__1downAux_m_parentLink;   //!
   TBranch        *b_Muons___MUONS_ID__1up;   //!
   TBranch        *b_Muons___MUONS_ID__1upAux_m_parentLink;   //!
   TBranch        *b_Muons___MUONS_MS__1down;   //!
   TBranch        *b_Muons___MUONS_MS__1downAux_m_parentLink;   //!
   TBranch        *b_Muons___MUONS_MS__1up;   //!
   TBranch        *b_Muons___MUONS_MS__1upAux_m_parentLink;   //!
   TBranch        *b_Muons___MUONS_SCALE__1down;   //!
   TBranch        *b_Muons___MUONS_SCALE__1downAux_m_parentLink;   //!
   TBranch        *b_Muons___MUONS_SCALE__1up;   //!
   TBranch        *b_Muons___MUONS_SCALE__1upAux_m_parentLink;   //!
   TBranch        *b_Muons___Original;   //!
   TBranch        *b_Muons___OriginalAux_m_parentLink;   //!
   TBranch        *b_ElectronCollection___Nominal;   //!
   TBranch        *b_ElectronCollection___NominalAux_m_name;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1down;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAux_m_parentLink;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1up;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAux_m_parentLink;   //!
   TBranch        *b_ElectronCollection___Original;   //!
   TBranch        *b_ElectronCollection___OriginalAux_m_parentLink;   //!
   TBranch        *b_AntiKt4EMTopoJets___Nominal;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAux_m_name;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAuxDyn_pt;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAuxDyn_eta;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAuxDyn_phi;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAuxDyn_m;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAuxDyn_isVetoJet;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAuxDyn_isSignalJet;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAuxDyn_passOR;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAuxDyn_partIndex;   //!
   TBranch        *b_AntiKt4EMTopoJets___NominalAuxDyn_TruthLabelID;   //!
   TBranch        *b_AntiKt4EMTopoJets___Original;   //!
   TBranch        *b_AntiKt4EMTopoJets___OriginalAux_m_parentLink;   //!
   TBranch        *b_AntiKt4EMTopoJets___OriginalAuxDyn_pt;   //!
   TBranch        *b_AntiKt4EMTopoJets___OriginalAuxDyn_eta;   //!
   TBranch        *b_AntiKt4EMTopoJets___OriginalAuxDyn_phi;   //!
   TBranch        *b_AntiKt4EMTopoJets___OriginalAuxDyn_m;   //!
   TBranch        *b_AntiKt4EMTopoJets___OriginalAuxDyn_isVetoJet;   //!
   TBranch        *b_AntiKt4EMTopoJets___OriginalAuxDyn_isSignalJet;   //!
   TBranch        *b_AntiKt4EMTopoJets___OriginalAuxDyn_TruthLabelID;   //!
   TBranch        *b_CamKt12LCTopoJets___Nominal;   //!
   TBranch        *b_CamKt12LCTopoJets___NominalAux_m_name;   //!
   TBranch        *b_CamKt12LCTopoJets___NominalAuxDyn_pt;   //!
   TBranch        *b_CamKt12LCTopoJets___NominalAuxDyn_eta;   //!
   TBranch        *b_CamKt12LCTopoJets___NominalAuxDyn_phi;   //!
   TBranch        *b_CamKt12LCTopoJets___NominalAuxDyn_m;   //!
   TBranch        *b_CamKt12LCTopoJets___NominalAuxDyn_partIndex;   //!
   TBranch        *b_CamKt12LCTopoJets___Original;   //!
   TBranch        *b_CamKt12LCTopoJets___OriginalAux_m_parentLink;   //!
   TBranch        *b_CamKt12LCTopoJets___OriginalAuxDyn_pt;   //!
   TBranch        *b_CamKt12LCTopoJets___OriginalAuxDyn_eta;   //!
   TBranch        *b_CamKt12LCTopoJets___OriginalAuxDyn_phi;   //!
   TBranch        *b_CamKt12LCTopoJets___OriginalAuxDyn_m;   //!
   TBranch        *b_MET_RefFinal___Nominal;   //!
   TBranch        *b_MET_RefFinal___NominalAux_xAOD__AuxContainerBase;   //!
   TBranch        *b_MET_RefFinal___NominalAux_mpx;   //!
   TBranch        *b_MET_RefFinal___NominalAux_mpy;   //!
   TBranch        *b_MET_RefFinal___NominalAux_sumet;   //!
   TBranch        *b_MET_RefFinal___NominalAux_name;   //!
   TBranch        *b_MET_RefFinal___NominalAux_source;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_partIndex;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_eta;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_phi;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_isVeryTightLH;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_m;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_isVHLooseElectron;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_isZHSignalElectron;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_ptcone20;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_isWHSignalElectron;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_topoetcone30;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_passOR;   //!
   TBranch        *b_ElectronCollection___NominalAuxDyn_pt;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVHLooseElectron;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_pt;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_ptcone20;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_eta;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isZHSignalElectron;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_phi;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isWHSignalElectron;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_m;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_topoetcone30;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVeryTightLH;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVHLooseElectron;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_pt;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_ptcone20;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_eta;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isZHSignalElectron;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_phi;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isWHSignalElectron;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_m;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_topoetcone30;   //!
   TBranch        *b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVeryTightLH;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_isVHLooseElectron;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_pt;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_ptcone20;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_eta;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_isZHSignalElectron;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_phi;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_isWHSignalElectron;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_m;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_topoetcone30;   //!
   TBranch        *b_ElectronCollection___OriginalAuxDyn_isVeryTightLH;   //!

   CollectionTree(TTree *tree=0);
   virtual ~CollectionTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef CollectionTree_cxx
CollectionTree::CollectionTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("sampleCxAOD/data-outputLabel/AOD.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("sampleCxAOD/data-outputLabel/AOD.root");
      }
      f->GetObject("CollectionTree",tree);

   }
   Init(tree);
}

CollectionTree::~CollectionTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t CollectionTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CollectionTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void CollectionTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   EventInfo___Nominal = 0;
   TruthParticle___Nominal = 0;
   TruthParticle___NominalAuxDyn_m = 0;
   TruthParticle___NominalAuxDyn_px = 0;
   TruthParticle___NominalAuxDyn_partIndex = 0;
   TruthParticle___NominalAuxDyn_pdgId = 0;
   TruthParticle___NominalAuxDyn_py = 0;
   TruthParticle___NominalAuxDyn_barcode = 0;
   TruthParticle___NominalAuxDyn_pz = 0;
   TruthParticle___NominalAuxDyn_status = 0;
   TruthParticle___NominalAuxDyn_e = 0;
   Muons___Nominal = 0;
   Muons___MUONS_ID__1down = 0;
   Muons___MUONS_ID__1up = 0;
   Muons___MUONS_MS__1down = 0;
   Muons___MUONS_MS__1up = 0;
   Muons___MUONS_SCALE__1down = 0;
   Muons___MUONS_SCALE__1up = 0;
   Muons___Original = 0;
   ElectronCollection___Nominal = 0;
   ElectronCollection___EG_SCALE_ALL__1down = 0;
   ElectronCollection___EG_SCALE_ALL__1up = 0;
   ElectronCollection___Original = 0;
   AntiKt4EMTopoJets___Nominal = 0;
   AntiKt4EMTopoJets___NominalAuxDyn_pt = 0;
   AntiKt4EMTopoJets___NominalAuxDyn_eta = 0;
   AntiKt4EMTopoJets___NominalAuxDyn_phi = 0;
   AntiKt4EMTopoJets___NominalAuxDyn_m = 0;
   AntiKt4EMTopoJets___NominalAuxDyn_isVetoJet = 0;
   AntiKt4EMTopoJets___NominalAuxDyn_isSignalJet = 0;
   AntiKt4EMTopoJets___NominalAuxDyn_passOR = 0;
   AntiKt4EMTopoJets___NominalAuxDyn_partIndex = 0;
   AntiKt4EMTopoJets___NominalAuxDyn_TruthLabelID = 0;
   AntiKt4EMTopoJets___Original = 0;
   AntiKt4EMTopoJets___OriginalAuxDyn_pt = 0;
   AntiKt4EMTopoJets___OriginalAuxDyn_eta = 0;
   AntiKt4EMTopoJets___OriginalAuxDyn_phi = 0;
   AntiKt4EMTopoJets___OriginalAuxDyn_m = 0;
   AntiKt4EMTopoJets___OriginalAuxDyn_isVetoJet = 0;
   AntiKt4EMTopoJets___OriginalAuxDyn_isSignalJet = 0;
   AntiKt4EMTopoJets___OriginalAuxDyn_TruthLabelID = 0;
   CamKt12LCTopoJets___Nominal = 0;
   CamKt12LCTopoJets___NominalAuxDyn_pt = 0;
   CamKt12LCTopoJets___NominalAuxDyn_eta = 0;
   CamKt12LCTopoJets___NominalAuxDyn_phi = 0;
   CamKt12LCTopoJets___NominalAuxDyn_m = 0;
   CamKt12LCTopoJets___NominalAuxDyn_partIndex = 0;
   CamKt12LCTopoJets___Original = 0;
   CamKt12LCTopoJets___OriginalAuxDyn_pt = 0;
   CamKt12LCTopoJets___OriginalAuxDyn_eta = 0;
   CamKt12LCTopoJets___OriginalAuxDyn_phi = 0;
   CamKt12LCTopoJets___OriginalAuxDyn_m = 0;
   MET_RefFinal___Nominal = 0;
   MET_RefFinal___NominalAux_xAOD__AuxContainerBase = 0;
   ElectronCollection___NominalAuxDyn_partIndex = 0;
   ElectronCollection___NominalAuxDyn_eta = 0;
   ElectronCollection___NominalAuxDyn_phi = 0;
   ElectronCollection___NominalAuxDyn_isVeryTightLH = 0;
   ElectronCollection___NominalAuxDyn_m = 0;
   ElectronCollection___NominalAuxDyn_isVHLooseElectron = 0;
   ElectronCollection___NominalAuxDyn_isZHSignalElectron = 0;
   ElectronCollection___NominalAuxDyn_ptcone20 = 0;
   ElectronCollection___NominalAuxDyn_isWHSignalElectron = 0;
   ElectronCollection___NominalAuxDyn_topoetcone30 = 0;
   ElectronCollection___NominalAuxDyn_passOR = 0;
   ElectronCollection___NominalAuxDyn_pt = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVHLooseElectron = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_pt = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_ptcone20 = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_eta = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isZHSignalElectron = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_phi = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isWHSignalElectron = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_m = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_topoetcone30 = 0;
   ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVeryTightLH = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVHLooseElectron = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_pt = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_ptcone20 = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_eta = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isZHSignalElectron = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_phi = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isWHSignalElectron = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_m = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_topoetcone30 = 0;
   ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVeryTightLH = 0;
   ElectronCollection___OriginalAuxDyn_isVHLooseElectron = 0;
   ElectronCollection___OriginalAuxDyn_pt = 0;
   ElectronCollection___OriginalAuxDyn_ptcone20 = 0;
   ElectronCollection___OriginalAuxDyn_eta = 0;
   ElectronCollection___OriginalAuxDyn_isZHSignalElectron = 0;
   ElectronCollection___OriginalAuxDyn_phi = 0;
   ElectronCollection___OriginalAuxDyn_isWHSignalElectron = 0;
   ElectronCollection___OriginalAuxDyn_m = 0;
   ElectronCollection___OriginalAuxDyn_topoetcone30 = 0;
   ElectronCollection___OriginalAuxDyn_isVeryTightLH = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventInfo___Nominal", &EventInfo___Nominal, &b_EventInfo___Nominal);
   fChain->SetBranchAddress("EventInfo___NominalAux.m_name", &EventInfo___NominalAux_m_name, &b_EventInfo___NominalAux_m_name);
   fChain->SetBranchAddress("EventInfo___NominalAuxDyn.isMC", &EventInfo___NominalAuxDyn_isMC, &b_EventInfo___NominalAuxDyn_isMC);
   fChain->SetBranchAddress("EventInfo___NominalAuxDyn.MCEventWeight", &EventInfo___NominalAuxDyn_MCEventWeight, &b_EventInfo___NominalAuxDyn_MCEventWeight);
   fChain->SetBranchAddress("EventInfo___NominalAuxDyn.zPV", &EventInfo___NominalAuxDyn_zPV, &b_EventInfo___NominalAuxDyn_zPV);
   fChain->SetBranchAddress("EventInfo___NominalAuxDyn.NVtx3Trks", &EventInfo___NominalAuxDyn_NVtx3Trks, &b_EventInfo___NominalAuxDyn_NVtx3Trks);
   fChain->SetBranchAddress("EventInfo___NominalAuxDyn.runNumber", &EventInfo___NominalAuxDyn_runNumber, &b_EventInfo___NominalAuxDyn_runNumber);
   fChain->SetBranchAddress("EventInfo___NominalAuxDyn.eventNumber", &EventInfo___NominalAuxDyn_eventNumber, &b_EventInfo___NominalAuxDyn_eventNumber);
   fChain->SetBranchAddress("EventInfo___NominalAuxDyn.mcChannelNumber", &EventInfo___NominalAuxDyn_mcChannelNumber, &b_EventInfo___NominalAuxDyn_mcChannelNumber);
   fChain->SetBranchAddress("EventInfo___NominalAuxDyn.mcEventNumber", &EventInfo___NominalAuxDyn_mcEventNumber, &b_EventInfo___NominalAuxDyn_mcEventNumber);
   fChain->SetBranchAddress("EventInfo___NominalAuxDyn.averageInteractionsPerCrossing", &EventInfo___NominalAuxDyn_averageInteractionsPerCrossing, &b_EventInfo___NominalAuxDyn_averageInteractionsPerCrossing);
   fChain->SetBranchAddress("TruthParticle___Nominal", &TruthParticle___Nominal, &b_TruthParticle___Nominal);
   fChain->SetBranchAddress("TruthParticle___NominalAux.m_name", &TruthParticle___NominalAux_m_name, &b_TruthParticle___NominalAux_m_name);
   fChain->SetBranchAddress("TruthParticle___NominalAuxDyn.m", &TruthParticle___NominalAuxDyn_m, &b_TruthParticle___NominalAuxDyn_m);
   fChain->SetBranchAddress("TruthParticle___NominalAuxDyn.px", &TruthParticle___NominalAuxDyn_px, &b_TruthParticle___NominalAuxDyn_px);
   fChain->SetBranchAddress("TruthParticle___NominalAuxDyn.partIndex", &TruthParticle___NominalAuxDyn_partIndex, &b_TruthParticle___NominalAuxDyn_partIndex);
   fChain->SetBranchAddress("TruthParticle___NominalAuxDyn.pdgId", &TruthParticle___NominalAuxDyn_pdgId, &b_TruthParticle___NominalAuxDyn_pdgId);
   fChain->SetBranchAddress("TruthParticle___NominalAuxDyn.py", &TruthParticle___NominalAuxDyn_py, &b_TruthParticle___NominalAuxDyn_py);
   fChain->SetBranchAddress("TruthParticle___NominalAuxDyn.barcode", &TruthParticle___NominalAuxDyn_barcode, &b_TruthParticle___NominalAuxDyn_barcode);
   fChain->SetBranchAddress("TruthParticle___NominalAuxDyn.pz", &TruthParticle___NominalAuxDyn_pz, &b_TruthParticle___NominalAuxDyn_pz);
   fChain->SetBranchAddress("TruthParticle___NominalAuxDyn.status", &TruthParticle___NominalAuxDyn_status, &b_TruthParticle___NominalAuxDyn_status);
   fChain->SetBranchAddress("TruthParticle___NominalAuxDyn.e", &TruthParticle___NominalAuxDyn_e, &b_TruthParticle___NominalAuxDyn_e);
   fChain->SetBranchAddress("Muons___Nominal", &Muons___Nominal, &b_Muons___Nominal);
   fChain->SetBranchAddress("Muons___NominalAux.m_name", &Muons___NominalAux_m_name, &b_Muons___NominalAux_m_name);
   fChain->SetBranchAddress("Muons___MUONS_ID__1down", &Muons___MUONS_ID__1down, &b_Muons___MUONS_ID__1down);
   fChain->SetBranchAddress("Muons___MUONS_ID__1downAux.m_parentLink", &Muons___MUONS_ID__1downAux_m_parentLink, &b_Muons___MUONS_ID__1downAux_m_parentLink);
   fChain->SetBranchAddress("Muons___MUONS_ID__1up", &Muons___MUONS_ID__1up, &b_Muons___MUONS_ID__1up);
   fChain->SetBranchAddress("Muons___MUONS_ID__1upAux.m_parentLink", &Muons___MUONS_ID__1upAux_m_parentLink, &b_Muons___MUONS_ID__1upAux_m_parentLink);
   fChain->SetBranchAddress("Muons___MUONS_MS__1down", &Muons___MUONS_MS__1down, &b_Muons___MUONS_MS__1down);
   fChain->SetBranchAddress("Muons___MUONS_MS__1downAux.m_parentLink", &Muons___MUONS_MS__1downAux_m_parentLink, &b_Muons___MUONS_MS__1downAux_m_parentLink);
   fChain->SetBranchAddress("Muons___MUONS_MS__1up", &Muons___MUONS_MS__1up, &b_Muons___MUONS_MS__1up);
   fChain->SetBranchAddress("Muons___MUONS_MS__1upAux.m_parentLink", &Muons___MUONS_MS__1upAux_m_parentLink, &b_Muons___MUONS_MS__1upAux_m_parentLink);
   fChain->SetBranchAddress("Muons___MUONS_SCALE__1down", &Muons___MUONS_SCALE__1down, &b_Muons___MUONS_SCALE__1down);
   fChain->SetBranchAddress("Muons___MUONS_SCALE__1downAux.m_parentLink", &Muons___MUONS_SCALE__1downAux_m_parentLink, &b_Muons___MUONS_SCALE__1downAux_m_parentLink);
   fChain->SetBranchAddress("Muons___MUONS_SCALE__1up", &Muons___MUONS_SCALE__1up, &b_Muons___MUONS_SCALE__1up);
   fChain->SetBranchAddress("Muons___MUONS_SCALE__1upAux.m_parentLink", &Muons___MUONS_SCALE__1upAux_m_parentLink, &b_Muons___MUONS_SCALE__1upAux_m_parentLink);
   fChain->SetBranchAddress("Muons___Original", &Muons___Original, &b_Muons___Original);
   fChain->SetBranchAddress("Muons___OriginalAux.m_parentLink", &Muons___OriginalAux_m_parentLink, &b_Muons___OriginalAux_m_parentLink);
   fChain->SetBranchAddress("ElectronCollection___Nominal", &ElectronCollection___Nominal, &b_ElectronCollection___Nominal);
   fChain->SetBranchAddress("ElectronCollection___NominalAux.m_name", &ElectronCollection___NominalAux_m_name, &b_ElectronCollection___NominalAux_m_name);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1down", &ElectronCollection___EG_SCALE_ALL__1down, &b_ElectronCollection___EG_SCALE_ALL__1down);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAux.m_parentLink", &ElectronCollection___EG_SCALE_ALL__1downAux_m_parentLink, &b_ElectronCollection___EG_SCALE_ALL__1downAux_m_parentLink);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1up", &ElectronCollection___EG_SCALE_ALL__1up, &b_ElectronCollection___EG_SCALE_ALL__1up);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAux.m_parentLink", &ElectronCollection___EG_SCALE_ALL__1upAux_m_parentLink, &b_ElectronCollection___EG_SCALE_ALL__1upAux_m_parentLink);
   fChain->SetBranchAddress("ElectronCollection___Original", &ElectronCollection___Original, &b_ElectronCollection___Original);
   fChain->SetBranchAddress("ElectronCollection___OriginalAux.m_parentLink", &ElectronCollection___OriginalAux_m_parentLink, &b_ElectronCollection___OriginalAux_m_parentLink);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___Nominal", &AntiKt4EMTopoJets___Nominal, &b_AntiKt4EMTopoJets___Nominal);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAux.m_name", &AntiKt4EMTopoJets___NominalAux_m_name, &b_AntiKt4EMTopoJets___NominalAux_m_name);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAuxDyn.pt", &AntiKt4EMTopoJets___NominalAuxDyn_pt, &b_AntiKt4EMTopoJets___NominalAuxDyn_pt);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAuxDyn.eta", &AntiKt4EMTopoJets___NominalAuxDyn_eta, &b_AntiKt4EMTopoJets___NominalAuxDyn_eta);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAuxDyn.phi", &AntiKt4EMTopoJets___NominalAuxDyn_phi, &b_AntiKt4EMTopoJets___NominalAuxDyn_phi);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAuxDyn.m", &AntiKt4EMTopoJets___NominalAuxDyn_m, &b_AntiKt4EMTopoJets___NominalAuxDyn_m);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAuxDyn.isVetoJet", &AntiKt4EMTopoJets___NominalAuxDyn_isVetoJet, &b_AntiKt4EMTopoJets___NominalAuxDyn_isVetoJet);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAuxDyn.isSignalJet", &AntiKt4EMTopoJets___NominalAuxDyn_isSignalJet, &b_AntiKt4EMTopoJets___NominalAuxDyn_isSignalJet);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAuxDyn.passOR", &AntiKt4EMTopoJets___NominalAuxDyn_passOR, &b_AntiKt4EMTopoJets___NominalAuxDyn_passOR);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAuxDyn.partIndex", &AntiKt4EMTopoJets___NominalAuxDyn_partIndex, &b_AntiKt4EMTopoJets___NominalAuxDyn_partIndex);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___NominalAuxDyn.TruthLabelID", &AntiKt4EMTopoJets___NominalAuxDyn_TruthLabelID, &b_AntiKt4EMTopoJets___NominalAuxDyn_TruthLabelID);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___Original", &AntiKt4EMTopoJets___Original, &b_AntiKt4EMTopoJets___Original);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___OriginalAux.m_parentLink", &AntiKt4EMTopoJets___OriginalAux_m_parentLink, &b_AntiKt4EMTopoJets___OriginalAux_m_parentLink);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___OriginalAuxDyn.pt", &AntiKt4EMTopoJets___OriginalAuxDyn_pt, &b_AntiKt4EMTopoJets___OriginalAuxDyn_pt);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___OriginalAuxDyn.eta", &AntiKt4EMTopoJets___OriginalAuxDyn_eta, &b_AntiKt4EMTopoJets___OriginalAuxDyn_eta);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___OriginalAuxDyn.phi", &AntiKt4EMTopoJets___OriginalAuxDyn_phi, &b_AntiKt4EMTopoJets___OriginalAuxDyn_phi);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___OriginalAuxDyn.m", &AntiKt4EMTopoJets___OriginalAuxDyn_m, &b_AntiKt4EMTopoJets___OriginalAuxDyn_m);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___OriginalAuxDyn.isVetoJet", &AntiKt4EMTopoJets___OriginalAuxDyn_isVetoJet, &b_AntiKt4EMTopoJets___OriginalAuxDyn_isVetoJet);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___OriginalAuxDyn.isSignalJet", &AntiKt4EMTopoJets___OriginalAuxDyn_isSignalJet, &b_AntiKt4EMTopoJets___OriginalAuxDyn_isSignalJet);
   fChain->SetBranchAddress("AntiKt4EMTopoJets___OriginalAuxDyn.TruthLabelID", &AntiKt4EMTopoJets___OriginalAuxDyn_TruthLabelID, &b_AntiKt4EMTopoJets___OriginalAuxDyn_TruthLabelID);
   fChain->SetBranchAddress("CamKt12LCTopoJets___Nominal", &CamKt12LCTopoJets___Nominal, &b_CamKt12LCTopoJets___Nominal);
   fChain->SetBranchAddress("CamKt12LCTopoJets___NominalAux.m_name", &CamKt12LCTopoJets___NominalAux_m_name, &b_CamKt12LCTopoJets___NominalAux_m_name);
   fChain->SetBranchAddress("CamKt12LCTopoJets___NominalAuxDyn.pt", &CamKt12LCTopoJets___NominalAuxDyn_pt, &b_CamKt12LCTopoJets___NominalAuxDyn_pt);
   fChain->SetBranchAddress("CamKt12LCTopoJets___NominalAuxDyn.eta", &CamKt12LCTopoJets___NominalAuxDyn_eta, &b_CamKt12LCTopoJets___NominalAuxDyn_eta);
   fChain->SetBranchAddress("CamKt12LCTopoJets___NominalAuxDyn.phi", &CamKt12LCTopoJets___NominalAuxDyn_phi, &b_CamKt12LCTopoJets___NominalAuxDyn_phi);
   fChain->SetBranchAddress("CamKt12LCTopoJets___NominalAuxDyn.m", &CamKt12LCTopoJets___NominalAuxDyn_m, &b_CamKt12LCTopoJets___NominalAuxDyn_m);
   fChain->SetBranchAddress("CamKt12LCTopoJets___NominalAuxDyn.partIndex", &CamKt12LCTopoJets___NominalAuxDyn_partIndex, &b_CamKt12LCTopoJets___NominalAuxDyn_partIndex);
   fChain->SetBranchAddress("CamKt12LCTopoJets___Original", &CamKt12LCTopoJets___Original, &b_CamKt12LCTopoJets___Original);
   fChain->SetBranchAddress("CamKt12LCTopoJets___OriginalAux.m_parentLink", &CamKt12LCTopoJets___OriginalAux_m_parentLink, &b_CamKt12LCTopoJets___OriginalAux_m_parentLink);
   fChain->SetBranchAddress("CamKt12LCTopoJets___OriginalAuxDyn.pt", &CamKt12LCTopoJets___OriginalAuxDyn_pt, &b_CamKt12LCTopoJets___OriginalAuxDyn_pt);
   fChain->SetBranchAddress("CamKt12LCTopoJets___OriginalAuxDyn.eta", &CamKt12LCTopoJets___OriginalAuxDyn_eta, &b_CamKt12LCTopoJets___OriginalAuxDyn_eta);
   fChain->SetBranchAddress("CamKt12LCTopoJets___OriginalAuxDyn.phi", &CamKt12LCTopoJets___OriginalAuxDyn_phi, &b_CamKt12LCTopoJets___OriginalAuxDyn_phi);
   fChain->SetBranchAddress("CamKt12LCTopoJets___OriginalAuxDyn.m", &CamKt12LCTopoJets___OriginalAuxDyn_m, &b_CamKt12LCTopoJets___OriginalAuxDyn_m);
   fChain->SetBranchAddress("MET_RefFinal___Nominal", &MET_RefFinal___Nominal, &b_MET_RefFinal___Nominal);
   fChain->SetBranchAddress("MET_RefFinal___NominalAux.xAOD::AuxContainerBase", &MET_RefFinal___NominalAux_xAOD__AuxContainerBase, &b_MET_RefFinal___NominalAux_xAOD__AuxContainerBase);
   fChain->SetBranchAddress("MET_RefFinal___NominalAux.mpx", &MET_RefFinal___NominalAux_mpx, &b_MET_RefFinal___NominalAux_mpx);
   fChain->SetBranchAddress("MET_RefFinal___NominalAux.mpy", &MET_RefFinal___NominalAux_mpy, &b_MET_RefFinal___NominalAux_mpy);
   fChain->SetBranchAddress("MET_RefFinal___NominalAux.sumet", &MET_RefFinal___NominalAux_sumet, &b_MET_RefFinal___NominalAux_sumet);
   fChain->SetBranchAddress("MET_RefFinal___NominalAux.name", &MET_RefFinal___NominalAux_name, &b_MET_RefFinal___NominalAux_name);
   fChain->SetBranchAddress("MET_RefFinal___NominalAux.source", &MET_RefFinal___NominalAux_source, &b_MET_RefFinal___NominalAux_source);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.partIndex", &ElectronCollection___NominalAuxDyn_partIndex, &b_ElectronCollection___NominalAuxDyn_partIndex);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.eta", &ElectronCollection___NominalAuxDyn_eta, &b_ElectronCollection___NominalAuxDyn_eta);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.phi", &ElectronCollection___NominalAuxDyn_phi, &b_ElectronCollection___NominalAuxDyn_phi);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.isVeryTightLH", &ElectronCollection___NominalAuxDyn_isVeryTightLH, &b_ElectronCollection___NominalAuxDyn_isVeryTightLH);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.m", &ElectronCollection___NominalAuxDyn_m, &b_ElectronCollection___NominalAuxDyn_m);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.isVHLooseElectron", &ElectronCollection___NominalAuxDyn_isVHLooseElectron, &b_ElectronCollection___NominalAuxDyn_isVHLooseElectron);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.isZHSignalElectron", &ElectronCollection___NominalAuxDyn_isZHSignalElectron, &b_ElectronCollection___NominalAuxDyn_isZHSignalElectron);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.ptcone20", &ElectronCollection___NominalAuxDyn_ptcone20, &b_ElectronCollection___NominalAuxDyn_ptcone20);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.isWHSignalElectron", &ElectronCollection___NominalAuxDyn_isWHSignalElectron, &b_ElectronCollection___NominalAuxDyn_isWHSignalElectron);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.topoetcone30", &ElectronCollection___NominalAuxDyn_topoetcone30, &b_ElectronCollection___NominalAuxDyn_topoetcone30);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.passOR", &ElectronCollection___NominalAuxDyn_passOR, &b_ElectronCollection___NominalAuxDyn_passOR);
   fChain->SetBranchAddress("ElectronCollection___NominalAuxDyn.pt", &ElectronCollection___NominalAuxDyn_pt, &b_ElectronCollection___NominalAuxDyn_pt);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.isVHLooseElectron", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVHLooseElectron, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVHLooseElectron);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.pt", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_pt, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_pt);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.ptcone20", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_ptcone20, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_ptcone20);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.eta", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_eta, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_eta);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.isZHSignalElectron", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isZHSignalElectron, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isZHSignalElectron);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.phi", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_phi, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_phi);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.isWHSignalElectron", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isWHSignalElectron, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isWHSignalElectron);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.m", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_m, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_m);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.topoetcone30", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_topoetcone30, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_topoetcone30);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1downAuxDyn.isVeryTightLH", &ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVeryTightLH, &b_ElectronCollection___EG_SCALE_ALL__1downAuxDyn_isVeryTightLH);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.isVHLooseElectron", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVHLooseElectron, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVHLooseElectron);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.pt", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_pt, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_pt);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.ptcone20", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_ptcone20, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_ptcone20);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.eta", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_eta, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_eta);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.isZHSignalElectron", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isZHSignalElectron, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isZHSignalElectron);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.phi", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_phi, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_phi);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.isWHSignalElectron", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isWHSignalElectron, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isWHSignalElectron);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.m", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_m, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_m);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.topoetcone30", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_topoetcone30, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_topoetcone30);
   fChain->SetBranchAddress("ElectronCollection___EG_SCALE_ALL__1upAuxDyn.isVeryTightLH", &ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVeryTightLH, &b_ElectronCollection___EG_SCALE_ALL__1upAuxDyn_isVeryTightLH);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.isVHLooseElectron", &ElectronCollection___OriginalAuxDyn_isVHLooseElectron, &b_ElectronCollection___OriginalAuxDyn_isVHLooseElectron);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.pt", &ElectronCollection___OriginalAuxDyn_pt, &b_ElectronCollection___OriginalAuxDyn_pt);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.ptcone20", &ElectronCollection___OriginalAuxDyn_ptcone20, &b_ElectronCollection___OriginalAuxDyn_ptcone20);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.eta", &ElectronCollection___OriginalAuxDyn_eta, &b_ElectronCollection___OriginalAuxDyn_eta);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.isZHSignalElectron", &ElectronCollection___OriginalAuxDyn_isZHSignalElectron, &b_ElectronCollection___OriginalAuxDyn_isZHSignalElectron);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.phi", &ElectronCollection___OriginalAuxDyn_phi, &b_ElectronCollection___OriginalAuxDyn_phi);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.isWHSignalElectron", &ElectronCollection___OriginalAuxDyn_isWHSignalElectron, &b_ElectronCollection___OriginalAuxDyn_isWHSignalElectron);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.m", &ElectronCollection___OriginalAuxDyn_m, &b_ElectronCollection___OriginalAuxDyn_m);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.topoetcone30", &ElectronCollection___OriginalAuxDyn_topoetcone30, &b_ElectronCollection___OriginalAuxDyn_topoetcone30);
   fChain->SetBranchAddress("ElectronCollection___OriginalAuxDyn.isVeryTightLH", &ElectronCollection___OriginalAuxDyn_isVeryTightLH, &b_ElectronCollection___OriginalAuxDyn_isVeryTightLH);
   Notify();
}

Bool_t CollectionTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void CollectionTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CollectionTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef CollectionTree_cxx
