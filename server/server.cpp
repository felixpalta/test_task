#include "server.h"

Server::Server(std::ostream& err_stream)
    : m_err(err_stream),
      m_channel_handler_pair()
{

}


void Server::add(IOPtr io_channel, RqHandlerPtr handler)
{
    m_channel_handler_pair.first = io_channel;
    m_channel_handler_pair.second = handler;
}

void Server::run()
{
    while (true)
    try
    {
        if (!m_channel_handler_pair.first)
            throw std::invalid_argument("Server::io_channel is null");
        if (!m_channel_handler_pair.second)
            throw std::invalid_argument("Server::handler is null");

        std::string input = m_channel_handler_pair.first->read_input_line_blocking();

        std::string params;
        auto rq_type = m_channel_handler_pair.second->extract_rq_type_and_params(input, params);

        std::string output = m_channel_handler_pair.second->process_request(rq_type, params);

        m_channel_handler_pair.first->write_output_line_blocking(output);
    }
    catch (std::exception& e)
    {
        m_err << e.what() << '\n';
    }
}
