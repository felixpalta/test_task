#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include "iledmanager.h"
#include "irgbled.h"

class LedManager : public ILedManager
{
private:
    IRgbLed &led_;
public:
    LedManager(IRgbLed &led);

    std::string process_command(const std::string &command) override;
private:
    static std::string get_color_name(IRgbLed::Color color);
    static std::string get_ok_with_result(const std::string &result);
    static std::string get_ok_string();
    static std::string get_failed_string();
    static IRgbLed::Color get_color_value(const std::string &s);
};

#endif // LEDMANAGER_H
