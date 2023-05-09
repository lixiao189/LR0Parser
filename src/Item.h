#ifndef __ITEM_H__
#define __ITEM_H__

#include "Production.h"
#include <memory>
#include <string>

class Item {
private:
  int dot_pos;              // dot pos 代表点的位置 dot_pos = 0 的时候点在第 0 个字符的前面
  Production production; // 对应的产生式

public:
  Item(Production production, int dot_pos);
  int get_dot_pos() const;
  Production get_production() const;
  std::string to_string() const;

  bool operator==(const Item &item) const {
    return this->dot_pos == item.dot_pos && this->production == item.production;
  }  
};

using ItemPtr = std::shared_ptr<Item>;

#endif // __ITEM_H__