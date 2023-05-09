#include "Automaton.h"
#include "Item.h"
#include <iostream>
#include <ostream>
#include <vector>

Automaton::Automaton() {}

Automaton::~Automaton() {}

void Automaton::add_production(Production production) { this->rules.push_back(production); }

std::vector<Production> Automaton::get_rules() const { return this->rules; }

/**
 * @brief 求项目集闭包
 *
 * @param item_set 项目集
 */
void Automaton::get_closure(ItemSet &item_set) {
  if (item_set.empty()) {
    std::cout << "Item set is empty!" << std::endl;
    return;
  }

  // 求闭包
  auto prev_size = 0;
  while (prev_size != item_set.size()) {
    prev_size = item_set.size();
    for (auto &item : item_set) {
      auto dot_pos = item.get_dot_pos();
      auto production = item.get_production();

      if (dot_pos < production.get_rhs().size()) {
        auto next_char = production.get_rhs()[dot_pos];
        for (auto rule : rules) {
          if (rule.get_lhs()[0] == next_char) {
            Item new_item(rule, 0);

            if (std::find(item_set.begin(), item_set.end(), new_item) == item_set.end()) {
              item_set.push_back(new_item);
            }
          }
        }
      }
    }
  }
}

/**
 * @brief 构建自动机
 *
 */
void Automaton::build_automaon() {
  if (rules.empty()) {
    std::cout << "No production rules!" << std::endl;
    return;
  }

  // 构建初始状态
  Item initial_item(rules[rules.size() - 1], 0);
  ItemSet initial_item_set;
  initial_item_set.push_back(initial_item);
  get_closure(initial_item_set);
  item_sets.push_back(initial_item_set);

  // Debug: Output the initial item set
  std::cout << "Initial item set: " << std::endl;
  for (auto item : initial_item_set) {
    std::cout << item.to_string() << std::endl;
  }
}