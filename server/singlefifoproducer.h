#ifndef SINGLEFIFOPRODUCER_H
#define SINGLEFIFOPRODUCER_H

#include "iclientproducer.h"
#include "iblockingiochannel.h"
#include <ostream>

class SingleFifoProducer : public IClientProducer
{
public:
    SingleFifoProducer(IOPtr input, std::ostream& log);
    virtual IOPtr wait_for_new_client() override;
private:
    IOPtr m_io;
    std::ostream& m_log_stream;
};

#endif // SINGLEFIFOPRODUCER_H
