#include "HbbAnalysis/WHmnubbTuple.h"

WHmnubbTuple::WHmnubbTuple():
  WHlnubbTuple()
{
}

WHmnubbTuple::~WHmnubbTuple() {;}

void WHmnubbTuple::DefineBranches(TTree * tr) {
  
  WHlnubbTuple::DefineBranches(tr);
  
}



