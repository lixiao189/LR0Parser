#include "LRParser.h"
#include "Production.h"
#include <memory>

std::string LRParser::SYNTHETIC_START = "G";

LRParser::LRParser(std::string LR0_STR) {
  // 创建自动机对象
  automaton = std::make_unique<Automaton>();

  // 解析 LR0_STR 中的每行产生式
  auto pos = 0;
  auto prev = 0;
  while ((pos = LR0_STR.find('\n', prev)) != std::string::npos) {
    auto line = LR0_STR.substr(prev, pos - prev);
    if (line.size()) {
      auto arrow_pos = line.find("->");
      auto lhs = line.substr(0, arrow_pos);
      auto rhs = line.substr(arrow_pos + 2);

      automaton->add_production(
          std::make_shared<Production>(automaton->get_rules().size(), lhs, rhs));

      // 添加符号
      automaton->add_symbol(lhs[0]);
      automaton->add_noneterminals(lhs[0]);
      for (auto c : rhs) {
        automaton->add_symbol(c);
        if (c >= 'A' && c <= 'Z') {
          automaton->add_noneterminals(c);
        } else {
          automaton->add_terminals(c);
        }
      }
    }
    prev = pos + 1;
  }
  automaton->add_production(
      std::make_shared<Production>(automaton->get_rules().size(), SYNTHETIC_START,
                                   automaton->get_rules()[0]->get_lhs())); // 构建增广文法

  automaton->build_automaton(); // 构建 LR0 自动机

  // Output the data
  automaton->output_automaton(); // 输出 LR0 自动机

  build_action_table(); // 构建 action 表
  build_goto_table();   // 构建 goto 表
}

LRParser::~LRParser() {}

/**
 * @brief 构建 action 表
 * 
 */
void LRParser::build_action_table() {

}

/**
 * @brief 构建 goto 表
 * 
 */
void LRParser::build_goto_table() {}

/**
 * @brief 输出 action 和 goto 表
 * 
 */
void LRParser::output_action_goto_table() {}
