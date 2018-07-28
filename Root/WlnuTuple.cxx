#include "HbbAnalysis/WlnuTuple.h"

WlnuTuple::WlnuTuple():
  RecoTuple()
{
}

WlnuTuple::~WlnuTuple() {;}

void WlnuTuple::DefineBranches(TTree * tr) {
  RecoTuple::DefineBranches(tr);

  tr->Branch("wlnu_lMet",&wlnu_lMet,"wlnu_lMet/I");

  tr->Branch("wlnu_njet",&wlnu_njet,"wlnu_njet/I");
  tr->Branch("wlnu_jet",&wlnu_jet,"wlnu_jet/I");

  tr->Branch("wlnu_njetfw",&wlnu_njetfw,"wlnu_njetfw/I");
  tr->Branch("wlnu_jetfw",&wlnu_jetfw,"wlnu_jetfw/I");

}


// template <class T> void WlnuTuple::SetBranchAddressSafe(TTree * tr, const char * label, T * var) {
//   if( tr->GetBranch(label) ) {
//     tr->SetBranchAddress(label,var);
//   }
// }
// void WlnuTuple::SetBranchAddresses(TTree * tr) {
//   SetBranchAddressSafe(tr,"eve_num",&eve_num);
// }


