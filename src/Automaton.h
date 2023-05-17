#ifndef __AUTOMATON_H__
#define __AUTOMATON_H__

#include "Item.h"
#include "Production.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <vector>

using State = std::vector<std::shared_ptr<Item>>;

class Automaton {
private:
  std::vector<ProductionPtr> rules; // 所有当前文法的产生式
  std::vector<State> states;        // 项目集规范族
  std::set<char> terminals;         // 终结符集
  std::set<char> none_terminals;    // 非终结符集
  std::set<char> symbols; // 符号集，包括终结符和非终结符
  std::map<int, std::map<char, int>> transitions; // 状态转移函数

public:
  Automaton();
  ~Automaton();

  void add_production(ProductionPtr production);
  void add_terminals(char symbol);
  void add_noneterminals(char symbol);
  void add_symbol(char symbol);

  std::vector<ProductionPtr> &get_rules();
  std::map<int, std::map<char, int>> &get_transitions();
  std::set<char> &get_symbols();
  std::set<char> &get_terminals();
  std::set<char> &get_noneterminals();
  std::vector<State> &get_states();

  void get_closure(State &item_set); // 求项目集闭包
  State compute_goto(State &item_set, char symbol);
  void build_automaton(); // 构建 LR0 自动机

  static bool is_same_state(State &s1, State &s2);
};

#endif // __AUTOMATON_H__