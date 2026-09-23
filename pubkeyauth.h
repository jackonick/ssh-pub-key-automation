#ifndef PUBKEYAUTH_H
#define PUBKEYAUTH_H
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

// Shared struct definition
struct connectionInfo {
    std::string IP;
    std::string Username;
};

// Function declarations (prototypes) you want to use or test across files
std::vector<std::string> read_comp_list(std::filesystem::path file_name);

int secure_copy(std::filesystem::path path, std::string ip);
// Add other function declarations here if you want to call/test them elsewhere
#endif 