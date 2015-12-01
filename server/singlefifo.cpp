#include "singlefifo.h"
#include <fstream>
#include <iostream>

extern "C"
{
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
}

SingleFifo::SingleFifo(const std::string& filename)
    : m_filename(filename)
{
    if (!file_exists(filename))
    {
        int status = mkfifo(m_filename.c_str(), S_IRUSR | S_IWUSR);
        if (status)
            throw InternalException("Unable to create FIFO: " + filename);
    }
}

std::string SingleFifo::read_input_line_blocking()
{
    std::ifstream ifs(m_filename);

    if (!ifs)
        throw InternalException("SingleFifo: Unable to open input pipe for reading");
    std::string input_buf;

    while (!std::getline(ifs, input_buf) || input_buf.empty())
    {
        ifs.clear();
    }
    return input_buf;
}

void SingleFifo::write_output_line_blocking(const std::string &out_s)
{
    std::ofstream ofs(m_filename);

    if (!ofs)
        throw InternalException("SingleFifo: Unable to open output pipe for writing");
    ofs << out_s << std::endl;
}

bool SingleFifo::file_exists(const std::string &file_name)
{
    struct stat buf;
    return stat(file_name.c_str(), &buf) == 0;
}
