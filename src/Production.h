#ifndef __PRODUCTION_H__
#define __PRODUCTION_H__

#include <string>

class Production {
private:
  std::string left;
  std::string right;
public:
  Production(std::string left, std::string right);
  std::string get_left() const;
  std::string get_right() const;
  std::string to_string() const;
};

#endif // __PRODUCTION_H__