#include "LRParser.h"
#include "Automaton.h"
#include "Production.h"
#include <fstream>
#include <memory>
#include <string>

char LRParser::SYNTHETIC_START = 'G';
char LRParser::SYNTHETIC_END= '#';

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
      std::make_shared<Production>(automaton->get_rules().size(), std::string(1, SYNTHETIC_START),
                                   automaton->get_rules()[0]->get_lhs())); // 构建增广文法

  automaton->build_automaton(); // 构建 LR0 自动机

  build_action_table(); // 构建 action 表
  build_goto_table();   // 构建 goto 表
}

LRParser::~LRParser() {}

/**
 * @brief 构建 action 表
 *
 */
void LRParser::build_action_table() {
  for (int i = 0; i < automaton->get_states().size(); i++) {
    if (automaton->get_states()[i].size() == 1) { // accept 或者 reduce
      if (automaton->get_states()[i][0]->get_production()->get_lhs() == std::string(1, SYNTHETIC_START)) {
        action_table[i][SYNTHETIC_END] = "accept";
      } else {
        for (auto symbol : automaton->get_terminals()) {
          if (automaton->get_states()[i][0]->get_dot_pos()
              == automaton->get_states()[i][0]->get_production()->get_rhs().size()) {
            action_table[i][symbol]
                = "r" + std::to_string(automaton->get_states()[i][0]->get_production()->get_id());
          }
        }
      }
    } else { // shift
      for (auto symbol : automaton->get_terminals()) {
        if (automaton->get_transitions()[i].find(symbol) != automaton->get_transitions()[i].end()) {
          auto target = automaton->get_transitions()[i][symbol];
          action_table[i][symbol] = "s" + std::to_string(target);
        }
      }
    }
  }
}

/**
 * @brief 构建 goto 表
 *
 */
void LRParser::build_goto_table() {
  for (int i = 0; i < automaton->get_states().size(); i++) {
    for (auto symbol : automaton->get_noneterminals()) {
      if (automaton->get_transitions()[i].find(symbol) != automaton->get_transitions()[i].end()) {
        auto target = automaton->get_transitions()[i][symbol];
        goto_table[i][symbol] = std::to_string(target);
      }
    }
  }
}

/**
 * @brief 输出自动机
 *
 */
void LRParser::output_automaton() {
  std::ofstream outfile("output.txt", std::ios::app);
  // 输出文法
  outfile << "Grammar: " << std::endl;
  for (auto i = 0; i < automaton->get_rules().size(); i++) {
    outfile << i << ": " << automaton->get_rules()[i]->to_string() << std::endl;
  }
  outfile << std::endl;

  // 输出状态集合
  outfile << "States: " << std::endl;
  for (auto i = 0; i < automaton->get_states().size(); i++) {
    outfile << "I" << i << ": ";
    for (auto item : automaton->get_states()[i]) {
      outfile << item->to_string() << " ";
    }
    outfile << std::endl;
  }

  outfile << std::endl;

  // 输出转移函数
  outfile << "Transitions: " << std::endl;
  for (auto i = 0; i < automaton->get_states().size(); i++) {
    for (auto symbol : automaton->get_symbols()) {
      if (automaton->get_transitions()[i].find(symbol) != automaton->get_transitions()[i].end()) {
        outfile << "I" << i << " --" << symbol << "--> I"
                  << automaton->get_transitions()[i][symbol] << std::endl;
      }
    }
  }

  outfile << std::endl;

  outfile.close();
}

/**
 * @brief 输出 action 和 goto 表
 *
 */
void LRParser::output_action_goto_table() {
  std::ofstream outfile("output.txt", std::ios::app);

  // Output the table header
  for (auto symbol : automaton->get_terminals()) {
    outfile << "\t" << symbol;
  }
  outfile << "\t" << SYNTHETIC_END;
  for (auto symbol : automaton->get_noneterminals()) {
    outfile << "\t" << symbol;
  }

  for (int i = 0; i < automaton->get_states().size(); i++) {
    outfile << std::endl << i;
    for (auto symbol : automaton->get_terminals()) {
      if (action_table[i].find(symbol) != action_table[i].end()) {
        outfile << "\t" << action_table[i][symbol];
      } else {
        outfile << "\t";
      }
    }

    // symbol == '#'
    if (action_table[i].find('#') != action_table[i].end()) {
      outfile << "\t" << action_table[i]['#'];
    } else {
      outfile << "\t";
    }

    for (auto symbol : automaton->get_noneterminals()) {
      if (goto_table[i].find(symbol) != goto_table[i].end()) {
        outfile << "\t" << goto_table[i][symbol];
      } else {
        outfile << "\t";
      }
    }
  }

  outfile.close();
}
