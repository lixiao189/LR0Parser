#ifndef __PRODUCTION_H__
#define __PRODUCTION_H__

#include <memory>
#include <string>

class Production {
private:
  int id;
  std::string lhs;
  std::string rhs;

public:
  Production();
  Production(int id, std::string, std::string);
  Production(const Production &);

  int get_id() const;
  std::string get_lhs() const;
  std::string get_rhs() const;
  std::string to_string() const;

  bool operator==(const Production &production) const {
    return this->lhs == production.lhs && this->rhs == production.rhs;
  }
};

using ProductionPtr = std::shared_ptr<Production>;

#endif // __PRODUCTION_H__