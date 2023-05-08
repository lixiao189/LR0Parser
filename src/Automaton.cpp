#include "Automaton.h"

Automaton::Automaton() {}

Automaton::~Automaton() {}

void Automaton::add_production(Production production) { this->productions.push_back(production); }

std::vector<Production> Automaton::get_productions() const { return this->productions; }
