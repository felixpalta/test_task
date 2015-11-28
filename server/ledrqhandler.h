#ifndef LEDRQHANDLER_H
#define LEDRQHANDLER_H

#include "abstractrqhandler.h"
#include "irgbled.h"
#include <memory>
#include <ostream>

class LedRqHandler : public AbstractRqHandler
{
public:
    LedRqHandler(std::shared_ptr<IRgbLed> led, std::ostream& err_stream);

private:
    std::shared_ptr<IRgbLed> m_rgb_led;
    std::ostream& m_err;

    virtual std::string process_rq(RqType rq_type, const std::string& params) override;

    static std::string get_ok_with_result(const std::string &result);
    static std::string get_ok_string();
    static std::string get_failed_string();

    static std::string get_color_name(IRgbLed::Color color);
    static IRgbLed::Color get_color_value(const std::string &s);

    static std::string get_state_name(IRgbLed::LedState state);
    static IRgbLed::LedState get_state_value(const std::string &s);

    static IRgbLed::Rate get_rate_value(const std::string& s);

    static std::string strip(const std::string &params);

    LedRqHandler(const LedRqHandler&) = delete;
    LedRqHandler& operator=(const LedRqHandler&) = delete;

};

#endif // LEDRQHANDLER_H
