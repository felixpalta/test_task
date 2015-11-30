#ifndef CONCURRENT_SERVER_H
#define CONCURRENT_SERVER_H

#include "iserver.h"
#include "irqprocessor.h"
#include "iclientproducer.h"
#include <list>
#include <ostream>
#include <future>
#include <functional>

class ConcurrentServer : public IServer
{
public:
    using RqProcessorPtr = std::shared_ptr<IRqProcessor>;
    using ProducerPtr = std::shared_ptr<IClientProducer>;

    ConcurrentServer(std::ostream& err_stream, RqProcessorPtr rq_processor, ProducerPtr producer);
    void add(IOPtr io_channel) override;
    void run() override;

private:
    std::ostream& m_err;
    RqProcessorPtr m_rq_processor;
    ProducerPtr m_producer;
    using Task = std::function<void(void)>;
    using Future = std::future<void>;
    using FuturePtr = std::unique_ptr<Future>;
    std::list<FuturePtr> m_futures;

    ConcurrentServer(const ConcurrentServer&) = delete;
    ConcurrentServer& operator=(const ConcurrentServer&) = delete;
};

#endif // CONCURRENT_SERVER_H
