#include "AsioCommunication.h"
#include "payload.hpp"

#include <boost/thread/thread.hpp>

#include <iostream>

void Process(Payload* p)
{
  std::cout<<"Start"<<std::endl;
  boost::this_thread::sleep_for( boost::chrono::seconds(2) );
  p->Work();
  std::cout<<"Stop"<<std::endl;
  delete p;
}

int main()
{
  try
    {
      for(;;)
        {
          AsioCommunication comm;
          comm.connectAsServer();
          Payload* p=new Payload(comm.readObject<Payload>());
          boost::thread worker(boost::bind(&Process, p));
          //you could just detach the thread and throw the boost::thread object away. Doing this is usually considered bad style, unless the monitoring responsibility has been transferred to another object first. 
          worker.detach(); 
          comm.sendObject(*p);
        }
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }
  
  return 0;
}
