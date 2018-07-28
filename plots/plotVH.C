#include "Plotter.h"
#include "plotEvent.C"

void plotVH(Plotter* analysis){
  plotEvent(analysis);

  //VH
  analysis->plot("vh_m[vh]/1000",50,0,1000,""," VH mass [GeV]","",c2,"vh_m",1);
  analysis->plot("vh_mass[vh]/1000",50,0,1000,""," VH mass [GeV]","",c2,"vh_m_HmassConstrained",1);
  analysis->plot("vh_pt[vh]/1000",50,0,500,""," VH p_{T} [GeV]","",c2,"vh_pt");
  analysis->plot("vh_dR[vh]",50,0,10,""," #DeltaR(V,H)","",c1,"vh_dRVH");
  analysis->plot("vh_dPhiHMET[vh]",50,0,10,""," #Delta#phi(H,MET)","",c1,"vh_dPhiHMET");

  //H
  analysis->plot("jj_m[vh_h[vh]]/1000",25,0,500,""," M_{jj} [GeV]","",c2,"vh_h_m",1);
  analysis->plot("jj_pt[vh_h[vh]]/1000",50,0,500,""," p_{T}_{jj} [GeV]","",c2,"vh_h_pt");
  analysis->plot("jj_dR[vh_h[vh]]",50,0,10,""," #DeltaR_{jj} [GeV]","",c1,"vh_h_dRjj");

  ///Higgs Jets (pT ordered)
  analysis->plot("vh_njet",10,0,10,""," # of central jets","",c2,"vh_njet",1);
  //Higgs jet1
  analysis->plot("jet_pt[jj_leg1[vh_h[vh]]]/1000",40,.0,200,"","leading jet p_{T}","",c2,"vh_leadjet_pt");
  analysis->plot("jet_eta[jj_leg1[vh_h[vh]]]",20,-5.0,5.0,""," leading jet #eta","",c2,"vh_leadjet_eta");
  //Higgs jet2
  analysis->plot("jet_pt[jj_leg2[vh_h[vh]]]/1000",40,.0,200,"","subleading jet p_{T}","",c2,"vh_subleadjet_pt");
  analysis->plot("jet_eta[jj_leg2[vh_h[vh]]]",20,-5.0,5.0,"","subleading jet #eta","",c2,"vh_subleadjet_eta");
  //third jet: not tracked at the moment)

  
  //////b-tagged jets
  analysis->plot("vh_nbjet",4,0,4,""," # of b-tagged jets","",c2,"vh_nbjet");
  ////b-jet1 
  analysis->plot("jet_pt[vh_bjet1]/1000",40,.0,200,"","leading b-jet p_{T}","",c2,"vh_leadbjet_pt");
  analysis->plot("jet_eta[vh_bjet1]",20,-5.0,5.0,""," leading b-jet #eta","",c2,"vh_leadbjet_eta");
  analysis->plot("jet_sv1ip3d[vh_bjet1]",50,-20,30,"","leading b-jet SV1_IP3D","",c2,"vh_leadbjet_sv1ip3d");
  ////b-jet2 (for 2 tags)
  analysis->plot("jet_pt[vh_bjet2]/1000",40,.0,200,"vh_nbjet>1","subleading b-jet p_{T}","",c2,"vh_subleadbjet_pt");
  analysis->plot("jet_eta[vh_bjet2]",20,-5.0,5.0,"vh_nbjet>1","subleading b-jet #eta","",c2,"vh_subleadbjet_eta");
  analysis->plot("jet_sv1ip3d[vh_bjet2]",50,-20,30,"vh_nbjet>1","subleading b-jet SV1_IP3D","",c2,"vh_subleadbjet_sv1ip3d");


  //Forward jets
  analysis->plot("vh_njetfw",10,0,10,""," # of forward jets","",c2,"vh_njetfw");
  analysis->plot("jet_pt[vh_jetfw]/1000",40,0,200,"vh_njetfw>0","lead forward jet p_{T} [GeV]","",c2,"vh_extraleadjetfw_pt");
  analysis->plot("jet_eta[vh_jetfw]",20,-5.0,5.0,"vh_njetfw>0","lead forward jet #eta","",c2,"vh_extraleadjetfw_eta");
 
}
