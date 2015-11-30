#include "singlefifoproducer.h"
#include "singlefifo.h"

SingleFifoProducer::SingleFifoProducer(IOPtr input)
    : m_io(input)
{
}

IClientProducer::IOPtr SingleFifoProducer::wait_for_new_client()
{
    std::string client_id = m_io->read_input_line_blocking();

    IOPtr result = std::make_shared<SingleFifo>(client_id);

    return result;
}
