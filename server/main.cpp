#include "rgbled.h"
#include "concurrentserver.h"
#include "singlethreadserver.h"
#include "ledprotocolhelper.h"
#include "rqprocessor.h"
#include "args.h"
#include "singlefifoproducer.h"
#include "singlefifo.h"
#include <iostream>

using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::cerr;
using std::cin;
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

static void print_usage(std::ostream& out, char *name)
{
    out << "Usage: " << name << " input_pipe output_pipe\n";
}

int main(int argc, char **argv)
try
{
    Args args(argc, argv);

    auto service_pipe = make_shared<SingleFifo>(args.input_pipe_name());

    auto led = make_shared<RgbLed>(cout);
    auto led_protocol_helper = make_shared<LedProtocolHelper>(led);

    RqProcessorPtr rq_processor = make_shared<RqProcessor>(cerr);
    add_led_handlers(rq_processor, led_protocol_helper);

    auto producer = make_shared<SingleFifoProducer>(service_pipe);

    ConcurrentServer server(cerr, rq_processor, producer);
    server.run();
}
catch (Args::InvalidArgs& e)
{
    cerr << e.what() << '\n';
    print_usage(cerr, argv[0]);
    return 1;
}
catch (exception &e)
{
    cerr << "main() exception: " << e.what() << '\n';
    return 2;
}
catch (...)
{
    cerr << "Unknown exception" << '\n';
    return 3;
}
