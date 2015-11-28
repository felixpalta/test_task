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
