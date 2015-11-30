#include "singlefifoproducer.h"
#include "singlefifo.h"

SingleFifoProducer::SingleFifoProducer(std::istream& id_stream)
    : m_id_stream(id_stream)
{
}

IClientProducer::ClientPtr SingleFifoProducer::wait_for_new_client()
{
    std::string client_id;

    while(!std::getline(m_id_stream, client_id) || client_id.empty())
    {
        m_id_stream.clear();
    }

    ClientPtr result = std::make_shared<SingleFifo>(client_id);
    return result;
}
