#include "rqhandler.h"
#include <algorithm>
#include <ostream>

RqHandler::RqHandler(HandlerSetPtr handler_set_ptr, std::ostream &err_stream)
    : m_handler_set(handler_set_ptr),
      m_err(err_stream)
{
}

std::string RqHandler::process_request(const std::string& input)
try
{
    std::string params;
    std::string rq_name = extract_rq_name_and_params(input, params);

    auto handler = m_handler_set->get_handler(rq_name);

    std::string result = handler(params);

    return result.empty() ? get_ok_string() : get_ok_with_result(result);
}
catch (std::exception& e)
{
    m_err << e.what() << '\n';
    return get_failed_string();
}

std::string RqHandler::get_failed_string()
{
    return "FAILED";
}

std::string RqHandler::get_ok_string()
{
    return "OK";
}

std::string RqHandler::get_ok_with_result(const std::string& result)
{
    return std::string("OK " + result);
}

std::string RqHandler::extract_rq_name_and_params(const std::string& full_input, std::string& params)
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

// Skip leading whitespace in parameter list and check that there is only 1 parameter in the list.
std::string RqHandler::strip_single_parameter(const std::string &params)
{
    auto params_begin = std::find_if(params.cbegin(), params.cend(), [](char c){return !std::isspace(c);});

    auto params_end = std::find_if(params_begin, params.cend(), [](char c){return std::isspace(c);});

    if (params_end != params.cend())
        throw ParamParsingException("RqHandler::strip_single_parameter(): parameter contains trailing characters: \"" + std::string(params_end, params.cend()) + "\"");

    return std::string(params_begin, params_end);
}
