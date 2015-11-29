#ifndef SERVER_H
#define SERVER_H

#include "iserver.h"
#include <utility>
#include <ostream>

class Server : public IServer
{
public:
    Server(std::ostream& err_stream);
    void add(IOPtr io_channel, RqProcessorPtr handler) override;
    void run() override;

private:
    std::ostream& m_err;
    std::pair<IOPtr, RqProcessorPtr> m_channel_handler_pair;
};

#endif // SERVER_H
