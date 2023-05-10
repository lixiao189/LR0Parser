#include "Item.h"

Item::Item(ProductionPtr production, int dot_pos) {
  this->production = production;
  this->dot_pos = dot_pos;
}

int Item::get_dot_pos() const { return this->dot_pos; }

ProductionPtr Item::get_production() const { return this->production; }

std::string Item::to_string() const {
  std::string result = this->production->get_lhs() + " -> ";

  for (int i = 0; i < production->get_rhs().length(); i++) {
    if (i == dot_pos) {
      result += ".";
    }
    result += production->get_rhs()[i];
  }
  if (dot_pos == production->get_rhs().length()) {
    result += ".";
  }

  return std::move(result);
}