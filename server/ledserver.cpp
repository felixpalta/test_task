#include "ledserver.h"
#include <cstdio>

extern "C"
{
#include <sys/types.h>
#include <sys/stat.h>
}

using namespace std;

LedServer::LedServer(const string &in, const string &out, ILedManager &led_manager)
    : input_file_name_(in),
      output_file_name_(out),
      led_manager_(led_manager)
{
    remove_if_exists(in);
    remove_if_exists(out);

    int status = mkfifo(in.c_str(), S_IRUSR | S_IWUSR);
    if (status)
        error("Unable to create input FIFO");

    status = mkfifo(out.c_str(), S_IRUSR | S_IWUSR);
    if (status)
        error("Unable to create output FIFO");
}

LedServer::~LedServer()
{
    int status = remove(input_file_name_.c_str());
    if (status)
        error("Unable to remove input FIFO on exit");

    status = remove(output_file_name_.c_str());
    if (status)
        error("Unable to remove output FIFO on exit");
}

void LedServer::run()
{
    while (true)
    {
        // Blocks until this pipe is open for writing
        // on the other end.
        input_pipe_.open(input_file_name_.c_str());

        if (!input_pipe_)
            error("Unable to open input pipe for reading");

        string in_buf, out_buf;

        getline(input_pipe_, in_buf);

        out_buf = led_manager_.process_command(in_buf);

        // Blocks until this pipe is open for reading
        // on the other end.
        output_pipe_.open(output_file_name_.c_str());

        if (!output_pipe_)
            error("Unable to open output pipe for writing");

        output_pipe_ << out_buf;

        // Output pipe closes for writing, so the other (reading) end receives EOF and will have to reopen it.
        // Input pipe closes for reading, so the other (writing) end will have to reopen it.
        output_pipe_.close();
        input_pipe_.close();
    }
}

void LedServer::error(const char *s)
{
    perror(s);
    exit(1);
}

void LedServer::error(const string &s)
{
    error(s.c_str());
}

bool LedServer::file_exists(const char *file_name)
{
    struct stat buf;
    return stat(file_name, &buf) == 0;
}

bool LedServer::file_exists(const string &file_name)
{
    return file_exists(file_name.c_str());
}

void LedServer::remove_if_exists(const char *file_name)
{
    if (file_exists(file_name))
    {
        int status = remove(file_name);
        if (status)
            error("File exists and cannot be removed");
    }
}

void LedServer::remove_if_exists(const string &file_name)
{
    remove_if_exists(file_name.c_str());
}
