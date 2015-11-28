#include "ledrqhandler.h"

LedRqHandler::LedRqHandler(std::shared_ptr<IRgbLed> led, std::ostream &err_stream)
    : m_rgb_led(led),
      m_err(err_stream)
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
                if (params.length() != 0)
                    throw ParamParsingException("LedRqHandler::process_request(): trailing characters for this request are not allowed");

                color = m_rgb_led->get_color();
                retval = get_ok_with_result(get_color_name(color));
                break;

            case RqType::LED_GET_RATE:
                if (params.length() != 0)
                    throw ParamParsingException("LedRqHandler::process_request(): trailing characters for this request are not allowed");

                rate = m_rgb_led->get_rate();
                retval = get_ok_with_result(std::to_string(rate));
                break;

            case RqType::LED_GET_STATUS:
                if (params.length() != 0)
                    throw ParamParsingException("LedRqHandler::process_request(): trailing characters for this request are not allowed");

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
    catch (std::exception &e)
    {
        // TODO: Add internal exception logging.
        retval = get_failed_string();

        m_err << "LedRqHandler::process_request(): " << e.what() << '\n';
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
    try
    {
        IRgbLed::Rate retval = std::stoi(s, &sz);
        if (sz < s.size())
            throw ParamParsingException("Unexpected trailing characters after integer parameter:\"" + s.substr(sz) + "\"");

        return retval;
    }
    catch (std::invalid_argument& e)
    {
        throw ParamParsingException("LedRqHandler::get_rate_value(): Expected integer parameter");
    }
    catch (std::out_of_range& e)
    {
        throw ParamParsingException("LedRqHandler::get_rate_value(): integer parameter is too large");
    }
}
