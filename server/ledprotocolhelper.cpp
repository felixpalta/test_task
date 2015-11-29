#include "ledprotocolhelper.h"

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
        throw std::invalid_argument("LedProtocolHelper::get_color(): parameters are not allowed");
    return get_color_name(m_led->get_color());
}

std::string LedProtocolHelper::get_rate(const std::string& params)
{
    if (!params.empty())
        throw std::invalid_argument("LedProtocolHelper::get_rate(): parameters are not allowed");
    return get_rate_string(m_led->get_rate());
}

std::string LedProtocolHelper::get_state(const std::string& params)
{
    if (!params.empty())
        throw std::invalid_argument("LedProtocolHelper::get_state(): parameters are not allowed");
    return get_state_name(m_led->get_state());
}

std::string LedProtocolHelper::set_color(const std::string& params)
{
    if (params.empty())
        throw std::invalid_argument("LedProtocolHelper::set_color(): parameter missing");
    m_led->set_color(get_color_value(params));

    return "";
}

std::string LedProtocolHelper::set_rate(const std::string& params)
{
    if (params.empty())
        throw std::invalid_argument("LedProtocolHelper::set_rate(): parameter missing");
    m_led->set_rate(get_rate_value(params));

    return "";
}

std::string LedProtocolHelper::set_state(const std::string& params)
{
    if (params.empty())
        throw std::invalid_argument("LedProtocolHelper::set_state(): parameter missing");
    m_led->set_state(get_state_value(params));

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
    {
        for (auto& x : m_state_names)
        {
            if (x.first == led_state)
                return x.second;
        }
        throw std::invalid_argument("LedProtocolHelper::get_state_name(): invalid value");
    }
}

IRgbLed::Rate LedProtocolHelper::get_rate_value(const std::string& rate_string)
try
{
    return std::stoi(rate_string);
}
catch (std::exception& e)
{
    throw std::runtime_error(std::string("LedProtocolHelper::get_rate_value(): ") + e.what());
}

std::string LedProtocolHelper::get_rate_string(IRgbLed::Rate rate_value)
{
    return std::to_string(rate_value);
}
