#ifndef IRGBLED_H
#define IRGBLED_H

#include <boost/optional.hpp>

class IRgbLed
{
public:

    enum class Color
    {
        INVALID_COLOR,
        RED,
        GREEN,
        BLUE,
    };

    using LedState = bool;
    using Rate = int;

    virtual bool set_state(LedState state) = 0;
    virtual bool set_color(Color color) = 0;
    virtual bool set_rate(Rate rate) = 0;

    virtual boost::optional<LedState> get_state() const = 0;
    virtual boost::optional<Color> get_color() const = 0;
    virtual boost::optional<Rate> get_rate() const = 0;

    virtual ~IRgbLed() = default;
};

#endif // IRGBLED_H
