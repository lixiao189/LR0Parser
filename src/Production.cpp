#include "Production.h"

Production::Production() {
  this->id = 0;
  this->lhs = "";
  this->rhs = "";
}

Production::Production(const Production &other) {
  this->id = other.id;
  this->lhs = other.lhs;
  this->rhs = other.rhs;
}

Production::Production(int id, std::string lhs, std::string rhs) {
  this->id = id;
  this->lhs = lhs;
  this->rhs = rhs;
}

int Production::get_id() const { return this->id; }

std::string Production::get_lhs() const { return this->lhs; }

std::string Production::get_rhs() const { return this->rhs; }

std::string Production::to_string() const {
  return this->lhs + " -> " + this->rhs;
}
