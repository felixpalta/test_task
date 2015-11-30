#include "concurrentserver.h"
#include <thread>
#include <chrono>
#include <string>
#include <stdexcept>

ConcurrentServer::ConcurrentServer(std::ostream& err_stream, RqProcessorPtr rq_processor, ProducerPtr producer)
    : m_err(err_stream),
      m_rq_processor(rq_processor),
      m_producer(producer),
      m_futures()
{
}

void ConcurrentServer::add(IOPtr io_channel)
{
    if (!io_channel)
        throw std::invalid_argument("ConcurrentServer::io_channel is null");

    Task task = [this, io_channel]()
        {
                std::string input = io_channel->read_input_line_blocking();
                std::string output = this->m_rq_processor->process_request(input);
                io_channel->write_output_line_blocking(output);
        };

    m_futures.emplace_back(new Future(std::async(std::launch::async, task)));
}

void ConcurrentServer::run()
{
    while (true)
    try
    {
        IOPtr client = m_producer->wait_for_new_client();

        add(client);

        decltype(m_futures.begin()) it;

        for (it = m_futures.begin(); it != m_futures.end(); ++it)
        {
            auto &ptr = *it;
            if (ptr->valid())
            {
                ptr->get();
                break;
            }
        }
        if (it != m_futures.end())
            m_futures.erase(it);
    }
    catch (std::exception& e)
    {
        m_err << "SingleThreadServer::run(): " << e.what() << std::endl;
    }
}
