#include "payload.hpp"
#include <boost/range/irange.hpp>
#include <iostream>

Payload::Payload()
{
  Table.resize(9);
  X=Y=3;
  for (int x :boost::irange(0,X))
    for(int y :boost::irange(0,Y))
      Table[x*Y+y]=x*Y+y;
}

std::ostream& operator<<(std::ostream& out, const Payload& p)
{
  out<<"x: "<<p.X<<" y: "<<p.Y<<std::endl;
  for (int v :p.Table)
    out<<v<<" ";
  return out;
}
