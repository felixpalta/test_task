#include "singlethreadserver.h"
#include <string>
#include <stdexcept>

SingleThreadServer::SingleThreadServer(std::ostream& err_stream,
    RqProcessorPtr rq_processor, ProducerPtr producer)
    : m_err(err_stream),
      m_rq_processor(rq_processor),
      m_producer(producer)
{
}

void SingleThreadServer::add(IOPtr io_channel)
{
    if (!io_channel)
        throw std::invalid_argument("SingleThreadedServer::io_channel is null");

    std::string input = io_channel->read_input_line_blocking();
    std::string output = this->m_rq_processor->process_request(input);
    io_channel->write_output_line_blocking(output);
}

void SingleThreadServer::run()
{
    while (true)
    try
    {
        IOPtr client = m_producer->wait_for_new_client();
        add(client);
    }
    catch (std::exception& e)
    {
        m_err << "SingleThreadServer::run(): " << e.what() << std::endl;
    }
}
