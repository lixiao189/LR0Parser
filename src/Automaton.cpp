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

void Automaton::add_symbol(char symbol) { symbols.insert(symbol); }

std::vector<ProductionPtr> Automaton::get_rules() const { return this->rules; }

/**
 * @brief 判断是否是同一个状态
 *
 * @param s1
 * @param s2
 * @return true
 * @return false
 */
bool Automaton::is_same_state(State &s1, State &s2) {
  if (s1.size() != s2.size()) {
    return false;
  }

  for (auto item : s1) {
    if (std::find_if(s2.begin(), s2.end(),
                     [&](const std::shared_ptr<Item> &i) { return *item == *i; })
        == s2.end()) {
      return false;
    }
  }

  return true;
}

/**
 * @brief 求项目集闭包
 *
 * @param item_set 项目集
 */
void Automaton::get_closure(State &item_set) {
  if (item_set.empty()) {
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
 * @brief 构建 ItemSet 的 GOTO 函数
 *
 * @param state
 * @param symbol
 * @return ItemSet
 */
State Automaton::compute_goto(State &state, char symbol) {
  State new_state;
  for (auto item : state) {
    auto dot_pos = item->get_dot_pos();
    auto production = item->get_production();

    if (dot_pos < production->get_rhs().size() && production->get_rhs()[dot_pos] == symbol) {
      auto new_item = std::make_shared<Item>(production, dot_pos + 1);
      new_state.push_back(new_item);
    }
  }

  get_closure(new_state);
  return std::move(new_state); // TODO maybe has bug
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
  State initial_state;
  initial_state.push_back(initial_item);
  get_closure(initial_state);
  states.push_back(std::move(initial_state));

  auto transitions = std::map<int, std::map<int, int>>{}; // 状态转移函数

  // 构建状态转移函数
  for (auto i = 0; i < states.size(); i++) {
    for (auto symbol : symbols) {
      auto new_state = compute_goto(states[i], symbol);
      if (new_state.empty()) {
        continue;
      }

      auto j = 0;
      for (; j < states.size(); j++) {
        if (is_same_state(states[j], new_state)) {
          break;
        }
      }

      if (j == states.size()) {
        states.push_back(new_state);
      }

      transitions[i][symbol] = j;
    }
  }

  // 输出状态集合
  std::cout << "States: " << std::endl;
  for (auto i = 0; i < states.size(); i++) {
    std::cout << "I" << i << ": ";
    for (auto item : states[i]) {
      std::cout << item->to_string() << " ";
    }
    std::cout << std::endl;
  }

  // 输出转移函数
  std::cout << "Transitions: " << std::endl;
  for (auto i = 0; i < states.size(); i++) {
    for (auto symbol : symbols) {
      if (transitions[i].find(symbol) != transitions[i].end()) {
        std::cout << "I" << i << " --" << symbol << "--> I" << transitions[i][symbol] << std::endl;
      }
    }
  }
}