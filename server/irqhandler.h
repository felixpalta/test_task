#ifndef IRQHANDLER_H
#define IRQHANDLER_H

#include <string>

class IRqHandler
{
public:

    virtual std::string process_request(const std::string& input) = 0;
    virtual ~IRqHandler() = default;
};

#endif // IRQHANDLER_H
