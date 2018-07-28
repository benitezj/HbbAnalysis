#include "HbbAnalysis/BaseTuple.h"

BaseTuple::BaseTuple(){
}

BaseTuple::~BaseTuple(){;}

void BaseTuple::DefineBranches(TTree * tr) {

  // event properties
  tr->Branch("eve_num",&eve_num,"eve_num/I");
  tr->Branch("eve_run",&eve_run,"eve_run/I");
  tr->Branch("eve_isMC",&eve_isMC,"eve_isMC/I");
  tr->Branch("eve_mc_w",&eve_mc_w,"eve_mc_w/F");
  tr->Branch("eve_mc_num",&eve_mc_num,"eve_mc_num/I");
  tr->Branch("eve_mc_chan",&eve_mc_chan,"eve_mc_chan/I");

  //pileup
  tr->Branch("eve_mu",&eve_mu,"eve_mu/I");
  tr->Branch("nmcpuw",&nmcpuw,"nmcpuw/I");
  tr->Branch("eve_mc_puw",eve_mc_puw,"eve_mc_puw[nmcpuw]/F");

  // MC truth 
  tr->Branch("ntruth",&ntruth,"ntruth/I");
  tr->Branch("truth_m",truth_m,"truth_m[ntruth]/F");
  tr->Branch("truth_p",truth_p,"truth_p[ntruth]/F");
  tr->Branch("truth_pt",truth_pt,"truth_pt[ntruth]/F");
  tr->Branch("truth_eta",truth_eta,"truth_eta[ntruth]/F");
  tr->Branch("truth_phi",truth_phi,"truth_phi[ntruth]/F");
  tr->Branch("truth_status",truth_status,"truth_status[ntruth]/I");
  tr->Branch("truth_pdg",truth_pdg,"truth_pdg[ntruth]/I");


  //MC Truth Processes
  tr->Branch("truth_Zmm",&truth_Zmm,"truth_Zmm/I");
  tr->Branch("truth_Zmm_m1",&truth_Zmm_m1,"truth_Zmm_m1/I");
  tr->Branch("truth_Zmm_m2",&truth_Zmm_m2,"truth_Zmm_m2/I");

  tr->Branch("truth_Zee",&truth_Zee,"truth_Zee/I");
  tr->Branch("truth_Zee_e1",&truth_Zee_e1,"truth_Zee_e1/I");
  tr->Branch("truth_Zee_e2",&truth_Zee_e2,"truth_Zee_e2/I");

  tr->Branch("truth_Wmv",&truth_Wmv,"truth_Wmv/I");
  tr->Branch("truth_Wmv_m",&truth_Wmv_m,"truth_Wmv_m/I");
  tr->Branch("truth_Wmv_v",&truth_Wmv_v,"truth_Wmv_v/I");

  tr->Branch("truth_Wev",&truth_Wev,"truth_Wev/I");
  tr->Branch("truth_Wev_e",&truth_Wev_e,"truth_Wev_e/I");
  tr->Branch("truth_Wev_v",&truth_Wev_v,"truth_Wev_v/I");

  tr->Branch("truth_top",&truth_top,"truth_top/I");
  tr->Branch("truth_top_mm_m1",&truth_top_mm_m1,"truth_top_mm_m1/I");
  tr->Branch("truth_top_mm_m2",&truth_top_mm_m2,"truth_top_mm_m2/I");
  tr->Branch("truth_top_ee_e1",&truth_top_ee_e1,"truth_top_ee_e1/I");
  tr->Branch("truth_top_ee_e2",&truth_top_ee_e2,"truth_top_ee_e2/I");
  tr->Branch("truth_top_em_e",&truth_top_em_e,"truth_top_em_e/I");
  tr->Branch("truth_top_em_m",&truth_top_em_m,"truth_top_em_m/I");
  
  tr->Branch("truth_H0bb",&truth_H0bb,"truth_H0bb/I");
  tr->Branch("truth_H0bb_b1",&truth_H0bb_b1,"truth_H0bb_b1/I");
  tr->Branch("truth_H0bb_b2",&truth_H0bb_b2,"truth_H0bb_b2/I");

  tr->Branch("truth_ZHmmbb",&truth_ZHmmbb,"truth_ZHmmbb/I");
  tr->Branch("truth_ZHeebb",&truth_ZHeebb,"truth_ZHeebb/I");
  tr->Branch("truth_WHmvbb",&truth_WHmvbb,"truth_WHmvbb/I");
  tr->Branch("truth_WHevbb",&truth_WHevbb,"truth_WHevbb/I");


  tr->Branch("truth_RToVH",&truth_RToVH,"truth_RToVH/I");
  tr->Branch("truth_RToVH_V",&truth_RToVH_V,"truth_RToVH_V/I");
  tr->Branch("truth_RToVH_H",&truth_RToVH_H,"truth_RToVH_H/I");
  tr->Branch("truth_RToVH_H_b1",&truth_RToVH_H_b1,"truth_RToVH_H_b1/I");
  tr->Branch("truth_RToVH_H_b2",&truth_RToVH_H_b2,"truth_RToVH_H_b2/I");
  tr->Branch("truth_RToVH_H_dR",&truth_RToVH_H_dR,"truth_RToVH_H_dR/F");


}



