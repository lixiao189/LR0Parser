#ifndef __PRODUCTION_H__
#define __PRODUCTION_H__

#include <string>

class Production {
private:
  std::string lhs;
  std::string rhs;

public:
  Production();
  Production(std::string, std::string);
  Production(const Production&);

  std::string get_lhs() const;
  std::string get_rhs() const;
  std::string to_string() const;

  bool operator==(const Production &production) const {
    return this->lhs == production.lhs && this->rhs == production.rhs;
  }
};

#endif // __PRODUCTION_H__