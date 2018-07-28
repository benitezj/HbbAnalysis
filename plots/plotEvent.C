#include "Plotter.h"

plotEvent(Plotter* analysis){
  ///////pile up
  analysis->plot("nvtx",40,0,40,"","# of rec. vertices","",c2,"nvtx");
  analysis->plot("eve_mu",40,0,40,"","# of interactions","",c2,"mu");
  
  //MET
  analysis->plot("met_pt/1000",50,0,300,""," MET (GeV)","",c2,"met");
  analysis->plot("met_phi",70,-3.5,3.5,""," MET Phi ","",c2,"metphi");

}
