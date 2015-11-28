#include "ledrqhandler.h"

LedRqHandler::LedRqHandler(std::shared_ptr<IRgbLed> led)
    : m_rgb_led(led)
{
}

std::string LedRqHandler::process_request(RqType rq_type, const std::string& params)
{
    std::string retval;

    try
    {
        switch (rq_type)
        {
        case RqType::LED_GET_COLOR:
            {
                auto color = m_rgb_led->get_color();
                retval = get_ok_with_result(get_color_name(color));
            }
            break;
        case RqType::LED_GET_RATE:
            {
                auto rate = m_rgb_led->get_rate();
                retval = get_ok_with_result(std::to_string(rate));
            }
            break;
        case RqType::LED_GET_STATUS:
            {
                auto state = m_rgb_led->get_state();
                retval = get_ok_with_result(state ? "on" : "off");
            }
            break;
        default:
            break;
        }
    }
    catch (IRgbLed::IRgbLedInternalException&)
    {
        // TODO: Add internal exception logging.
        retval = get_failed_string();
    }

    return retval;
}


std::string LedRqHandler::get_failed_string()
{
    return "FAILED\n";
}

std::string LedRqHandler::get_ok_string()
{
    return "OK\n";
}

std::string LedRqHandler::get_ok_with_result(const std::string& result)
{
    return std::string("OK " + result + '\n');
}

std::string LedRqHandler::get_color_name(IRgbLed::Color color)
{
    switch (color)
    {
    case IRgbLed::Color::RED:
        return "red";
    case IRgbLed::Color::BLUE:
        return "blue";
    case IRgbLed::Color::GREEN:
        return "green";
    default:
        return "";
    }
}

IRgbLed::Color LedRqHandler::get_color_value(const std::string &s)
{
    if (s == "red")
        return IRgbLed::Color::RED;
    if (s == "green")
        return IRgbLed::Color::GREEN;
    if (s == "blue")
        return IRgbLed::Color::BLUE;

    return IRgbLed::Color::INVALID_COLOR;
}
