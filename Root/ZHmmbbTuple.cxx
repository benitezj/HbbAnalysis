#include "HbbAnalysis/ZHmmbbTuple.h"

ZHmmbbTuple::ZHmmbbTuple():
  ZHllbbTuple()
{
}

ZHmmbbTuple::~ZHmmbbTuple() {;}

void ZHmmbbTuple::DefineBranches(TTree * tr) {
  
  ZHllbbTuple::DefineBranches(tr);
  
}



