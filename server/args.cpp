#include "args.h"

Args::Args(int argc, char **argv)
    : m_input_pipe_name()
{
    if (argc < 2)
        throw InvalidArgs();

    m_input_pipe_name = std::string(argv[1]);
}

std::string Args::input_pipe_name()
{
    return m_input_pipe_name;
}
