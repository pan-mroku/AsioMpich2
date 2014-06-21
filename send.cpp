#include "AsioCommunication.h"
#include "payload.hpp"
#include <iostream>

int main()
{
  try 
  {
    Payload p;
    AsioCommunication comm;
    comm.connectAsClient();
    comm.sendObject(p);
    std::cout<<p<<std::endl;
    p=comm.readObject<Payload>();
    std::cout<<p<<std::endl;
  }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }

  return 0;
}
