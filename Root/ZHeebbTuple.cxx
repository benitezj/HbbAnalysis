#include "HbbAnalysis/ZHeebbTuple.h"

ZHeebbTuple::ZHeebbTuple():
  ZHllbbTuple()
{
}

ZHeebbTuple::~ZHeebbTuple() {;}

void ZHeebbTuple::DefineBranches(TTree * tr) {
  
  ZHllbbTuple::DefineBranches(tr);
  
}



