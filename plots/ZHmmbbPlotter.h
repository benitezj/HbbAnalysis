#ifndef ZHmmbbPlotter_H
#define ZHmmbbPlotter_H

#include "Plotter.h"

class ZHmmbbPlotter :  public  Plotter {

public:
  
  ZHmmbbPlotter();
  ZHmmbbPlotter(const char * name, const char * title);
  virtual ~ZHmmbbPlotter();
  
  ClassDef(ZHmmbbPlotter, 1);
};

#endif 
