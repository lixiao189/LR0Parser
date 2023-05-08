#include "LRParser.h"

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
      auto left = line.substr(0, arrow_pos);
      auto right = line.substr(arrow_pos + 2);

      automaton->add_production(Production(left, right));
    }
    prev = pos + 1;
  }
}

LRParser::~LRParser() {}