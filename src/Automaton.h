#ifndef __AUTOMATON_H__
#define __AUTOMATON_H__

#include "Production.h"
#include <vector>
class Automaton {
private:
  std::vector<Production> productions;
public:
  Automaton();
  ~Automaton();
  
  void add_production(Production production);
  std::vector<Production> get_productions() const;
};

#endif // __AUTOMATON_H__