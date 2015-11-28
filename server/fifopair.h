#ifndef FIFOPAIR_H
#define FIFOPAIR_H

#include "iblockingiochannel.h"
#include <fstream>

class FifoPair : public IBlockingIOChannel
{
public:

    FifoPair(const std::string &input, const std::string &output);

    std::string read_input_line_blocking() override;

    void write_output_line_blocking(const std::string &out_s) override;

    ~FifoPair();

private:

    std::string m_input_pipe_name;
    std::string m_output_pipe_name;
};

#endif // FIFOPAIR_H
