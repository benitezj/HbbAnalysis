#ifndef ZLLTUPLE
#define ZLLTUPLE

#include "RecoTuple.h"

class ZllTuple : public RecoTuple {
 public:
  ZllTuple();
  ~ZllTuple();

  int zll_ll;//index of ll pair

  int zll_l1;//leading leg
  int zll_l2;//subleading leg

  int zll_njet;//# of central jets after overlap cleaning
  int zll_jet;//index of leading central jet after overlap cleaning

  int zll_njetfw;//# of forward jets after overlap cleaning
  int zll_jetfw;//index of leading fw jet after overlap cleaning


  virtual void DefineBranches(TTree * tr); 

  //void SetBranchAddresses(TTree * tr);
  
 private:

  //template<class T> void SetBranchAddressSafe(TTree * tr, const char * label, T * var);
  
};
#endif 
