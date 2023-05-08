#ifndef __ITEM_H__
#define __ITEM_H__

#include "Production.h"
#include <memory>
#include <string>

using ProductionPtr = std::shared_ptr<Production>;

class Item {
private:
  int dot_pos;
  ProductionPtr production; // 对应的产生式
public:
  Item(ProductionPtr production, int dot_pos);
  int get_dot_pos() const;
  ProductionPtr get_production() const;
  std::string to_string() const;
};

#endif // __ITEM_H__