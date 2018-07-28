#include "ZmmPlotter.h"
#include "plotZll.C"

void plotZmm(ZmmPlotter* analysis){
  plotZll(analysis);

  //////Z pt,dR
  analysis->plot("mm_m[zll_ll]/1000",100,50,130,""," mass(#mu^{+}#mu^{-}) (GeV)","",c2,"zll_m");
  analysis->plot("mm_pt[zll_ll]/1000",100,0,150,""," p_{T}(#mu^{+}#mu^{-}) (GeV)","",c2,"zll_pt");
  analysis->plot("mm_dR[zll_ll]",100,0,5,""," #DeltaR(#mu^{+}#mu^{-}) (GeV)","",c1,"zll_dR");

  /////high pT lepton
  analysis->plot("muo_pt[zll_l1]/1000",100,0,150,"","  p_{T}(#mu_{1}) (GeV)","",c2,"zll_l1_pt");
  analysis->plot("muo_eta[zll_l1]",100,-3.0,3.0,""," #eta(#mu_{1})","",c2,"zll_l1_eta");
  //analysis->plot("muo_z0[zll_l1]",100,-50.0,50.0,""," z0(#mu_{1})","",c2,"zll_l1_z0");
  //analysis->plot("muo_d0[zll_l1]",100,-1.0,1.0,""," d0(#mu_{1})","",c2,"zll_l1_d0");
  analysis->plot("muo_ptiso[zll_l1]/muo_pt[zll_l1]",100,0,0.5,"","#mu_{1} track isolation","",c2,"zll_l1_ptiso");
  analysis->plot("muo_etiso[zll_l1]/muo_pt[zll_l1]",100,0,0.5,"","#mu_{1} calo. isolation","",c2,"zll_l1_etiso");

  ////Low pT lepton
  analysis->plot("muo_pt[zll_l2]/1000",100,0,150,""," p_{T}(#mu_{2}) (GeV)","",c2,"zll_l2_pt");
  analysis->plot("muo_eta[zll_l2]",100,-3.0,3.0,""," #eta(#mu_{2})","",c2,"zll_l2_eta");
 
}

