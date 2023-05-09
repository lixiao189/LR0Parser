#ifndef __PRODUCTION_H__
#define __PRODUCTION_H__

#include <string>

class Production {
private:
  std::string lhs;
  std::string rhs;

public:
  Production(std::string, std::string);
  std::string get_lhs() const;
  std::string get_rhs() const;
  std::string to_string() const;
};

#endif // __PRODUCTION_H__