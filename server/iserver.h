#ifndef ISERVER_H
#define ISERVER_H

#include "irqhandler.h"
#include "iblockingiochannel.h"
#include <memory>
#include <stdexcept>

class IServer
{
public:

    class InternalError : public std::runtime_error
    {
    public:
        InternalError(const std::string& msg)
            : runtime_error("IServer::InternalError: " + msg)
        {
        }
    };

    using IOPtr = std::shared_ptr<IBlockingIOChannel>;
    using RqHandlerPtr = std::shared_ptr<IRqHandler>;

    virtual void add(IOPtr io_channel, RqHandlerPtr handler) = 0;
    virtual void run() = 0;

    virtual ~IServer() = default;

};

#endif // ISERVER_H
