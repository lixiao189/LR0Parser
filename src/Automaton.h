#ifndef __AUTOMATON_H__
#define __AUTOMATON_H__

#include "Item.h"
#include "Production.h"
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <set>

using State = std::vector<std::shared_ptr<Item>>;

class Automaton {
private:
  std::vector<ProductionPtr> rules; // 所有当前文法的产生式
  std::vector<State> states;        // 项目集规范族
  std::set<char> symbols;

public:
  Automaton();
  ~Automaton();

  void add_production(ProductionPtr production);
  void add_symbol(char symbol);
  std::vector<ProductionPtr> get_rules() const;

  void get_closure(State &item_set); // 求项目集闭包
  State compute_goto(State &item_set, char symbol);
  void build_automaon(); // 构建 LR0 自动机

  static bool is_same_state(State &s1, State &s2);
};

#endif // __AUTOMATON_H__