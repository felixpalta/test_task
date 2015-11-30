#ifndef SINGLEFIFO_H
#define SINGLEFIFO_H

#include "iblockingiochannel.h"
#include <string>


class SingleFifo : public IBlockingIOChannel
{
public:
    SingleFifo(const std::string& filename);

    virtual std::string read_input_line_blocking() override;

    virtual void write_output_line_blocking(const std::string &out_s) override;

    ~SingleFifo() override;
private:
    std::string m_filename;

    bool file_exists(const std::string &file_name);
    void remove_if_exists(const std::string &file_name);
};

#endif // SINGLEFIFO_H