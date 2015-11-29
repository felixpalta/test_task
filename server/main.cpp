#include "rgbled.h"
#include "fifopair.h"
#include "server.h"
#include "ledprotocolhelper.h"
#include "rqhandler.h"
#include <iostream>

using namespace std;

using RqHandlerPtr = std::shared_ptr<RqHandler>;
using LedHelperPtr = std::shared_ptr<LedProtocolHelper>;

static RqHandlerPtr g_rq_processor = make_shared<RqHandler>(cerr);

static void add_led_handlers(RqHandlerPtr rq_processor, LedHelperPtr led_helper)
{
    rq_processor->add_handler("get-led-color", [led_helper](const std::string& params) { return led_helper->get_color(params); });
    rq_processor->add_handler("set-led-color", [led_helper](const std::string& params) { return led_helper->set_color(params); });
    rq_processor->add_handler("get-led-rate", [led_helper](const std::string& params) { return led_helper->get_rate(params); });
    rq_processor->add_handler("set-led-rate", [led_helper](const std::string& params) { return led_helper->set_rate(params); });
    rq_processor->add_handler("get-led-state", [led_helper](const std::string& params) { return led_helper->get_state(params); });
    rq_processor->add_handler("set-led-state", [led_helper](const std::string& params) { return led_helper->set_state(params); });
}

int main()
try
{
    auto led = make_shared<RgbLed>(cout);

    auto led_protocol_helper = make_shared<LedProtocolHelper>(led);

    add_led_handlers(g_rq_processor, led_protocol_helper);

    auto fifo_pair = make_shared<FifoPair>("input_pipe", "output_pipe");

    Server server(cerr);

    server.add(fifo_pair, g_rq_processor);

    server.run();
}
catch (exception &e)
{
    cerr << "main() exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unknown exception" << '\n';
}
