#ifndef IRQHANDLERSET_H
#define IRQHANDLERSET_H

#include <functional>
#include <string>

class IRqHandlerSet
{
public:
    using Handler = std::function<std::string(const std::string&)>;

    class InternalError : public std::runtime_error
    {
    public:
        InternalError(const std::string& msg)
            : runtime_error("IrqHandlerSet::InternalError: " + msg) {}
    };

    virtual void add_handler(const std::string &rq_name, Handler h) = 0;
    virtual Handler get_handler(const std::string &rq_name) = 0;
    virtual ~IRqHandlerSet() = default;
};

#endif // IRQHANDLERSET_H
