#ifndef WHLNUBBTUPLEMAKER_H
#define WHLNUBBTUPLEMAKER_H

#include "HbbAnalysis/VHTupleMaker.h"
#include "HbbAnalysis/WHlnubbTuple.h"

class WHlnubbTupleMaker : public VHTupleMaker
{
public:
  WHlnubbTupleMaker ();//Default Do not use.
  WHlnubbTupleMaker (std::string configPath);

  virtual EL::StatusCode initialize ();
  
  // this is needed to distribute the algorithm to the workers
  ClassDef(WHlnubbTupleMaker, 1);

protected:
 
  WHlnubbTuple * m_tuple = 0 ; //!
  TLorentzVector lp4;
  

  virtual EL::StatusCode processEvent();

  virtual bool jetOverlap(int jetindex); 
private:

};

#endif
