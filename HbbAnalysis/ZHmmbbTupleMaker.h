#ifndef ZHMMBBTUPLEMAKER_H
#define ZHMMBBTUPLEMAKER_H

#include "HbbAnalysis/ZHllbbTupleMaker.h"
#include "HbbAnalysis/ZHmmbbTuple.h"

class ZHmmbbTupleMaker : public ZHllbbTupleMaker
{
public:
  ZHmmbbTupleMaker ();//Default Do not use.
  ZHmmbbTupleMaker (std::string configPath);

  virtual EL::StatusCode initialize ();

  EL::StatusCode processMMBB();  
  

  ClassDef(ZHmmbbTupleMaker, 1);

private:
  
  ZHmmbbTuple * m_tuple =0 ; //!

  virtual EL::StatusCode processEvent();
 
};

#endif
