#ifndef IRQHANDLER_H
#define IRQHANDLER_H

#include <string>
#include <stdexcept>

class IRqHandler
{
public:

    class ParamParsingException : public std::runtime_error
    {
    public:
        ParamParsingException(const std::string &s)
            : runtime_error("IRqHandler::ParamParsingException: " + s)
        {
        }
    };

    virtual std::string process_request(const std::string& input) = 0;
    virtual ~IRqHandler() = default;
};

#endif // IRQHANDLER_H
