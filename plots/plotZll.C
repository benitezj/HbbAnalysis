#include "Plotter.h"
#include "plotEvent.C"

void plotZll(Plotter* analysis){
  plotEvent(analysis);

  //Jets
  analysis->plot("zll_njet",10,0,10,""," # of central jets","",c2,"zll_njet");
  analysis->plot("jet_pt[zll_jet]/1000",100,0,200,"zll_jet>=0","lead central jet p_{T} (GeV)","",c2,"zll_leadjet_pt");
  analysis->plot("jet_eta[zll_jet]",100,-5.0,5.0,"zll_jet>=0"," lead central jet #eta","",c2,"zll_leadjet_eta");
  analysis->plot("jet_sv1ip3d[zll_jet]",100,-10,10,"zll_jet>=0"," lead central jet SV1_IP3D","",c2,"zll_leadjet_sv1ip3d");

  analysis->plot("zll_njetfw",10,0,10,""," # of forward jets","",c2,"zll_njetfw");
  analysis->plot("jet_pt[zll_jetfw]/1000",100,0,200,"zll_jetfw>=0","lead forward jet p_{T} (GeV)","",c2,"zll_leadjetfw_pt");
  analysis->plot("jet_eta[zll_jetfw]",100,-5.0,5.0,"zll_jetfw>=0"," lead forward jet #eta","",c2,"zll_leadjetfw_eta");
 
}
