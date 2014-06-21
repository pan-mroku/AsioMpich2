#ifndef _PAYLOAD_HPP_
#define _PAYLOAD_HPP_

#include <boost/serialization/vector.hpp>

#include <vector>
#include <ostream>

class Payload
{
public:
  std::vector<int> Table;
  int X,Y;
  Payload();

  friend std::ostream& operator<<(std::ostream& out, const Payload& p);

private:

  friend class boost::serialization::access;

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & X;
    ar & Y;
    ar & Table;
  }

};

#endif
