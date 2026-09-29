#ifndef PUBKEYAUTH_H
#define PUBKEYAUTH_H
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

struct Globals{
  std::string Username {"loc-admin"};
  std::filesystem::path hostList { "./computer_list.txt" };
  std::filesystem::path windowsDestinationPath { "C:\\Users\\" + Username + ".ssh"};
  std::filesystem::path linuxDestinationPath { "/home/" + Username + "/.ssh/config" };
  std::filesystem::path sshd_config { "./sshd_config" };
  std::filesystem::path pubkeyPath { "./id_rsa.pub" };
};

struct CommandResult {
  int exit_code;
  std::string output;
};



// Function declarations (prototypes) you want to use or test across files
std::vector<std::string> read_comp_list(std::filesystem::path file_name);

CommandResult run_command(const std::string& command);


#endif 
