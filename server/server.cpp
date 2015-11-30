#include "server.h"
#include <thread>
#include <chrono>

Server::Server(std::ostream& err_stream, RqProcessorPtr rq_processor, ProducerPtr producer)
    : m_err(err_stream),
      m_rq_processor(rq_processor),
      m_producer(producer),
      m_futures()
{
}

void Server::add(IOPtr io_channel)
{
    if (!io_channel)
        throw std::invalid_argument("Server::io_channel is null");

    Task task = [this, io_channel]()
        {
                std::string input = io_channel->read_input_line_blocking();
                std::string output = this->m_rq_processor->process_request(input);
                io_channel->write_output_line_blocking(output);
        };

    m_futures.emplace_back(std::async(std::launch::async, task));
}

void Server::run()
{
    while (true)
    {
        IOPtr client = m_producer->wait_for_new_client();

        add(client);

        decltype(m_futures.begin()) it;

//        for (it = m_futures.begin(); it != m_futures.end(); ++it)
//        {
//            auto status = it->wait_for(std::chrono::milliseconds(1));
//            if (status == std::future_status::ready)
//                break;
//        }
//        it->get();
//        if (it != m_futures.end())
//            m_futures.erase(it);
    }
}
