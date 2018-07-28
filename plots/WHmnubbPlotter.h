#ifndef WHmnubbPlotter_H
#define WHmnubbPlotter_H

#include "Plotter.h"

class WHmnubbPlotter :  public  Plotter {

public:
  
  WHmnubbPlotter();
  WHmnubbPlotter(const char * name, const char * title);
  virtual ~WHmnubbPlotter();
  
  ClassDef(WHmnubbPlotter, 1);
};

#endif 
