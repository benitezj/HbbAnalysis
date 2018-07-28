#ifndef WHMNUBBTUPLEMAKER_H
#define WHMNUBBTUPLEMAKER_H

#include "HbbAnalysis/WHlnubbTupleMaker.h"
#include "HbbAnalysis/WHmnubbTuple.h"

class WHmnubbTupleMaker : public WHlnubbTupleMaker
{
public:
  WHmnubbTupleMaker ();//Default Do not use.
  WHmnubbTupleMaker (std::string configPath);

  virtual EL::StatusCode initialize ();

  EL::StatusCode processMuMETBB();  
  

  ClassDef(WHmnubbTupleMaker, 1);

private:
  
  WHmnubbTuple * m_tuple =0 ; //!

  virtual EL::StatusCode processEvent();
 
};

#endif
