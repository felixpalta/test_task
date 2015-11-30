#ifndef SINGLEFIFOPRODUCER_H
#define SINGLEFIFOPRODUCER_H

#include "iclientproducer.h"
#include <istream>
#include <ostream>

class SingleFifoProducer : public IClientProducer
{
public:
    SingleFifoProducer(std::istream& id_stream, std::ostream& log);
    virtual ClientPtr wait_for_new_client() override;
private:
    std::istream& m_id_stream;
    std::ostream& m_log_stream;
};

#endif // SINGLEFIFOPRODUCER_H
