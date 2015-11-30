#ifndef SINGLETHREADSERVER_H
#define SINGLETHREADSERVER_H

#include "iserver.h"
#include "irqprocessor.h"
#include "iclientproducer.h"
#include <ostream>

class SingleThreadServer : public IServer
{
public:
    using RqProcessorPtr = std::shared_ptr<IRqProcessor>;
    using ProducerPtr = std::shared_ptr<IClientProducer>;

    SingleThreadServer(std::ostream& err_stream,
        RqProcessorPtr rq_processor, ProducerPtr producer);

    /**
     * Blocks until client has been processed.
     */
    void add(IOPtr io_channel) override;
    void run() override;
private:
    std::ostream& m_err;
    RqProcessorPtr m_rq_processor;
    ProducerPtr m_producer;

    SingleThreadServer(const SingleThreadServer&) = delete;
    SingleThreadServer& operator=(const SingleThreadServer&) = delete;
};

#endif // SINGLETHREADSERVER_H
