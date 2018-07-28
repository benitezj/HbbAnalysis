#include "Plotter.h"
#include "plotEvent.C"

void plotWlnu(Plotter* analysis){
  plotEvent(analysis);
  
  //Jets
  analysis->plot("wlnu_njet",10,0,10,""," # of central jets","",c2,"wlnu_njet");
  analysis->plot("jet_pt[wlnu_jet]/1000",100,0,100,"wlnu_njet>0","lead central jet p_{T} (GeV)","",c2,"wlnu_leadjet_pt");
  analysis->plot("jet_eta[wlnu_jet]",100,-3.0,3.0,"wlnu_njet>0"," lead central jet #eta","",c2,"wlnu_leadjet_eta");
  analysis->plot("jet_sv1ip3d[wlnu_jet]",100,-10,10,"wlnu_njet>0"," lead central jet SV1_IP3D","",c2,"wlnu_leadjet_sv1ip3d");

  analysis->plot("wlnu_njetfw",10,0,10,""," # of forward jets","",c2,"wlnu_njetfw");
  analysis->plot("jet_pt[wlnu_jetfw]/1000",100,0,100,"wlnu_njetfw>0","lead forward jet p_{T} (GeV)","",c2,"wlnu_leadjetfw_pt");
  analysis->plot("jet_eta[wlnu_jetfw]",100,-3.0,3.0,"wlnu_njetfw>0"," lead forward jet #eta","",c2,"wlnu_leadjetfw_eta");
 
 
}
