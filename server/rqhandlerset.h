#ifndef RQHANDLERSET_H
#define RQHANDLERSET_H

#include "irqhandlerset.h"
#include <map>

class RqHandlerSet : public IRqHandlerSet
{
public:
    RqHandlerSet();

    void add_handler(const std::string &rq_name, Handler h) override;
    Handler get_handler(const std::string &rq_name) const override;

private:
    std::map<const std::string, Handler> m_rq_handlers;
};

#endif // RQHANDLERSET_H
