#include "args.h"

Args::Args(int argc, char **argv)
    : m_input_pipe_name(), m_output_pipe_name()
{
    if (argc < 3)
        throw InvalidArgs();

    m_input_pipe_name = std::string(argv[1]);
    m_output_pipe_name = std::string(argv[2]);
}

std::string Args::input_pipe_name()
{
    return m_input_pipe_name;
}

std::string Args::output_pipe_name()
{
    return m_output_pipe_name;
}
