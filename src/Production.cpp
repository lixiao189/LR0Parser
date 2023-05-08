#include "Production.h"

Production::Production(std::string left, std::string right) {
  this->left = left;
  this->right = right;
}

std::string Production::get_left() const {
  return this->left;
}

std::string Production::get_right() const {
  return this->right;
}

std::string Production::to_string() const {
  return this->left + " -> " + this->right;
}
