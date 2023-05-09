#include "Production.h"

Production::Production(std::string lhs, std::string rhs) {
  this->lhs = lhs;
  this->rhs = rhs;
}

std::string Production::get_lhs() const {
  return this->lhs;
}

std::string Production::get_rhs() const {
  return this->rhs;
}

std::string Production::to_string() const {
  return this->lhs + " -> " + this->rhs;
}
