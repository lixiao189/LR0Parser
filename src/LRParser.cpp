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

      automaton->add_production(std::make_shared<Production>(lhs, rhs));
    }
    prev = pos + 1;
  }
  automaton->add_production(std::make_shared<Production>(SYNTHETIC_START, automaton->get_rules()[0]->get_lhs())); // 构建增广文法

  automaton->build_automaon(); // 构建 LR0 自动机
}

LRParser::~LRParser() {}