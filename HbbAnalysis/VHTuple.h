#ifndef VHTUPLE
#define VHTUPLE

#include "RecoTuple.h"

class VHTuple : public RecoTuple {
  
public:
  VHTuple();

  ///Define here the block to hold the VH resonance quantities
  const static int MAXVH=200;
  int nvh;
  int vh_charge[MAXVH];
  float vh_m[MAXVH];
  float vh_E[MAXVH];
  float vh_p[MAXVH];
  float vh_pt[MAXVH];
  float vh_phi[MAXVH];
  float vh_eta[MAXVH];
  float vh_dR[MAXVH];
  int   vh_v[MAXVH];//index of V
  int   vh_h[MAXVH];//index of H

  float vh_dPhiHMET[MAXVH];

  float vh_mass[MAXVH];//final mass variable

  ////These are the selected candidates
  int vh;//index of VH resonance candidate

  ///Jets with b-tag requirements
  int vh_nbjet;//number of b-tagged jets
  int vh_bjet1;//leading b-tagged jet
  int vh_bjet2;//subleading b-tagged jet

  ///Jets with standard jet selections
  int vh_njet;//signal candidate jets
  int vh_jet1;//leading signal jet
  int vh_jet2;//leading signal jet
  int vh_jet3;//leading signal jet

  int vh_njetveto;//for central jet veto

  int vh_njetfw;//for forward jet veto
  int vh_jetfw;//leading forward jet


  virtual void DefineBranches(TTree * tr); 

private:
  
};
#endif 
