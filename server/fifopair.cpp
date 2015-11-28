#include "fifopair.h"
#include <cstdlib>

extern "C"
{
#include <sys/types.h>
#include <sys/stat.h>
}

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
    // Blocks until this pipe is open for writing
    // on the other end.
    std::ifstream ifs(m_input_pipe_name.c_str());

    if (!ifs)
        throw InternalException("Unable to open input pipe for reading");

    std::string input_buf;

    std::getline(ifs, input_buf);

    return input_buf;
}

void FifoPair::write_output_line_blocking(const std::string &out_s)
{
    // Blocks until this pipe is open for reading
    // on the other end.
    std::ofstream ofs(m_output_pipe_name.c_str());

    if (!ofs)
        throw InternalException("Unable to open output pipe for writing");

    ofs << out_s + '\n';
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
