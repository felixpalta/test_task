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

    class InternalException : public std::runtime_error
    {
    public:
        InternalException(const std::string &msg)
            : std::runtime_error("IRgbLed: " + msg){}
    };

    /**
     * @throw InternalException in case of internal error.
     * @throw std::invalid_argument
     */
    virtual void set_state(LedState state) = 0;
    virtual void set_color(Color color) = 0;
    virtual void set_rate(Rate rate) = 0;


    /**
     * @throw InternalException in case of internal error.
     */
    virtual LedState get_state() const = 0;
    virtual Color get_color() const = 0;
    virtual Rate get_rate() const = 0;

    virtual ~IRgbLed() = default;
};

#endif // IRGBLED_H
