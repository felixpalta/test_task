#ifndef IRGBLED_H
#define IRGBLED_H

#include <stdexcept>

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

    class IRgbLedInternalException : public std::runtime_error
    {
    public:
        IRgbLedInternalException(const std::string &msg)
            : std::runtime_error("IRgbLedInternalException: " + msg)
        {
        }
    };

    /**
     * @return false in case of invalid parameters.
     * @throw IRgbLedInternalException in case of internal error.
     */
    virtual bool set_state(LedState state) = 0;
    virtual bool set_color(Color color) = 0;
    virtual bool set_rate(Rate rate) = 0;


    /**
     * @throw IRgbLedInternalException in case of internal error.
     */
    virtual LedState get_state() const = 0;
    virtual Color get_color() const = 0;
    virtual Rate get_rate() const = 0;

    virtual ~IRgbLed() = default;
};

#endif // IRGBLED_H
