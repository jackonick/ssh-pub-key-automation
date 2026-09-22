#include <iostream>
#include <cstdio>
#include <array>
#include <memory>
#include <regex>
#include <fstream>
#include "pubkeyauth.h"
std::string doCmd(const char* cmd) {
    std::array<char, 256> buffer;
    std::string result;
    
    std::unique_ptr <FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

    if (!pipe) {
        throw std::runtime_error("popem() failed");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
        result += buffer.data();
        std::cerr << result;
    }

    return result;
}

connectionInfo gatherInput() {
  connectionInfo ci;

  std::cout << "please enter an ip: \n";
  std::cin >> ci.IP;
  std::cout << "\n";

  std::cout << "please enter a username: \n";
  std::cin >> ci.Username;
  std::cout << "\n";

  return ci;
};

bool isWindows() {
  std::regex match("(Windows)(.*)");

  std::string result = doCmd("wmic os get Caption");

  if (std::regex_search(result, match)){
    std::cerr << "This is a windows PC.\n";
    return 1;
  }

  return 0;
};

std::string assemble_linux_command(const connectionInfo& ci, std::string filepath){

  return "TEST";
};

std::string assemble_win_command(const connectionInfo& ci, std::string filepath){

  return 0;
};

void doLinuxCmd (const connectionInfo& ci) {
    std::cout << "Starting Linux Command \n";
    std::string combined {ci.Username + "@" + ci.IP};

    std::string command {"scp ./sshd_config " + combined + ":~"};
    std::cerr << command << "\n";

    std::string check {"ssh -q " + combined + " '[ -f ~./sshd_config ]' && echo \"File exists\" || echo \"File does not exist\""};

    const char* comb = command.c_str();
    const char* check2 = check.c_str();

    std::string output = doCmd(comb);
    std::string check_out = doCmd(check2);

    std::cerr << output << "\n";
    std::cerr << check_out << "\n";
}

void doWinCmd (const connectionInfo& ci){
    std::string combined {ci.Username + "@" + ci.IP};

    //std::string filepath {""};
    std::string command {"scp sshd_config " + combined + ":~"};

    //std::string access_cmd {"Start-Process notepad " + filepath + " -Verb runAs"};
    //std::cerr << access_cmd;

    const char* comb = command.c_str();
    //const char* ac_cmd = access_cmd.c_str();

    //std::string access = doCmd(ac_cmd);

    std::string output = doCmd(comb);
    std::cerr << "ssh cmd ran for windows \n";
}

#ifndef UNIT_TESTING
int main() {
    connectionInfo con = gatherInput();

    isWindows() ? doWinCmd(con) : doLinuxCmd(con);

    return 0;
}
#endif
