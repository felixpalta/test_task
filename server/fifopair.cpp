#include "fifopair.h"
#include <cstdlib>

extern "C"
{
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
}

#include <cstring>
#include <cerrno>

FifoPair::FifoPair(const std::string &input, const std::string &output)
    : m_input_pipe_name(input),
      m_output_pipe_name(output)
{
    remove_if_exists(input);
    remove_if_exists(output);

    int status = mkfifo(m_input_pipe_name.c_str(), S_IRUSR | S_IWUSR);
    if (status)
        throw InternalException("Unable to create input FIFO");

    status = mkfifo(m_output_pipe_name.c_str(), S_IRUSR | S_IWUSR);
    if (status)
        throw InternalException("Unable to create output FIFO");
}

std::string FifoPair::read_input_line_blocking()
{
    int input_pipe_desc =  open(m_input_pipe_name.c_str(), O_RDONLY);
    if (input_pipe_desc < 0)
        throw InternalException("Unable to open input pipe for reading: " + std::string(strerror(errno)));

    std::string input_buf;
    input_buf.reserve(1024);

    char c;

    while (read(input_pipe_desc, &c, 1))
    {
            if (c != '\n')
                input_buf +=c;
            else
                break;
    }

    if (close(input_pipe_desc) != 0)
    {
        throw InternalException("close(input_pipe) error: " + std::string(strerror(errno)));
    }
    return input_buf;
}

void FifoPair::write_output_line_blocking(const std::string &out_s)
{
    int output_pipe_desc = open(m_output_pipe_name.c_str(), O_WRONLY);
    if (output_pipe_desc < 0)
        throw InternalException("Unable to open output pipe for writing: " + std::string(strerror(errno)));

    std::string out_buf = out_s + '\n';

    ssize_t n = write(output_pipe_desc, out_s.c_str(), out_buf.length());
    if (n < 0)
        throw InternalException("write(output_pipe_desc): " + std::string(strerror(errno)));
    if (size_t(n) < out_buf.length())
        throw InternalException("unable to write full buffer using write(output_pipe_desc)");

    if (close(output_pipe_desc) != 0)
    {
        throw InternalException("close(output_pipe_desc) error: " + std::string(strerror(errno)));
    }
}

bool FifoPair::file_exists(const std::string &file_name)
{
    struct stat buf;
    return stat(file_name.c_str(), &buf) == 0;
}

void FifoPair::remove_if_exists(const std::string &file_name)
{
    if (file_exists(file_name))
    {
        int status = remove(file_name.c_str());
        if (status)
            throw InternalException("File exists and cannot be removed: " + file_name);
    }
}

FifoPair::~FifoPair()
{
    int status = remove(m_input_pipe_name.c_str());
    if (status)
        throw InternalException("Unable to remove input FIFO");

    status = remove(m_output_pipe_name.c_str());
    if (status)
        throw InternalException("Unable to remove output FIFO");
}
