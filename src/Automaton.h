#ifndef __AUTOMATON_H__
#define __AUTOMATON_H__

#include "Item.h"
#include "Production.h"
#include <iostream>
#include <vector>
#include <map>

using ItemSet = std::vector<Item>;

class Automaton {
private:
  std::vector<Production> rules; // 所有当前文法的产生式
  std::vector<ItemSet> item_sets;               // 项目集规范族

public:
  Automaton();
  ~Automaton();

  void add_production(Production production);
  std::vector<Production> get_rules() const;

  void get_closure(ItemSet &item_set); // 求项目集闭包
  void build_automaon(); // 构建 LR0 自动机
};

#endif // __AUTOMATON_H__