#include "pubkeyauth.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

// SCP Example: scp [source_file] [user@remote_host:destination_path]


// TODO: DECLARE GLOBAL VARIABLES HERE.
// Should be for things like:
  //  computer lists, 
  //  command strings, 
  //  file names/paths - (Filesystem library included. Use std::filesystem::path instead of strings)


// TODO: Implement the secure_copy function to actually perform the file transfer.
// Use the std::system function to execute the secure copy command (e.g., scp).
/** 
 * Securely copies a file to a remote computer using its IP address or hostname.
 * @param path Path to the input file.
 * @param ip IP address or hostname of the target computer.
 * @return 0 on success, non-zero on failure.
 */
int secure_copy(std::filesystem::path path, std::string ip) {

  return 0;
}


/**
 * Reads computer addresses or hostnames from a file, one entry per line.
 *
 * @param file_name Path to the input file.
 * @return Lines read from the file, or an empty vector if the file cannot
 *         be opened or contains no entries.
 */
std::vector<std::string> read_comp_list(std::filesystem::path file_name) {
  std::ifstream file(file_name);

  std::vector<std::string> ip_list;
  std::string ip;

  while (std::getline(file, ip)) {
    ip_list.push_back(ip);
  }

  return ip_list;
}






#ifndef UNIT_TESTING
int main() {
  

  #ifdef _WIN32
  // Windows-specific includes or definitions can go here.
  #else
  // Non-Windows-specific includes or definitions can go here.
  #endif



  return 0;
}
#endif
