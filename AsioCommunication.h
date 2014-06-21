#ifndef ASIOCOMMUNICATION_H
#define ASIOCOMMUNICATION_H
#include <boost/archive/binary_iarchive.hpp>
#include <boost/asio.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/format.hpp>
#include "Logger.h"
using namespace std;
using namespace boost;

///strongly typed enum to save settings about header.
enum class messageType
{
    initialize=0
};
///Header struct
class Header
{
public:
    uint32_t length;
    //messageType type;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & length;
        //ar & type;
    }
};



class AsioCommunication
{
public:
    template <typename T>
    void sendObject(T object)
    {
        ///save object
        asio::streambuf outputBuffer;
        std::ostream objectStream(&outputBuffer);
        archive::binary_oarchive objectArchive(objectStream);
        objectArchive & object;

        ///prepare header
        Header header;
        header.length=outputBuffer.size();
        asio::streambuf headerBuffer;
        std::ostream header2Stream(&headerBuffer);
        archive::binary_oarchive headerArchive(header2Stream);
        headerArchive & header;

        std::vector<asio::const_buffer> buffers;
        buffers.push_back(headerBuffer.data());
        buffers.push_back(outputBuffer.data());

        //socket->connect(asio::ip::tcp::endpoint(asio::ip::tcp::v4(),6666));
        asio::write(*socket, buffers);
    }
    template <typename T>
    T readObject()
    {
        asio::streambuf bufx;
        Header m = decodeHeader(*socket);

        int amount=0;

        while(amount<m.length)
        {
            asio::streambuf::mutable_buffers_type bufs = bufx.prepare(m.length);
            size_t rcx = socket->receive(bufs);
            amount+=rcx;
            bufx.commit(rcx);
            logger.log((format("packet size - %d buffer - %d") %m.length%amount).str());
        }

        istream is(&bufx);
        archive::binary_iarchive ia(is);
        T obj;
        ia>> obj;

        return obj;
    }
    void connectAsServer(){
        acceptor = new asio::ip::tcp::acceptor(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 6666));
        socket = new asio::ip::tcp::socket(io_service);
        acceptor->accept(*socket);
    }
    void connectAsClient(){
    	socket = new asio::ip::tcp::socket(io_service);
    	socket->connect(asio::ip::tcp::endpoint(asio::ip::tcp::v4(),6666));
    }
    AsioCommunication()
    {
            ///Header size calculation, once per lifecycle
            Header header;
            std::ostringstream header2Stream;
            archive::binary_oarchive headerArchive(header2Stream);
            headerArchive & header;
            headerLength = header2Stream.tellp();
    }

    ~AsioCommunication()
    {
        delete socket;
        delete acceptor;
        socket=nullptr;
        acceptor=nullptr;
    }

protected:
private:
    Logger<AsioCommunication> logger = Logger<AsioCommunication>::getInstance(this);
    int headerLength;
    asio::io_service io_service;
    asio::ip::tcp::acceptor * acceptor = nullptr;
    asio::ip::tcp::socket * socket = nullptr;
    Header decodeHeader(asio::ip::tcp::socket & socket)
    {
        asio::streambuf bufx;
        asio::streambuf::mutable_buffers_type bufs = bufx.prepare(headerLength);
        size_t rcx = socket.receive(bufs);
        bufx.commit(rcx);
        istream is(&bufx);
        archive::binary_iarchive ia(is);
        Header m;
        ia>> m;
        return m;
    }
};

#endif // ASIOCOMMUNICATION_H
