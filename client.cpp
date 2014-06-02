#include <iostream>
#include <asio.hpp>

int main()
{
  try
    {
      char* buf= new char[30];
      asio::io_service io_service;
      
      asio::ip::tcp::acceptor acceptor(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 6666));

    for (;;)
    {
      asio::ip::tcp::socket socket(io_service);
      acceptor.accept(socket);

      socket.receive(asio::buffer(buf, 30));
      socket.send(asio::buffer("ok",2));
      std::cout<<buf<<std::endl;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}
