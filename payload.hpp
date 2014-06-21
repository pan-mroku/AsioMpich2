#ifndef _PAYLOAD_HPP_
#define _PAYLOAD_HPP_

#include <vector>
#include <ostream>

class Payload
{
public:
  std::vector<int> Table;
  int X,Y;
  Payload();

  friend std::ostream& operator<<(std::ostream& out, const Payload& p);
};

#endif
