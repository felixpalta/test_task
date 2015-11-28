#include "abstractrqhandler.h"
#include <algorithm>
#include <functional>

const std::map<const std::string, AbstractRqHandler::RqType> AbstractRqHandler::name_to_rq_map =
{
    {"get-led-color", RqType::LED_GET_COLOR},
    {"set-led-color", RqType::LED_SET_COLOR},
    {"get-led-rate", RqType::LED_GET_RATE},
    {"set-led-rate", RqType::LED_SET_RATE},
    {"get-led-state", RqType::LED_GET_STATUS},
    {"set-led-state", RqType::LED_SET_STATUS},
};

AbstractRqHandler::RqType AbstractRqHandler::get_rq_type(const std::string& request_name)
{
    auto iter = name_to_rq_map.find(request_name);
    if (iter != name_to_rq_map.end())
    {
        return iter->second;
    }
    return RqType::INVALID_RQ_TYPE;
}

std::string AbstractRqHandler::process_request(const std::string& input)
{
    std::string params;
    RqType rq_type = extract_rq_type_and_params(input, params);
    return process_rq(rq_type, params);
}

AbstractRqHandler::RqType AbstractRqHandler::extract_rq_type_and_params(const std::string& full_input, std::string& params)
{
    if (full_input.length() == 0)
        throw ParamParsingException("extract_rq_type_and_params(): input string is empty");

    auto not_space_f = [](char c){return !std::isspace(c);};

    auto is_space_f = [](char c){return std::isspace(c);};

    // Find first non-whitespace character.
    auto rq_name_begin = std::find_if(full_input.cbegin(), full_input.cend(), not_space_f);

    if (rq_name_begin == full_input.cend())
        throw ParamParsingException("extract_rq_type_and_params(): request name not found");

    // Read request name until end of full_input or until first whitespace character;
    auto rq_name_end = std::find_if(rq_name_begin, full_input.cend(), is_space_f);

    auto rq_name = std::string(rq_name_begin, rq_name_end);

    // Parameter name is either full string or first substring, depending on pos.
    RqType rq_type = get_rq_type(rq_name);

    params = std::string(rq_name_end, full_input.cend());

    return rq_type;
}
