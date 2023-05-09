#include "Automaton.h"

Automaton::Automaton() {}

Automaton::~Automaton() {}

void Automaton::add_production(Production production) {
  this->rules.push_back(production);
}

std::vector<Production> Automaton::get_rules() const {
  return this->rules;
}
