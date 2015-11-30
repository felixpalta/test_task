#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <stdexcept>

class Args
{
public:
    Args(int argc, char **argv);

    class InvalidArgs : public std::invalid_argument
    {
    public:
        InvalidArgs() : invalid_argument("Not enough arguments"){}
    };

    enum ServerType
    {
        SINGLE_THREADED,
        CONCURRENT,

    };

    std::string input_pipe_name() const;
    ServerType server_type() const;
private:
    std::string m_input_pipe_name;
    ServerType m_server_type;
};

#endif // ARGS_H
