#include "rgbled.h"
#include "ledrqhandler.h"
#include "fifopair.h"
#include "server.h"
#include <iostream>

using namespace std;

int main()
try
{

    auto led_ptr = make_shared<RgbLed>(cout);

    auto led_handler = make_shared<LedRqHandler>(led_ptr);

    auto fifo_pair = make_shared<FifoPair>("input_pipe", "output_pipe");

    Server server(cerr);

    server.add(fifo_pair, led_handler);

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
