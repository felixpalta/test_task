#ifndef ARGS_H
#define ARGS_H

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

    std::string input_pipe_name();
    std::string output_pipe_name();
private:
    std::string m_input_pipe_name;
    std::string m_output_pipe_name;
};

#endif // ARGS_H
