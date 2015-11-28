#ifndef LEDRQHANDLER_H
#define LEDRQHANDLER_H

#include "abstractrqhandler.h"
#include "irgbled.h"
#include <memory>

class LedRqHandler : public AbstractRqHandler
{
public:
    LedRqHandler(std::shared_ptr<IRgbLed> led);

    virtual std::string process_request(RqType rq_type, const std::string& params) override;

private:
    std::shared_ptr<IRgbLed> m_rgb_led;
};

#endif // LEDRQHANDLER_H
