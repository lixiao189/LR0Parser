#include "LRParser.h"
#include "data.h"
#include <iostream>
#include <memory>
#include <string>

using LRParserPtr = std::unique_ptr<LRParser>;

int main() {
  LRParserPtr parser = std::make_unique<LRParser>(LR0_STR);

  
  return 0;
}
