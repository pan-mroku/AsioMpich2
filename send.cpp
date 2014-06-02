#include <iostream>
#include <asio.hpp>

//@TODO: wysyłać serializowalny przez boosta obiekt (np tablica o zmiennych wymiarach)

int main()
{
  try 
    {
      char* response=new char[5];
      asio::io_service io_service;
      
      asio::ip::tcp::socket socket(io_service);
      socket.connect(asio::ip::tcp::endpoint(asio::ip::tcp::v4(),6666));
      
      socket.send(asio::buffer("asd",3));
      socket.receive(asio::buffer(response,30));
      std::cout<<"response: "<<response<<std::endl;
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
    }

  return 0;
}
