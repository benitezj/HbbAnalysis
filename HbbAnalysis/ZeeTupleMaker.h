#ifndef ZEETUPLEMAKER_H
#define ZEETUPLEMAKER_H

#include "HbbAnalysis/ZllTupleMaker.h"
#include "HbbAnalysis/ZeeTuple.h"

class ZeeTupleMaker : public ZllTupleMaker
{
public:
  ZeeTupleMaker ();//Default Do not use.
  ZeeTupleMaker (std::string configPath);

  virtual EL::StatusCode initialize ();

  ClassDef(ZeeTupleMaker, 1);

private:
  ZeeTuple * m_tuple = 0; //!

  virtual EL::StatusCode processEvent();

};

#endif
