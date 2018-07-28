#ifndef WMUNUTUPLEMAKER_H
#define WMUNUTUPLEMAKER_H

#include "HbbAnalysis/WlnuTupleMaker.h"
#include "HbbAnalysis/WmunuTuple.h"

class WmunuTupleMaker : public WlnuTupleMaker
{
public:
  WmunuTupleMaker ();//Default Do not use.
  WmunuTupleMaker (std::string configPath);

  virtual EL::StatusCode initialize ();  

  ClassDef(WmunuTupleMaker, 1);

protected:
  WmunuTuple * m_tuple = 0; //!
  
  virtual EL::StatusCode processEvent ();
  
};

#endif
