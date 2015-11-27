#ifndef ILEDMANAGER_H
#define ILEDMANAGER_H

#include <string>

class ILedManager
{
public:
    virtual std::string process_command(const std::string &command) = 0;
    virtual ~ILedManager() = default;
};

#endif // ILEDMANAGER_H
