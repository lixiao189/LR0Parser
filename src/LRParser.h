#ifndef __LRPARSER_H__
#define __LRPARSER_H__

#include "Automaton.h"
#include <iostream>
#include <memory>
#include <set>
#include <vector>

using AutomatonPtr = std::unique_ptr<Automaton>;

class LRParser {
private:
  AutomatonPtr automaton; // LR0 automaon

  std::map<int, std::map<char, std::string>> action_table; // action 表
  std::map<int, std::map<char, std::string>> goto_table;   // goto 表
public:
  static std::string SYNTHETIC_START; // 增广文法的开始符号

  void build_action_table();
  void build_goto_table();

  void output_action_goto_table();

  LRParser(std::string LR0_STR);
  ~LRParser();
};

#endif // __LRPARSER_H__