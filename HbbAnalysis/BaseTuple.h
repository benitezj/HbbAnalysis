#ifndef BASETUPLE
#define BASETUPLE

using namespace std;

#include "TTree.h"

class BaseTuple {
 public:
  BaseTuple();
  virtual ~BaseTuple();


  // Event level properties
  int eve_num;
  int eve_run;
  int eve_isMC;
  int eve_mu;
  float eve_mc_w;
  float eve_mc_num;
  float eve_mc_chan;

  ////pile-up weights
  const static int MAXMCPUWEIGHTS=100;
  int nmcpuw;
  float eve_mc_puw[MAXMCPUWEIGHTS];//one for each data/mc period

  //CxAOD Truth variables
   // string          TruthParticle___NominalAux_m_name;
   // vector<float>   *TruthParticle___NominalAuxDyn_m;
   // vector<float>   *TruthParticle___NominalAuxDyn_px;
   // vector<int>     *TruthParticle___NominalAuxDyn_partIndex;
   // vector<int>     *TruthParticle___NominalAuxDyn_pdgId;
   // vector<float>   *TruthParticle___NominalAuxDyn_py;
   // vector<int>     *TruthParticle___NominalAuxDyn_barcode;
   // vector<float>   *TruthParticle___NominalAuxDyn_pz;
   // vector<int>     *TruthParticle___NominalAuxDyn_status;
   // vector<float>   *TruthParticle___NominalAuxDyn_e;

  const static int MAXTRUTH=100;
  int ntruth;
  float truth_m[MAXTRUTH];
  float truth_p[MAXTRUTH];
  float truth_pt[MAXTRUTH];
  float truth_eta[MAXTRUTH];
  float truth_phi[MAXTRUTH];
  //int truth_charge[MAXTRUTH];
  int truth_status[MAXTRUTH];
  int truth_pdg[MAXTRUTH];
  
  //Specific channels
  int truth_Zmm;
  int truth_Zmm_m1;
  int truth_Zmm_m2;

  int truth_Zee;
  int truth_Zee_e1;
  int truth_Zee_e2;

  int truth_Wmv;
  int truth_Wmv_m;
  int truth_Wmv_v;

  int truth_Wev;
  int truth_Wev_e;
  int truth_Wev_v;
  
  int truth_top;
  int truth_top_mm_m1;
  int truth_top_mm_m2;
  int truth_top_ee_e1;
  int truth_top_ee_e2;
  int truth_top_em_e;
  int truth_top_em_m;
  
  int truth_H0bb;
  int truth_H0bb_b1;
  int truth_H0bb_b2;

  //these composites are defined in a special way:
  //A new truth particle will be created from the V and H
  //and will be added at the end of the truth list
  int truth_ZHmmbb;
  int truth_ZHeebb;
  int truth_WHmvbb;
  int truth_WHevbb;


  ///VH resonance analysis
  int truth_RToVH;
  int truth_RToVH_V;
  int truth_RToVH_H;
  int truth_RToVH_H_b1;
  int truth_RToVH_H_b2;
  float truth_RToVH_H_dR;

  virtual void DefineBranches(TTree * tr); 
  
private:
  
};
#endif // _HBBTUPLENEW_HPP
