#include "rqhandlerset.h"

void RqHandlerSet::add_handler(const std::string &rq_name, Handler h)
{
    m_rq_handlers[rq_name] = h;
}

IRqHandlerSet::Handler RqHandlerSet::get_handler(const std::string &rq_name)
{
    auto iter = m_rq_handlers.find(rq_name);
    if (iter != m_rq_handlers.end())
    {
        return iter->second;
    }
    throw InternalError("get_handler(): not found: " + rq_name);
}
