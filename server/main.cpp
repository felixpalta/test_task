#include "rgbled.h"
#include "fifopair.h"
#include "server.h"
#include "rqhandlerset.h"
#include "ledprotocolhelper.h"
#include "rqhandler.h"
#include <iostream>

using namespace std;

using HandlerSetPtr = std::shared_ptr<IRqHandlerSet>;
using LedHelperPtr = std::shared_ptr<LedProtocolHelper>;

static HandlerSetPtr g_handlers = make_shared<RqHandlerSet>();

static void add_led_handlers(HandlerSetPtr handler_set, LedHelperPtr led_helper)
{
    handler_set->add_handler("get-led-color", [led_helper](const std::string& params) { return led_helper->get_color(params); });
    handler_set->add_handler("set-led-color", [led_helper](const std::string& params) { return led_helper->set_color(params); });
    handler_set->add_handler("get-led-rate", [led_helper](const std::string& params) { return led_helper->get_rate(params); });
    handler_set->add_handler("set-led-rate", [led_helper](const std::string& params) { return led_helper->set_rate(params); });
    handler_set->add_handler("get-led-state", [led_helper](const std::string& params) { return led_helper->get_state(params); });
    handler_set->add_handler("set-led-state", [led_helper](const std::string& params) { return led_helper->set_state(params); });
}

int main()
try
{

    auto led = make_shared<RgbLed>(cout);

    auto led_protocol_helper = make_shared<LedProtocolHelper>(led);

    add_led_handlers(g_handlers, led_protocol_helper);

    auto rq_handler = make_shared<RqHandler>(g_handlers, cerr);

    auto fifo_pair = make_shared<FifoPair>("input_pipe", "output_pipe");

    Server server(cerr);

    server.add(fifo_pair, rq_handler);

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
