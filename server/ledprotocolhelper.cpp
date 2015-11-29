#include "ledprotocolhelper.h"
#include <algorithm>

const std::vector<LedProtocolHelper::Color_Name_Pair> LedProtocolHelper::m_color_names =
{
    {IRgbLed::Color::RED, "red"},
    {IRgbLed::Color::GREEN, "green"},
    {IRgbLed::Color::BLUE, "blue"},
};

const std::vector<LedProtocolHelper::State_Name_Pair>  LedProtocolHelper::m_state_names =
{
    {true, "on"},
    {false, "off"},
};

LedProtocolHelper::LedProtocolHelper(LedPtr led_ptr)
    : m_led(led_ptr)
{
}

std::string LedProtocolHelper::get_color(const std::string& params)
{
    if (!params.empty())
        throw std::invalid_argument("LedProtocolHelper::get_color(): trailing characters are not allowed for this request");
    return get_color_name(m_led->get_color());
}

std::string LedProtocolHelper::get_rate(const std::string& params)
{
    if (!params.empty())
        throw std::invalid_argument("LedProtocolHelper::get_rate(): trailing characters are not allowed for this request");
    return get_rate_string(m_led->get_rate());
}

std::string LedProtocolHelper::get_state(const std::string& params)
{
    if (!params.empty())
        throw std::invalid_argument("LedProtocolHelper::get_state(): trailing characters are not allowed for this request");
    return get_state_name(m_led->get_state());
}

std::string LedProtocolHelper::set_color(const std::string& params)
{
    if (params.empty())
        throw std::invalid_argument("LedProtocolHelper::set_color(): parameter missing");
    m_led->set_color(get_color_value(strip_single_parameter(params)));

    return "";
}

std::string LedProtocolHelper::set_rate(const std::string& params)
{
    if (params.empty())
        throw std::invalid_argument("LedProtocolHelper::set_rate(): parameter missing");
    m_led->set_rate(get_rate_value(strip_single_parameter(params)));

    return "";
}

std::string LedProtocolHelper::set_state(const std::string& params)
{
    if (params.empty())
        throw std::invalid_argument("LedProtocolHelper::set_state(): parameter missing");
    m_led->set_state(get_state_value(strip_single_parameter(params)));

    return "";
}

IRgbLed::Color LedProtocolHelper::get_color_value(const std::string& color_name)
{
    for (auto& x : m_color_names)
    {
        if (x.second == color_name)
            return x.first;
    }
    throw std::invalid_argument("LedProtocolHelper::get_color_value(): invalid value");
}

std::string LedProtocolHelper::get_color_name(IRgbLed::Color color)
{
    for (auto& x : m_color_names)
    {
        if (x.first == color)
            return x.second;
    }
    throw std::invalid_argument("LedProtocolHelper::get_color_name(): invalid value");
}

IRgbLed::LedState LedProtocolHelper::get_state_value(const std::string& state_name)
{
    for (auto& x : m_state_names)
    {
        if (x.second == state_name)
            return x.first;
    }
    throw std::invalid_argument("LedProtocolHelper::get_state_value(): invalid value");
}

std::string LedProtocolHelper::get_state_name(IRgbLed::LedState led_state)
{
    for (auto& x : m_state_names)
    {
        if (x.first == led_state)
            return x.second;
    }
    throw std::invalid_argument("LedProtocolHelper::get_state_name(): invalid value");
}

IRgbLed::Rate LedProtocolHelper::get_rate_value(const std::string& rate_string)
{
    size_t sz = 0;
    int retval = 0;

    try
    {
        retval = std::stoi(rate_string, &sz);
    }
    catch (std::invalid_argument& e)
    {
        throw std::invalid_argument("LedProtocolHelper::get_rate_value(): integer parameter not found");
    }
    catch (std::out_of_range& e)
    {
        throw std::invalid_argument("LedProtocolHelper::get_rate_value(): integer parameter is too large");
    }

    if (sz < rate_string.size())
        throw std::invalid_argument("Unexpected trailing characters after integer parameter:\"" + rate_string.substr(sz) + "\"");

    return retval;
}

std::string LedProtocolHelper::get_rate_string(IRgbLed::Rate rate_value)
{
    return std::to_string(rate_value);
}

// Skip leading whitespace in parameter list and check that there is only 1 parameter in the list.
std::string LedProtocolHelper::strip_single_parameter(const std::string &params)
{
    auto params_begin = std::find_if(params.cbegin(), params.cend(), [](char c){return !std::isspace(c);});

    auto params_end = std::find_if(params_begin, params.cend(), [](char c){return std::isspace(c);});

    if (params_end != params.cend())
        throw std::invalid_argument("LedProtocolHelper::strip_single_parameter(): parameter contains trailing characters: \"" + std::string(params_end, params.cend()) + "\"");

    return std::string(params_begin, params_end);
}
