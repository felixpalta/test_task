#ifndef SINGLEFIFOPRODUCER_H
#define SINGLEFIFOPRODUCER_H

#include "iclientproducer.h"
#include <istream>

class SingleFifoProducer : public IClientProducer
{
public:
    SingleFifoProducer(std::istream& id_stream);
    virtual ClientPtr wait_for_new_client() override;
private:
    std::istream& m_id_stream;
};

#endif // SINGLEFIFOPRODUCER_H
