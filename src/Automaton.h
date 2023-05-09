#ifndef __AUTOMATON_H__
#define __AUTOMATON_H__

#include "Production.h"
#include <vector>
class Automaton {
private:
  std::vector<Production> rules; // 所有当前文法的产生式

public:
  Automaton();
  ~Automaton();

  void add_production(Production production);
  std::vector<Production> get_rules() const;
};

#endif // __AUTOMATON_H__