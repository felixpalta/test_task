#include "rqprocessor.h"
#include <algorithm>
#include <ostream>

RqProcessor::RqProcessor(std::ostream &err_stream)
    : m_rq_handlers(),
      m_err(err_stream)
{
}

void RqProcessor::add_handler(const std::string &rq_name, Handler h)
{
    m_rq_handlers[rq_name] = h;
}

IRqProcessor::Handler RqProcessor::get_handler(const std::string &rq_name) const
{
    auto iter = m_rq_handlers.find(rq_name);
    if (iter != m_rq_handlers.end())
    {
        return iter->second;
    }
    throw InternalError("RqProcessor::get_handler(): not found: " + rq_name);
}

std::string RqProcessor::process_request(const std::string& input)
try
{
    std::string params;
    std::string rq_name = extract_rq_name_and_params(input, params);

    auto handler = get_handler(rq_name);

    std::string result = handler(params);

    return result.empty() ? get_ok_string() : get_ok_with_result(result);
}
catch (std::exception& e)
{
    m_err << e.what() << '\n';
    return get_failed_string();
}

std::string RqProcessor::get_failed_string()
{
    return "FAILED";
}

std::string RqProcessor::get_ok_string()
{
    return "OK";
}

std::string RqProcessor::get_ok_with_result(const std::string& result)
{
    return std::string("OK " + result);
}

std::string RqProcessor::extract_rq_name_and_params(const std::string& full_input, std::string& params)
{
    if (full_input.length() == 0)
        throw ParamParsingException("extract_rq_name_and_params(): input string is empty");

    auto not_space_f = [](char c){return !std::isspace(c);};

    auto is_space_f = [](char c){return std::isspace(c);};

    // Find first non-whitespace character.
    auto rq_name_begin = std::find_if(full_input.cbegin(), full_input.cend(), not_space_f);

    if (rq_name_begin == full_input.cend())
        throw ParamParsingException("extract_rq_type_and_params(): request name not found");

    // Read request name until end of full_input or until first whitespace character;
    auto rq_name_end = std::find_if(rq_name_begin, full_input.cend(), is_space_f);

    auto rq_name = std::string(rq_name_begin, rq_name_end);

    params = std::string(rq_name_end, full_input.cend());

    return rq_name;
}
