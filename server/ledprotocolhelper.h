#ifndef LEDPROTOCOLHELPER_H
#define LEDPROTOCOLHELPER_H

#include "irgbled.h"
#include <memory>
#include <string>
#include <vector>
#include <utility>

class LedProtocolHelper
{
public:
    using LedPtr = std::shared_ptr<IRgbLed>;

    LedProtocolHelper(LedPtr led_ptr);

    std::string get_color(const std::string& params);
    std::string get_rate(const std::string& params);
    std::string get_state(const std::string& params);
    std::string set_color(const std::string& params);
    std::string set_rate(const std::string& params);
    std::string set_state(const std::string& params);

private:
    LedPtr m_led;

    using Color_Name_Pair = std::pair<IRgbLed::Color, const std::string>;
    using State_Name_Pair = std::pair<IRgbLed::LedState, const std::string>;

    static const std::vector<Color_Name_Pair> m_color_names;
    static const std::vector<State_Name_Pair> m_state_names;

    static IRgbLed::Color get_color_value(const std::string& color_name);
    static std::string get_color_name(IRgbLed::Color color);

    static IRgbLed::LedState get_state_value(const std::string& state_name);
    static std::string get_state_name(IRgbLed::LedState led_state);

    static IRgbLed::Rate get_rate_value(const std::string& rate_string);
    static std::string get_rate_string(IRgbLed::Rate rate_value);

    static std::string strip_single_parameter(const std::string &params);
};

#endif // LEDPROTOCOLHELPER_H
