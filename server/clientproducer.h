#ifndef CLIENTPRODUCER_H
#define CLIENTPRODUCER_H

#include "iserver.h"
#include <string>
#include <stdexcept>
#include <thread>

class ClientProducer
{
public:
    ClientProducer(std::string service_pipe_name, std::shared_ptr<IRqProcessor> rq_processor);
private:
    std::string m_service_pipe_name;
    std::shared_ptr<IRqProcessor> m_rq_processor;
};

#endif // CLIENTPRODUCER_H
