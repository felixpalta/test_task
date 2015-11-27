#include "rgbled.h"
#include <iostream>
#include <stdexcept>

using namespace std;

RgbLed::RgbLed(ostream &out,
               LedState start_state,
               Color start_color,
               Rate start_rate)
    : m_out(out),
      m_state(start_state),
      m_color(is_valid_color(int(start_color)) ? Color(start_color) : DEFAULT_COLOR),
      m_rate(is_valid_rate(start_rate) ? start_rate : DEFAULT_RATE)
{
}

bool RgbLed::set_state(LedState state)
{
    m_state = state;

    m_out << "State set: " << boolalpha << state << '\n';

    return true;
}

bool RgbLed::set_color(Color color)
{

    if (!is_valid_color(int(color)))
        return false;

    m_color = color;
    m_out << "Color set: " << get_color_name(color) << '\n';
    return true;
}

bool RgbLed::set_rate(int rate)
{
    if (!is_valid_rate(rate))
        return false;

    m_rate = rate;
    m_out << "Rate set: " << rate << '\n';
    return true;
}

boost::optional<RgbLed::LedState> RgbLed::get_state() const
{
    return m_state;
}

boost::optional<RgbLed::Color> RgbLed::get_color() const
{
    return m_color;
}

boost::optional<RgbLed::Rate> RgbLed::get_rate() const
{
    return m_rate;
}

bool RgbLed::is_valid_rate(int r)
{
    return r >= 0 && r <= 5;
}

bool RgbLed::is_valid_color(int color)
{
    switch (color)
    {
    case int(Color::RED):
    case int(Color::BLUE):
    case int(Color::GREEN):
        return true;
    default:
        return false;
    }
}

std::string RgbLed::get_color_name(RgbLed::Color color)
{
    switch (color)
    {
    case Color::RED:
        return "Red";
    case Color::BLUE:
        return "Blue";
    case Color::GREEN:
        return "Green";
    default:
        return "Invalid Color";
    }
}
