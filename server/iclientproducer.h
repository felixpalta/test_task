#ifndef ICLIENTPRODUCER_H
#define ICLIENTPRODUCER_H

#include "iblockingiochannel.h"
#include <memory>
#include <string>
#include <stdexcept>

class IClientProducer
{
public:
    using IOPtr = std::shared_ptr<IBlockingIOChannel>;
    virtual IOPtr wait_for_new_client() = 0;
    virtual ~IClientProducer() = default;
};

#endif // ICLIENTPRODUCER_H
