#ifndef RECOTUPLE
#define RECOTUPLE

#include "BaseTuple.h"

class RecoTuple : public BaseTuple {

public:
  RecoTuple();
  ~RecoTuple();


  //vertices
  const static int MAXVERTICES=100;
  int nvtx;
  float vtx_x[MAXVERTICES];
  float vtx_y[MAXVERTICES];
  float vtx_z[MAXVERTICES];

  //MET
  float met_pt;
  float met_eta;
  float met_phi;
  float met_px;
  float met_py;

  //Electrons
  const static int MAXELECTRONS=30;
  int nele;
  float ele_E[MAXELECTRONS];
  float ele_m[MAXELECTRONS];
  float ele_pt[MAXELECTRONS];
  float ele_phi[MAXELECTRONS];
  float ele_eta[MAXELECTRONS];
  float ele_z0[MAXELECTRONS];
  float ele_d0[MAXELECTRONS];
  int ele_charge[MAXELECTRONS];
  float ele_ptiso[MAXELECTRONS];
  float ele_etiso[MAXELECTRONS];
  int ele_idVHl[MAXELECTRONS];
  int ele_idZHl[MAXELECTRONS];
  int ele_idWHl[MAXELECTRONS];
  int ele_passor[MAXELECTRONS];

  //Muons
  const static int MAXMUONS=20;
  int nmuo;
  float muo_E[MAXMUONS];
  float muo_m[MAXMUONS];
  float muo_pt[MAXMUONS];
  float muo_phi[MAXMUONS];
  float muo_eta[MAXMUONS];
  float muo_z0[MAXMUONS];
  float muo_d0[MAXMUONS];
  int muo_charge[MAXMUONS];
  float muo_ptiso[MAXMUONS];
  float muo_etiso[MAXMUONS];
  int muo_idVHl[MAXMUONS];
  int muo_idZH[MAXMUONS];
  int muo_idWH[MAXMUONS];
  int muo_passor[MAXMUONS];
  
  //Taus
  const static int MAXTAUS=30;
  int ntau;
  float tau_E[MAXTAUS];
  float tau_m[MAXTAUS];
  float tau_pt[MAXTAUS];
  float tau_phi[MAXTAUS];
  float tau_eta[MAXTAUS];
  float tau_z0[MAXTAUS];
  float tau_d0[MAXTAUS];
  int tau_charge[MAXTAUS];
  int tau_passor[MAXTAUS];

  //Jets
  const static int MAXJETS=50;
  int njet;
  int jet_charge[MAXJETS];
  float jet_E[MAXJETS];
  float jet_m[MAXJETS];
  float jet_pt[MAXJETS];
  float jet_phi[MAXJETS];
  float jet_eta[MAXJETS];

  int jet_ntrk[MAXJETS];
  float jet_massvx[MAXJETS];
  float jet_normdist[MAXJETS];
  float jet_jvf[MAXJETS];

  int jet_good[MAXJETS];
  int jet_passor[MAXJETS];

  float jet_mv1[MAXJETS];
  float jet_sv1ip3d[MAXJETS];
  float jet_mv2c00[MAXJETS];
  float jet_mv2c10[MAXJETS];
  float jet_mv2c20[MAXJETS];
  float jet_mvb[MAXJETS];



  //electron pairs
  const static int MAXEE=100;
  int nee;
  int ee_charge[MAXEE];
  float ee_m[MAXEE];
  float ee_E[MAXEE];
  float ee_p[MAXEE];
  float ee_pt[MAXEE];
  float ee_phi[MAXEE];
  float ee_eta[MAXEE];
  float ee_dR[MAXEE];
  int   ee_leg1[MAXEE];
  int   ee_leg2[MAXEE];

  //muon pairs
  const static int MAXMM=100;
  int nmm;
  int mm_charge[MAXMM];
  float mm_m[MAXMM];
  float mm_E[MAXMM];
  float mm_p[MAXMM];
  float mm_pt[MAXMM];
  float mm_phi[MAXMM];
  float mm_eta[MAXMM];
  float mm_dR[MAXMM];
  int   mm_leg1[MAXMM];
  int   mm_leg2[MAXMM];

  //tau pairs
  const static int MAXTT=100;
  int ntt;
  int tt_charge[MAXTT];
  float tt_m[MAXTT];
  float tt_E[MAXTT];
  float tt_p[MAXTT];
  float tt_pt[MAXTT];
  float tt_phi[MAXTT];
  float tt_eta[MAXTT];
  float tt_dR[MAXTT];
  int   tt_leg1[MAXTT];
  int   tt_leg2[MAXTT];

  //jet pairs
  const static int MAXJJ=300;
  int njj;
  int jj_charge[MAXJJ];
  float jj_m[MAXJJ];
  float jj_E[MAXJJ];
  float jj_p[MAXJJ];
  float jj_pt[MAXJJ];
  float jj_phi[MAXJJ];
  float jj_eta[MAXJJ];
  float jj_dR[MAXJJ];
  int   jj_leg1[MAXJJ];
  int   jj_leg2[MAXJJ];


  //e-MET pairs
  const static int MAXEMET=MAXELECTRONS;
  int neMet;
  int eMet_charge[MAXEMET];
  float eMet_m[MAXEMET];
  float eMet_E[MAXEMET];
  float eMet_p[MAXEMET];
  float eMet_pt[MAXEMET];
  float eMet_phi[MAXEMET];
  float eMet_eta[MAXEMET];
  float eMet_mT[MAXEMET];
  int eMet_ele[MAXEMET];//link to the electron

  //mu-MET pairs
  const static int MAXMUMET=MAXMUONS;
  int nmuMet;
  int muMet_charge[MAXMUMET];
  float muMet_m[MAXMUMET];
  float muMet_E[MAXMUMET];
  float muMet_p[MAXMUMET];
  float muMet_pt[MAXMUMET];
  float muMet_phi[MAXMUMET];
  float muMet_eta[MAXMUMET];
  float muMet_mT[MAXMUMET];
  int muMet_mu[MAXMUMET];//link to the muon
  


  virtual void DefineBranches(TTree * tr); 

  //void SetBranchAddresses(TTree * tr);
  
private:

  //template<class T> void SetBranchAddressSafe(TTree * tr, const char * label, T * var);
  
};
#endif // _HBBTUPLENEW_HPP
