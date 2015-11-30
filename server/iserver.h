#ifndef ISERVER_H
#define ISERVER_H

#include "iblockingiochannel.h"
#include <memory>
#include <string>
#include <stdexcept>

class IServer
{
public:
    class InternalError : public std::runtime_error
    {
    public:
        InternalError(const std::string& msg)
            : runtime_error("IServer::InternalError: " + msg){}
    };

    using IOPtr = std::shared_ptr<IBlockingIOChannel>;

    virtual void add(IOPtr io_channel) = 0;
    virtual void run() = 0;

    virtual ~IServer() = default;
};

#endif // ISERVER_H
