#include "Production.h"

Production::Production() {
  this->lhs = "";
  this->rhs = "";
}

Production::Production(const Production &other) {
  this->lhs = other.lhs;
  this->rhs = other.rhs;
}

Production::Production(std::string lhs, std::string rhs) {
  this->lhs = lhs;
  this->rhs = rhs;
}

std::string Production::get_lhs() const { return this->lhs; }

std::string Production::get_rhs() const { return this->rhs; }

std::string Production::to_string() const { return this->lhs + " -> " + this->rhs; }
