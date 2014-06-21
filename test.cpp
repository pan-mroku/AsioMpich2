#include "payload.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <iostream>
#include <fstream>

int main()
{
  Payload p;

  std::ofstream ofs("filename");
  {
    boost::archive::text_oarchive oa(ofs);
    oa << p;
  } 
  
  Payload d;
  {
    std::ifstream ifs("filename");
    boost::archive::text_iarchive ia(ifs);
    ia >> d;
  }

  std::cout<<p<<std::endl;
  std::cout<<d<<std::endl;
  return 0;
}
