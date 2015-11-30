#ifndef SINGLEFIFO_H
#define SINGLEFIFO_H

#include "iblockingiochannel.h"
#include <string>

class SingleFifo : public IBlockingIOChannel
{
public:
    SingleFifo(const std::string& filename);

    std::string read_input_line_blocking() override;

    void write_output_line_blocking(const std::string &out_s) override;

private:
    std::string m_filename;

    bool file_exists(const std::string &file_name);

    SingleFifo(const SingleFifo&) = delete;
    SingleFifo& operator=(const SingleFifo&) = delete;
};

#endif // SINGLEFIFO_H
