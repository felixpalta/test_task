#ifndef ABSTRACTRQHANDLER_H_
#define ABSTRACTRQHANDLER_H_

#include <string>
#include <map>

class AbstractRqHandler
{
public:

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

    virtual std::string process_request(RqType rq_type, const std::string& params) = 0;

    virtual ~AbstractRqHandler() = default;

    static RqType get_rq_type(const std::string& request_name);

    class ParamParsingException : public std::runtime_error
    {
    public:
        ParamParsingException(const std::string &s)
            : runtime_error("AbstractRqHandler::ParamParsingException: " + s)
        {
        }
    };

private:

    static const std::map<const std::string, RqType> name_to_rq_map;

};

#endif // ABSTRACTRQHANDLER_H_
