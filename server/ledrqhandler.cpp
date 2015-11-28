#include "ledrqhandler.h"

LedRqHandler::LedRqHandler(std::shared_ptr<IRgbLed> led)
    : m_rgb_led(led)
{
}

std::string LedRqHandler::process_request(RqType rq_type, const std::string& params)
{
    switch (rq_type)
    {
    case RqType::LED_GET_COLOR:
        break;
    case RqType::LED_SET_COLOR:
        break;
    default:
        break;

    }
    return "nope";
}
