#include "HbbAnalysis/ZllTuple.h"

ZllTuple::ZllTuple():
  RecoTuple()
{
}

ZllTuple::~ZllTuple() {;}

void ZllTuple::DefineBranches(TTree * tr) {
  RecoTuple::DefineBranches(tr);

  tr->Branch("zll_ll",&zll_ll,"zll_ll/I");
  tr->Branch("zll_l1",&zll_l1,"zll_l1/I");
  tr->Branch("zll_l2",&zll_l2,"zll_l2/I");

  tr->Branch("zll_njet",&zll_njet,"zll_njet/I");
  tr->Branch("zll_jet",&zll_jet,"zll_jet/I");

  tr->Branch("zll_njetfw",&zll_njetfw,"zll_njetfw/I");
  tr->Branch("zll_jetfw",&zll_jetfw,"zll_jetfw/I");

}


// template <class T> void ZllTuple::SetBranchAddressSafe(TTree * tr, const char * label, T * var) {
//   if( tr->GetBranch(label) ) {
//     tr->SetBranchAddress(label,var);
//   }
// }
// void ZllTuple::SetBranchAddresses(TTree * tr) {
//   SetBranchAddressSafe(tr,"eve_num",&eve_num);
// }


