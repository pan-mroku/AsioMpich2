#include "AsioCommunication.h"
#include "payload.hpp"
#include <iostream>

int main()
{
  try
  {
    AsioCommunication comm;
    comm.connectAsServer();
    Payload p=comm.readObject<Payload>();
    std::cout<<p<<std::endl;
    p.Work();
    std::cout<<p<<std::endl;
    comm.sendObject(p);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}
