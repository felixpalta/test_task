#include "rgbled.h"
#include "fifopair.h"
#include "server.h"
#include "ledprotocolhelper.h"
#include "rqprocessor.h"
#include <iostream>

using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::cerr;
using std::exception;
using std::string;

using RqProcessorPtr = shared_ptr<IRqProcessor>;
using LedHelperPtr = shared_ptr<LedProtocolHelper>;

static void add_led_handlers(RqProcessorPtr rq_processor, LedHelperPtr led_helper)
{
    rq_processor->add_handler("get-led-color", [led_helper](const string& params) { return led_helper->get_color(params); });
    rq_processor->add_handler("set-led-color", [led_helper](const string& params) { return led_helper->set_color(params); });
    rq_processor->add_handler("get-led-rate", [led_helper](const string& params) { return led_helper->get_rate(params); });
    rq_processor->add_handler("set-led-rate", [led_helper](const string& params) { return led_helper->set_rate(params); });
    rq_processor->add_handler("get-led-state", [led_helper](const string& params) { return led_helper->get_state(params); });
    rq_processor->add_handler("set-led-state", [led_helper](const string& params) { return led_helper->set_state(params); });
}

int main()
try
{
    auto led = make_shared<RgbLed>(cout);

    auto led_protocol_helper = make_shared<LedProtocolHelper>(led);

    RqProcessorPtr rq_processor = make_shared<RqProcessor>(cerr);

    add_led_handlers(rq_processor, led_protocol_helper);

    auto fifo_pair = make_shared<FifoPair>("input_pipe", "output_pipe");

    Server server(cerr);

    server.add(fifo_pair, rq_processor);

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
