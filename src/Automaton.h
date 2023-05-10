#ifndef __AUTOMATON_H__
#define __AUTOMATON_H__

#include "Item.h"
#include "Production.h"
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using ItemSet = std::vector<std::shared_ptr<Item>>;

class Automaton {
private:
  std::vector<ProductionPtr> rules; // 所有当前文法的产生式
  std::vector<ItemSet> states;      // 项目集规范族

public:
  Automaton();
  ~Automaton();

  void add_production(ProductionPtr production);
  std::vector<ProductionPtr> get_rules() const;

  void get_closure(ItemSet &item_set); // 求项目集闭包
  void build_automaon();               // 构建 LR0 自动机
};

#endif // __AUTOMATON_H__