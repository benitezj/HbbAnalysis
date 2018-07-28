#include "HbbAnalysis/VHTuple.h"

VHTuple::VHTuple():
  RecoTuple()
{
}

void VHTuple::DefineBranches(TTree * tr) {
  RecoTuple::DefineBranches(tr);

  tr->Branch("nvh",&nvh,"nvh/I");
  tr->Branch("vh_charge",vh_charge,"vh_charge[nvh]/I");
  tr->Branch("vh_m",vh_m,"vh_m[nvh]/F");
  tr->Branch("vh_E",vh_E,"vh_E[nvh]/F");
  tr->Branch("vh_p" ,vh_p, "vh_p[nvh]/F");
  tr->Branch("vh_pt" ,vh_pt, "vh_pt[nvh]/F");
  tr->Branch("vh_phi",vh_phi,"vh_phi[nvh]/F");
  tr->Branch("vh_eta",vh_eta,"vh_eta[nvh]/F");
  tr->Branch("vh_dR",vh_dR,"vh_dR[nvh]/F");
  tr->Branch("vh_v",vh_v,"vh_v[nvh]/I");
  tr->Branch("vh_h",vh_h,"vh_h[nvh]/I");

  tr->Branch("vh_dPhiHMET",vh_dPhiHMET,"vh_dPhiHMET[nvh]/F");

  tr->Branch("vh_mass",vh_mass,"vh_mass[nvh]/F");

  tr->Branch("vh",&vh,"vh/I");

  tr->Branch("vh_nbjet",&vh_nbjet,"vh_nbjet/I");
  tr->Branch("vh_bjet1",&vh_bjet1,"vh_bjet1/I");
  tr->Branch("vh_bjet2",&vh_bjet2,"vh_bjet2/I");

  tr->Branch("vh_njet",&vh_njet,"vh_njet/I");
  tr->Branch("vh_jet1",&vh_jet1,"vh_jet1/I");
  tr->Branch("vh_jet2",&vh_jet2,"vh_jet2/I");
  tr->Branch("vh_jet3",&vh_jet3,"vh_jet3/I");

  tr->Branch("vh_njetveto",&vh_njetveto,"vh_njetveto/I");

  tr->Branch("vh_njetfw",&vh_njetfw,"vh_njetfw/I");
  tr->Branch("vh_jetfw",&vh_jetfw,"vh_jetfw/I");

}


