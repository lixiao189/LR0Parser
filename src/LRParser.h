#ifndef __LRPARSER_H__
#define __LRPARSER_H__

#include "Automaton.h"
#include <iostream>
#include <memory>

using AutomatonPtr = std::unique_ptr<Automaton>;

class LRParser {
private:
  AutomatonPtr automaton; // LR0 automaon
public:
  static std::string SYNTHETIC_START; // 增广文法的开始符号

  LRParser(std::string LR0_STR);
  ~LRParser();
};

#endif // __LRPARSER_H__