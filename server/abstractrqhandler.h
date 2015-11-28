#ifndef ABSTRACTRQHANDLER_H_
#define ABSTRACTRQHANDLER_H_


#include "irqhandler.h"
#include "irqhandler.h"
#include <string>
#include <map>

class AbstractRqHandler : public IRqHandler
{
public:

    std::string process_request(const std::string& input) override final;

    class ParamParsingException : public std::runtime_error
    {
    public:
        ParamParsingException(const std::string &s)
            : runtime_error("AbstractRqHandler::ParamParsingException: " + s)
        {
        }
    };

protected:

    enum class RqType
    {
        INVALID_RQ_TYPE,
        LED_GET_COLOR,
        LED_SET_COLOR,
        LED_GET_RATE,
        LED_SET_RATE,
        LED_GET_STATUS,
        LED_SET_STATUS,
    };

private:
    virtual std::string process_rq(RqType rq_type, const std::string& params) = 0;

    static RqType extract_rq_type_and_params(const std::string& full_input, std::string& params);
    static RqType get_rq_type(const std::string& request_name);
    static const std::map<const std::string, RqType> name_to_rq_map;

};

#endif // ABSTRACTRQHANDLER_H_
