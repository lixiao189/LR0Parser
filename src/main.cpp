#include "LRParser.h"
#include "data.h"
#include <iostream>
#include <memory>
#include <string>

using LRParserPtr = std::unique_ptr<LRParser>;

int main() {
  LRParserPtr parser = std::make_unique<LRParser>(
      LR0_STR); // 构建 LR 解析器 (包括 action 表和 goto 表)

  parser->output_automaton();
  parser->output_action_goto_table();

  return 0;
}
