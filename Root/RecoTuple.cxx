#include "HbbAnalysis/RecoTuple.h"

RecoTuple::RecoTuple():
  BaseTuple()
{
}

RecoTuple::~RecoTuple() {;}

void RecoTuple::DefineBranches(TTree * tr) {
  BaseTuple::DefineBranches(tr);

  // vertices
  tr->Branch("nvtx",&nvtx,"nvtx/I");
  tr->Branch("vtx_x",vtx_x,"vtx_x[nvtx]/F");
  tr->Branch("vtx_y",vtx_y,"vtx_y[nvtx]/F");
  tr->Branch("vtx_z",vtx_z,"vtx_z[nvtx]/F");

  //met
  tr->Branch("met_pt",&met_pt,"met_pt/F");
  tr->Branch("met_eta",&met_eta,"met_eta/F");
  tr->Branch("met_phi",&met_phi,"met_phi/F");
  tr->Branch("met_px",&met_px,"met_px/F");
  tr->Branch("met_py",&met_py,"met_py/F");

  // electrons
  tr->Branch("nele",&nele,"nele/I");
  tr->Branch("ele_charge",ele_charge,"ele_charge[nele]/I");
  tr->Branch("ele_E",ele_E,"ele_E[nele]/F");
  tr->Branch("ele_m", ele_m, "ele_m[nele]/F");
  tr->Branch("ele_pt", ele_pt, "ele_pt[nele]/F");
  tr->Branch("ele_phi",ele_phi,"ele_phi[nele]/F");
  tr->Branch("ele_eta",ele_eta,"ele_eta[nele]/F");
  tr->Branch("ele_z0",ele_z0,"ele_z0[nele]/F");
  tr->Branch("ele_d0",ele_d0,"ele_d0[nele]/F");
  tr->Branch("ele_ptiso",ele_ptiso,"ele_ptiso[nele]/F");
  tr->Branch("ele_etiso",ele_etiso,"ele_etiso[nele]/F");
  tr->Branch("ele_idVHl",ele_idVHl,"ele_idVHl[nele]/I");
  tr->Branch("ele_idZHl",ele_idZHl,"ele_idZHl[nele]/I");
  tr->Branch("ele_idWHl",ele_idWHl,"ele_idWHl[nele]/I");
  tr->Branch("ele_passor",ele_passor,"ele_passor[nele]/I");

  // muons
  tr->Branch("nmuo",&nmuo,"nmuo/I");
  tr->Branch("muo_charge",muo_charge,"muo_charge[nmuo]/I");
  tr->Branch("muo_E",muo_E,"muo_E[nmuo]/F");
  tr->Branch("muo_m",muo_m,"muo_m[nmuo]/F");
  tr->Branch("muo_pt" ,muo_pt, "muo_pt[nmuo]/F");
  tr->Branch("muo_phi",muo_phi,"muo_phi[nmuo]/F");
  tr->Branch("muo_eta",muo_eta,"muo_eta[nmuo]/F");
  tr->Branch("muo_z0",muo_z0,"muo_z0[nmuo]/F");
  tr->Branch("muo_d0",muo_d0,"muo_d0[nmuo]/F");
  tr->Branch("muo_ptiso",muo_ptiso,"muo_ptiso[nmuo]/F");
  tr->Branch("muo_etiso",muo_etiso,"muo_etiso[nmuo]/F");
  tr->Branch("muo_idVHl",muo_idVHl,"muo_idVHl[nmuo]/I");
  tr->Branch("muo_idZH",muo_idZH,"muo_idZH[nmuo]/I");
  tr->Branch("muo_idWH",muo_idWH,"muo_idWH[nmuo]/I");
  tr->Branch("muo_passor",muo_passor,"muo_passor[nmuo]/I");
  

  // taus
  tr->Branch("ntau",&ntau,"ntau/I");
  tr->Branch("tau_charge",tau_charge,"tau_charge[ntau]/I");
  tr->Branch("tau_E",  tau_E,  "tau_E[ntau]/F");
  tr->Branch("tau_m", tau_m, "tau_m[ntau]/F");
  tr->Branch("tau_pt", tau_pt, "tau_pt[ntau]/F");
  tr->Branch("tau_phi",tau_phi,"tau_phi[ntau]/F");
  tr->Branch("tau_eta",tau_eta,"tau_eta[ntau]/F");
  tr->Branch("tau_passor",tau_passor,"tau_passor[ntau]/I");

  // jets
  tr->Branch("njet",&njet,"njet/I");
  tr->Branch("jet_charge",jet_charge,"jet_charge[njet]/I");
  tr->Branch("jet_E",jet_E,"jet_E[njet]/F");
  tr->Branch("jet_m",jet_m,"jet_m[njet]/F");
  tr->Branch("jet_pt", jet_pt,"jet_pt[njet]/F");
  tr->Branch("jet_phi",jet_phi,"jet_phi[njet]/F");
  tr->Branch("jet_eta",jet_eta,"jet_eta[njet]/F");

  tr->Branch("jet_ntrk",jet_ntrk,"jet_ntrk[njet]/I");
  tr->Branch("jet_massvx",jet_massvx,"jet_massvx[njet]/F");
  tr->Branch("jet_jvf",jet_jvf,"jet_jvf[njet]/F");
  tr->Branch("jet_normdist",jet_normdist,"jet_normdist[njet]/F");

  tr->Branch("jet_good",jet_good,"jet_good[njet]/I");
  tr->Branch("jet_passor",jet_passor,"jet_passor[njet]/I");

  tr->Branch("jet_mv1",jet_mv1,"jet_mv1[njet]/F");
  tr->Branch("jet_sv1ip3d",jet_sv1ip3d,"jet_sv1ip3d[njet]/F");
  tr->Branch("jet_mv2c00",jet_mv2c00,"jet_mv2c00[njet]/F");
  tr->Branch("jet_mv2c10",jet_mv2c10,"jet_mv2c10[njet]/F");
  tr->Branch("jet_mv2c20",jet_mv2c20,"jet_mv2c20[njet]/F");
  tr->Branch("jet_mvb",jet_mvb,"jet_mvb[njet]/F");




  //electron pairs
  tr->Branch("nee",&nee,"nee/I");
  tr->Branch("ee_charge",ee_charge,"ee_charge[nee]/I");
  tr->Branch("ee_m",ee_m,"ee_m[nee]/F");
  tr->Branch("ee_E",ee_E,"ee_E[nee]/F");
  tr->Branch("ee_p" ,ee_p, "ee_p[nee]/F");
  tr->Branch("ee_pt" ,ee_pt, "ee_pt[nee]/F");
  tr->Branch("ee_phi",ee_phi,"ee_phi[nee]/F");
  tr->Branch("ee_eta",ee_eta,"ee_eta[nee]/F");
  tr->Branch("ee_dR",ee_dR,"ee_dR[nee]/F");
  tr->Branch("ee_leg1",ee_leg1,"ee_leg1[nee]/I");
  tr->Branch("ee_leg2",ee_leg2,"ee_leg2[nee]/I");

  //muon pairs
  tr->Branch("nmm",&nmm,"nmm/I");
  tr->Branch("mm_charge",mm_charge,"mm_charge[nmm]/I");
  tr->Branch("mm_m",mm_m,"mm_m[nmm]/F");
  tr->Branch("mm_E",mm_E,"mm_E[nmm]/F");
  tr->Branch("mm_p" ,mm_p, "mm_p[nmm]/F");
  tr->Branch("mm_pt" ,mm_pt, "mm_pt[nmm]/F");
  tr->Branch("mm_phi",mm_phi,"mm_phi[nmm]/F");
  tr->Branch("mm_eta",mm_eta,"mm_eta[nmm]/F");
  tr->Branch("mm_dR",mm_dR,"mm_dR[nmm]/F");
  tr->Branch("mm_leg1",mm_leg1,"mm_leg1[nmm]/I");
  tr->Branch("mm_leg2",mm_leg2,"mm_leg2[nmm]/I");


  //muon pairs
  tr->Branch("ntt",&ntt,"ntt/I");
  tr->Branch("tt_charge",tt_charge,"tt_charge[ntt]/I");
  tr->Branch("tt_m",tt_m,"tt_m[ntt]/F");
  tr->Branch("tt_E",tt_E,"tt_E[ntt]/F");
  tr->Branch("tt_p" ,tt_p, "tt_p[ntt]/F");
  tr->Branch("tt_pt" ,tt_pt, "tt_pt[ntt]/F");
  tr->Branch("tt_phi",tt_phi,"tt_phi[ntt]/F");
  tr->Branch("tt_eta",tt_eta,"tt_eta[ntt]/F");
  tr->Branch("tt_dR",tt_dR,"tt_dR[ntt]/F");
  tr->Branch("tt_leg1",tt_leg1,"tt_leg1[ntt]/I");
  tr->Branch("tt_leg2",tt_leg2,"tt_leg2[ntt]/I");


  //jet pairs
  tr->Branch("njj",&njj,"njj/I");
  tr->Branch("jj_charge",jj_charge,"jj_charge[njj]/I");
  tr->Branch("jj_m",jj_m,"jj_m[njj]/F");
  tr->Branch("jj_E",jj_E,"jj_E[njj]/F");
  tr->Branch("jj_p" ,jj_pt, "jj_p[njj]/F");
  tr->Branch("jj_pt" ,jj_pt, "jj_pt[njj]/F");
  tr->Branch("jj_phi",jj_phi,"jj_phi[njj]/F");
  tr->Branch("jj_eta",jj_eta,"jj_eta[njj]/F");
  tr->Branch("jj_dR",jj_dR,"jj_dR[njj]/F");
  tr->Branch("jj_leg1",jj_leg1,"jj_leg1[njj]/I");
  tr->Branch("jj_leg2",jj_leg2,"jj_leg2[njj]/I");


  //e-Met
  tr->Branch("neMet",&neMet,"neMet/I");
  tr->Branch("eMet_charge",eMet_charge,"eMet_charge[neMet]/I");
  tr->Branch("eMet_m",eMet_m,"eMet_m[neMet]/F");
  tr->Branch("eMet_E",eMet_E,"eMet_E[neMet]/F");
  tr->Branch("eMet_p" ,eMet_p, "eMet_p[neMet]/F");
  tr->Branch("eMet_pt" ,eMet_pt, "eMet_pt[neMet]/F");
  tr->Branch("eMet_phi",eMet_phi,"eMet_phi[neMet]/F");
  tr->Branch("eMet_eta",eMet_eta,"eMet_eta[neMet]/F");
  tr->Branch("eMet_mT",eMet_mT,"eMet_mT[neMet]/F");
  tr->Branch("eMet_ele",eMet_ele,"eMet_ele[neMet]/I");

  //mu-Met
  tr->Branch("nmuMet",&nmuMet,"nmuMet/I");
  tr->Branch("muMet_charge",muMet_charge,"muMet_charge[nmuMet]/I");
  tr->Branch("muMet_m",muMet_m,"muMet_m[nmuMet]/F");
  tr->Branch("muMet_E",muMet_E,"muMet_E[nmuMet]/F");
  tr->Branch("muMet_p" ,muMet_p, "muMet_p[nmuMet]/F");
  tr->Branch("muMet_pt" ,muMet_pt, "muMet_pt[nmuMet]/F");
  tr->Branch("muMet_phi",muMet_phi,"muMet_phi[nmuMet]/F");
  tr->Branch("muMet_eta",muMet_eta,"muMet_eta[nmuMet]/F");
  tr->Branch("muMet_mT",muMet_mT,"muMet_mT[nmuMet]/F");
  tr->Branch("muMet_mu",muMet_mu,"muMet_mu[nmuMet]/I");


}


// template <class T> void RecoTuple::SetBranchAddressSafe(TTree * tr, const char * label, T * var) {
//   if( tr->GetBranch(label) ) {
//     tr->SetBranchAddress(label,var);
//   }
// }
// void RecoTuple::SetBranchAddresses(TTree * tr) {
//   SetBranchAddressSafe(tr,"eve_num",&eve_num);
// }


