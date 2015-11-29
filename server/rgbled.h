#ifndef RGBLED_H
#define RGBLED_H

#include "irgbled.h"
#include <string>
#include <ostream>

class RgbLed : public IRgbLed
{
public:
    RgbLed(std::ostream &out,
           LedState start_state = false,
           Color start_color = DEFAULT_COLOR,
           Rate start_rate = DEFAULT_RATE);

    ~RgbLed() override = default;

    void set_state(LedState state) override;
    void set_color(Color color) override;
    void set_rate(Rate rate) override;

    LedState get_state() const override;
    Color get_color() const override;
    Rate get_rate() const override;

private:
    std::ostream &m_out;
    LedState m_state;
    Color m_color;
    Rate m_rate;

    static bool is_valid_rate(int r);
    static bool is_valid_color(int color);
    static std::string get_color_name(Color color);

    static const Rate DEFAULT_RATE = 0;
    static const Color DEFAULT_COLOR = Color::RED;

    RgbLed(const RgbLed&) = delete;
    RgbLed& operator=(const RgbLed&) = delete;
};

#endif // RGBLED_H
