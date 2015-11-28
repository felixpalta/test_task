#include "ledrqhandler.h"

LedRqHandler::LedRqHandler(std::shared_ptr<IRgbLed> led)
    : m_rgb_led(led)
{
    if (!m_rgb_led)
        throw std::invalid_argument("LedRgbHandler(): led ptr is null");
}

std::string LedRqHandler::process_request(RqType rq_type, const std::string& params)
{
    std::string retval;

    bool result;
    IRgbLed::Color color;
    IRgbLed::Rate rate;
    IRgbLed::LedState state;

    try
    {
        switch (rq_type)
        {
            case RqType::LED_GET_COLOR:
                color = m_rgb_led->get_color();
                retval = get_ok_with_result(get_color_name(color));
                break;

            case RqType::LED_GET_RATE:
                rate = m_rgb_led->get_rate();
                retval = get_ok_with_result(std::to_string(rate));
                break;

            case RqType::LED_GET_STATUS:
                state = m_rgb_led->get_state();
                retval = get_ok_with_result(get_state_name(state));
                break;

            case RqType::LED_SET_COLOR:
                result = m_rgb_led->set_color(get_color_value(params));
                retval = result ? get_ok_string() : get_failed_string();
                break;

            case RqType::LED_SET_RATE:
                result = m_rgb_led->set_rate(get_rate_value(params));
                retval = result ? get_ok_string() : get_failed_string();
                break;

        case RqType::LED_SET_STATUS:
                result = m_rgb_led->set_state(get_state_value(params));
                retval = result ? get_ok_string() : get_failed_string();
                break;

            default:
                retval = get_failed_string();
                break;
        }
    }
    catch (IRgbLed::InternalException&)
    {
        // TODO: Add internal exception logging.
        retval = get_failed_string();
    }
    catch (ParamParsingException&)
    {
        // TODO: Add parameters parsing exception logging.
        retval = get_failed_string();
    }

    return retval;
}

std::string LedRqHandler::get_failed_string()
{
    return "FAILED";
}

std::string LedRqHandler::get_ok_string()
{
    return "OK";
}

std::string LedRqHandler::get_ok_with_result(const std::string& result)
{
    return std::string("OK " + result);
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

std::string LedRqHandler::get_state_name(IRgbLed::LedState state)
{
    return state ? "on" : "off";
}

IRgbLed::LedState LedRqHandler::get_state_value(const std::string &s)
{
    if (s == "on")
        return true;
    if (s == "off")
        return false;
    throw ParamParsingException("Invalid LED state parameter");
}

 IRgbLed::Rate LedRqHandler::get_rate_value(const std::string& s)
{
    size_t sz = 0;
    IRgbLed::Rate retval = std::stoi(s, &sz);
    if (sz == 0)
        throw ParamParsingException("Expected integer parameter");
    if (sz < s.size())
        throw ParamParsingException("Unexpected trailing characters after integer parameter");
    return retval;
}
