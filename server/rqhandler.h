#ifndef RQHANDLER_H
#define RQHANDLER_H

#include "irqhandler.h"
#include "irqhandlerset.h"
#include <memory>

class RqHandler : public IRqHandler
{
public:
    using HandlerSetPtr = std::shared_ptr<IRqHandlerSet>;

    RqHandler(HandlerSetPtr handler_set_ptr, std::ostream &err_stream);

    std::string process_request(const std::string& input) override;

private:
    HandlerSetPtr m_handler_set;

    std::ostream& m_err;

    static std::string extract_rq_name_and_params(const std::string& full_input, std::string& params);

    static std::string get_ok_with_result(const std::string &result);
    static std::string get_ok_string();
    static std::string get_failed_string();

    static std::string strip_single_parameter(const std::string &params);
};

#endif // RQHANDLER_H
