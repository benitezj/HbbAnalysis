#ifndef ZMMTUPLEMAKER_H
#define ZMMTUPLEMAKER_H

#include "HbbAnalysis/ZllTupleMaker.h"
#include "HbbAnalysis/ZmmTuple.h"

class ZmmTupleMaker : public ZllTupleMaker
{
public:
  ZmmTupleMaker ();//Default Do not use.
  ZmmTupleMaker (std::string configPath);

  virtual EL::StatusCode initialize ();

  ClassDef(ZmmTupleMaker, 1);

private:
  
  ZmmTuple * m_tuple =0 ; //!

  virtual EL::StatusCode processEvent();
 
};

#endif
