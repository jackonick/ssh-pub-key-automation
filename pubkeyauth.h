#ifndef PUBKEYAUTH_H
#define PUBKEYAUTH_H

#include <string>

// Shared struct definition
struct connectionInfo {
    std::string IP;
    std::string Username;
};

// Function declarations (prototypes) you want to use or test across files
std::string assemble_linux_command(const connectionInfo& ci, std::string filepath);
// Add other function declarations here if you want to call/test them elsewhere

#endif 