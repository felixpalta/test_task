#ifndef SERVER_H
#define SERVER_H

#include "iserver.h"
#include "irqprocessor.h"
#include <vector>
#include <ostream>
#include <thread>
#include <future>
#include <functional>

class Server : public IServer
{
public:
    using RqProcessorPtr = std::shared_ptr<IRqProcessor>;

    Server(std::ostream& err_stream, RqProcessorPtr rq_processor);
    void add(IOPtr io_channel) override;
    void run() override;

private:
    std::ostream& m_err;
    RqProcessorPtr m_rq_processor;
    using Task = std::function<void(void)>;
    std::vector<std::future<void>> m_futures;
};

#endif // SERVER_H
