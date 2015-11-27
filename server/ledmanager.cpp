#include "ledmanager.h"
#include <sstream>
#include <cstdlib>
using namespace std;

LedManager::LedManager(IRgbLed &led)
    : led_(led)
{
}

string LedManager::process_command(const string &command)
{
    istringstream iss(command);

    string directive, argument;
    bool argument_present = false;

    iss >> directive;
    if (!iss)
        return get_failed_string();
    if (iss >> argument)
        argument_present = true;

    if (!argument_present)
    {
        if (directive == "get-led-state")
        {
            boost::optional<IRgbLed::LedState> state_result = led_.get_state();
            if (state_result)
                return get_ok_with_result(*state_result ? "on" : "off");
        }
        else if (directive == "get-led-rate")
        {
            boost::optional<IRgbLed::Rate> rate_result= led_.get_rate();
            if (rate_result)
                return get_ok_with_result(to_string(*rate_result));
        }
        else if (directive == "get-led-color")
        {
            boost::optional<IRgbLed::Color> color_result = led_.get_color();
            if (color_result)
                return get_ok_with_result(get_color_name(*color_result));
        }
        else
            return get_failed_string();
    }

    if (directive == "set-led-state")
    {
        if (argument == "on" && led_.set_state(true))
            return get_ok_string();
        else if (argument == "off" && led_.set_state(false))
            return get_ok_string();

    }
    else if (directive == "set-led-rate")
    {
        int rate;
        istringstream is(argument);
        if ((is >> rate) && led_.set_rate(rate))
            return get_ok_string();
    }
    else if (directive == "set-led-color")
    {
        IRgbLed::Color color = get_color_value(argument);
        if (led_.set_color(IRgbLed::Color(color)))
            return get_ok_string();
    }

    return get_failed_string();
}

string LedManager::get_failed_string()
{
    return "FAILED\n";
}

string LedManager::get_ok_string()
{
    return "OK\n";
}

string LedManager::get_ok_with_result(const string& result)
{
    return string("OK " + result + '\n');
}

string LedManager::get_color_name(IRgbLed::Color color)
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

IRgbLed::Color LedManager::get_color_value(const std::string &s)
{
    if (s == "red")
        return IRgbLed::Color::RED;
    if (s == "green")
        return IRgbLed::Color::GREEN;
    if (s == "blue")
        return IRgbLed::Color::BLUE;

    return IRgbLed::Color::INVALID_COLOR;
}
