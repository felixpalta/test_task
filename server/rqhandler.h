#ifndef RQHANDLER_H
#define RQHANDLER_H

#include "irqhandler.h"
#include <memory>
#include <map>

class RqHandler : public IRqHandler
{
public:
    RqHandler(std::ostream &err_stream);

    std::string process_request(const std::string& input) override;

    void add_handler(const std::string &rq_name, Handler h) override;

private:
    std::map<const std::string, Handler> m_rq_handlers;

    std::ostream& m_err;

    Handler get_handler(const std::string &rq_name) const override;

    static std::string extract_rq_name_and_params(const std::string& full_input, std::string& params);

    static std::string get_ok_with_result(const std::string &result);
    static std::string get_ok_string();
    static std::string get_failed_string();


};

#endif // RQHANDLER_H
