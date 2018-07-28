#ifndef WLNUTUPLE
#define WLNUTUPLE

#include "RecoTuple.h"

class WlnuTuple : public RecoTuple {
 public:
  WlnuTuple();
  ~WlnuTuple();


  int wlnu_lMet;//index of selected lepton-Met pair, should be the same as that of the lepton 

  int wlnu_njet;//# of central jets after overlap removal
  int wlnu_jet;//index of leading central jet after overlap removal

  int wlnu_njetfw;//# of forward jets after overlap removal
  int wlnu_jetfw;//index of leading fw jet after overlap removal


  virtual void DefineBranches(TTree * tr); 
  
  //void SetBranchAddresses(TTree * tr);
  
 private:

  //template<class T> void SetBranchAddressSafe(TTree * tr, const char * label, T * var);
  
};
#endif 
