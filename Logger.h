#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <typeinfo>
#include <boost/format.hpp>
using namespace std;
template<typename T>
class Logger
{
public:
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }
    static Logger getInstance(T * source){
         Logger logger(source);
         return logger;
    }
    void log(string message)
    {
        if(source==nullptr)
            (*stream)<<message<<endl;
        else
            (*stream)<<boost::format("Source<%s> %s \n") % typeid(*source).name() % message;
    }
    virtual ~Logger(){}
protected:
    Logger()
    {
        stream=&cout;
    }
    Logger(T * source)
    {
        stream=&cout;
        this->source=source;
    }
    ostream * stream;
    T * source = nullptr;
private:

};

#endif // LOGGER_H
