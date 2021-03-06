
#ifndef __Extension_h__
#define __Extension_h__

#include "../stylesheet/Selector.h"

/**
 * 
 */
class Extension {
private:
  Selector target;
  Selector extension;
  bool all;
  
public:
  Extension();
  Extension(bool all);
  virtual ~Extension();

  Selector& getTarget();
  Selector& getExtension();

  void setExtension(Selector &selector);

  void updateSelector(Selector& s) const;
  void replaceInSelector(Selector &s) const;
};

#endif
