#include "abstractrqhandler.h"

const std::map<const std::string, AbstractRqHandler::RqType> AbstractRqHandler::name_to_rq_map =
{
    {"get-led-color", RqType::LED_GET_COLOR},
    {"set-led-color", RqType::LED_SET_COLOR},
    {"get-led-rate", RqType::LED_GET_RATE},
    {"set-led-rate", RqType::LED_SET_RATE},
    {"get-led-state", RqType::LED_GET_STATUS},
    {"set-led-state", RqType::LED_SET_STATUS},
};

AbstractRqHandler::RqType AbstractRqHandler::get_rq_type(const std::string& request_name)
{
    auto iter = name_to_rq_map.find(request_name);
    if (iter != name_to_rq_map.end())
    {
        return iter->second;
    }
    return RqType::INVALID_RQ_TYPE;
}

AbstractRqHandler::RqType AbstractRqHandler::extract_rq_type_and_params(const std::string& full_input, std::string& params)
{
    if (full_input.length() == 0)
        throw ParamParsingException("extract_rq_type_and_params(): input string is empty");

    auto pos = full_input.find(' ');

    // Parameter name is either full string or first substring, depending on pos.
    RqType rq_type = get_rq_type(full_input.substr(0, pos));

    if (pos == full_input.npos)
        params = "";
    else
        params = full_input.substr(pos + 1);

    return rq_type;
}
