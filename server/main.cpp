#include "rgbled.h"
#include "ledmanager.h"
#include "ledserver.h"
#include "ledrqhandler.h"
#include <iostream>

using namespace std;

int main()
try
{

    RgbLed led(cout);

    LedManager led_manager(led);

    LedServer led_server("input_pipe", "output_pipe", led_manager);

    led_server.run();

}
catch (exception &e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unknown exception" << '\n';
}
