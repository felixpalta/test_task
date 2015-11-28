#ifndef IBLOCKINGIOCHANNEL_H
#define IBLOCKINGIOCHANNEL_H

#include <string>

class IBlockingIOChannel
{
public:
    /**
     * Blocks until a line is read from input,
     * trailing newline character is discarded.
     */
    virtual std::string read_input_line_blocking() = 0;

    /**
     * Adds newline to to out_s, writes it to output and
     * blocks until writing is finished.
     */
    virtual void write_output_line_blocking(const std::string &out_s) = 0;

    virtual ~IBlockingIOChannel() = default;
};

#endif // IBLOCKINGIOCHANNEL_H
