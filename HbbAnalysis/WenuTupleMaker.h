#ifndef WENUTUPLEMAKER_H
#define WENUTUPLEMAKER_H

#include "HbbAnalysis/WlnuTupleMaker.h"
#include "HbbAnalysis/WenuTuple.h"

class WenuTupleMaker : public WlnuTupleMaker
{
public:
  WenuTupleMaker ();//Default Do not use.
  WenuTupleMaker (std::string configPath);

  virtual EL::StatusCode initialize ();  

  ClassDef(WenuTupleMaker, 1);

private:
  WenuTuple * m_tuple = 0; //!

  virtual EL::StatusCode processEvent ();

};

#endif
