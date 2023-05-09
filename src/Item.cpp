#include "Item.h"

Item::Item(ProductionPtr production, int dot_pos) {
  this->production = production;
  this->dot_pos = dot_pos;
}

int Item::get_dot_pos() const { return this->dot_pos; }

ProductionPtr Item::get_production() const { return this->production; }

std::string Item::to_string() const {
  return this->production->get_lhs() + " -> " + this->production->get_rhs() +
        ", " + std::to_string(this->dot_pos);
}