#ifndef IRQHANDLERSET_H
#define IRQHANDLERSET_H

#include <functional>
#include <string>

class IRqHandlerSet
{
public:
    using Handler = std::function<std::string(std::string)>;

    virtual void add_handler(std::string rq_name, Handler h) = 0;
    Handler get_handler(std::string rq_name) = 0;
    virtual ~IRqHandlerSet();
};

#endif // IRQHANDLERSET_H
