#include "Automaton.h"
#include "Item.h"
#include "Production.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

Automaton::Automaton() {}

Automaton::~Automaton() {}

void Automaton::add_production(ProductionPtr production) { this->rules.push_back(production); }

std::vector<ProductionPtr> Automaton::get_rules() const { return this->rules; }

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
    for (auto item : item_set) {
      auto dot_pos = item->get_dot_pos();
      auto production = item->get_production();

      if (dot_pos < production->get_rhs().size()) {
        auto next_char = production->get_rhs()[dot_pos];
        for (auto rule : rules) {
          if (rule->get_lhs()[0] == next_char) {
            auto new_item = std::make_shared<Item>(rule, 0);

            if (std::find_if(item_set.begin(), item_set.end(),
                             [&](const std::shared_ptr<Item> &item) { return *item == *new_item; })
                == item_set.end()) {
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
  auto initial_item = std::make_shared<Item>(rules[rules.size() - 1], 0);
  ItemSet initial_state;
  initial_state.push_back(initial_item);
  get_closure(initial_state);
  states.push_back(std::move(initial_state));
}