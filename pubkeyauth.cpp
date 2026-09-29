#include "pubkeyauth.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

CommandResult run_command(const std::string& command) {
  std::string output;

  FILE* pipe = popen((command + " 2>&1").c_str(), "r");

  if (!pipe) {
    return {
      -1,
      "Failed to execute command, no pipe opened\n"
    };
  }

  char buffer[4096];
  
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    output += buffer;
  }

  int result = pclose(pipe);

  return {result, output};

}

/**
 * Reads computer addresses or hostnames from a file, one entry per line.
 *
 * @param file_name Path to the input file.
 * @return Lines read from the file, or an empty vector if the file cannot
 *         be opened or contains no entries.
 */
std::vector<std::string> read_comp_list(std::filesystem::path file_name) {
  std::ifstream file(Globals().hostList);

  std::vector<std::string> ip_list;
  std::string ip;

  while (std::getline(file, ip)) {

    // Strip trailing carriage return (\r) if it exists
    if (!ip.empty() && ip.back() == '\r') {
      ip.pop_back();
    }

    ip_list.push_back(ip);
  }

  return ip_list;
}


#ifndef UNIT_TESTING
int main() {
  
  return 0;
}
#endif
