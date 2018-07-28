#include "plotZll.C"

void plotZee(Plotter* analysis){
  plotZll(analysis);

  //////Z pt,dR
  analysis->plot("ee_m[zll_ll]/1000",100,50,130,""," mass(e^{+}e^{-}) (GeV)","",c2,"zll_m");
  analysis->plot("ee_pt[zll_ll]/1000",100,0,150,""," p_{T}(e^{+}e^{-}) (GeV)","",c2,"zll_pt");
  analysis->plot("ee_dR[zll_ll]",100,0,5,""," {#Delta}R(e^{+}e^{-}) (GeV)","",c1,"zll_dR");
  
  //high pT lepton
  analysis->plot("ele_pt[zll_l1]/1000",100,0,150,""," p_T(e_{1}) (GeV)","",c2,"zll_l1_pt");
  analysis->plot("ele_eta[zll_l1]",100,-3,3,""," #eta(e_{1})","",c2,"zll_l1_eta");
  analysis->plot("ele_ptiso[zll_l1]/ele_pt[zll_l1]",100,0,0.5,"","e_{1} track isolation","",c2,"zll_l1_ptiso");
  analysis->plot("ele_etiso[zll_l1]/ele_pt[zll_l1]",100,0,0.5,"","e_{1} calo. isolation","",c2,"zll_l1_etiso");

  //low pT lepton
  analysis->plot("ele_pt[zll_l2]/1000",100,0,150,""," p_T(e_{2}) (GeV)","",c2,"zll_l2_pt");
  analysis->plot("ele_eta[zll_l2]",100,-3,3,""," #eta(e_{2})","",c2,"zll_l2_eta");

}

