#ifndef LEDSERVER_H
#define LEDSERVER_H

#include "iledmanager.h"
#include <string>
#include <fstream>

class LedServer
{
public:
    LedServer(const std::string &in, const std::string &out, ILedManager &led_manager);

    void run();

    ~LedServer();
private:
    std::string input_file_name_;
    std::string output_file_name_;

    std::ifstream input_pipe_;
    std::ofstream output_pipe_;

    ILedManager &led_manager_;

    LedServer(const LedServer&) = delete;
    LedServer &operator=(const LedServer&) = delete;

    static void error(const std::string &s);
    static void error(const char *s);

    static bool file_exists(const char *file_name);
    static bool file_exists(const std::string &file_name);

    static void remove_if_exists(const char *file_name);
    static void remove_if_exists(const std::string &file_name);
};

#endif // LEDSERVER_H
