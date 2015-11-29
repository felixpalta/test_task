#ifndef IRQPROCESSOR_H
#define IRQPROCESSOR_H

#include <string>
#include <stdexcept>
#include <functional>

class IRqProcessor
{
public:
    class ParamParsingException : public std::runtime_error
    {
    public:
        ParamParsingException(const std::string &msg)
            : runtime_error("IRqProcessor: " + msg) {}
    };

    class InternalError : public std::runtime_error
    {
    public:
        InternalError(const std::string& msg)
            : runtime_error("IRqProcessor: " + msg) {}
    };

    using Handler = std::function<std::string(const std::string&)>;

    virtual void add_handler(const std::string &rq_name, Handler h) = 0;

    virtual std::string process_request(const std::string& input) = 0;
    virtual ~IRqProcessor() = default;

private:
    virtual Handler get_handler(const std::string &rq_name) const = 0;
};

#endif // IRQPROCESSOR_H
