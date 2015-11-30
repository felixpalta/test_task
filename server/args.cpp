#include "args.h"

Args::Args(int argc, char **argv)
    : m_input_pipe_name(),
      m_server_type(SINGLE_THREADED)
{
    if (argc < 2 || argc > 3)
        throw InvalidArgs();

    m_input_pipe_name = std::string(argv[1]);

    if (argc == 3 && std::string(argv[2]) == "--concurrent")
        m_server_type = CONCURRENT;
}

std::string Args::input_pipe_name() const
{
    return m_input_pipe_name;
}

Args::ServerType Args::server_type() const
{
    return m_server_type;
}
