#include <iostream>
#include <cstdio>
#include <array>
#include <memory>
#include <regex>
#include <fstream>

std::string execSSH(const char* cmd) {
    std::array<char, 256> buffer;
    std::string result;
    
    std::unique_ptr <FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

    if (!pipe) {
        throw std::runtime_error("popem() failed");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
        result += buffer.data();
    }

    return result;
}

struct connectionInfo {
  std::string IP;
  std::string Username;
};

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

  std::string result = execSSH("wmic os get Caption");

  if (std::regex_search(result, match)){
    std::cerr << "This is a windows PC.\n";
    return 1;
  }

  return 0;
};

void doLinuxCmd (const connectionInfo& ci) {
    std::string combined {ci.Username + "@" + ci.IP};

    std::string filepath {"/etc/ssh"};
    std::string command {"scp sshd_config " + combined + ":" + filepath};

    const char* comb = command.c_str();
    
    std::string output = execSSH(comb);
    std::cout << "ssh cmd ran for linux \n";
}

void doWinCmd (const connectionInfo& ci){
    std::string combined {ci.Username + "@" + ci.IP};

    std::string filepath {"\"${env:ProgramData}/ssh/sshd_config\""};
    std::string command {"scp sshd_config " + combined + ":" + filepath};

    std::string access_cmd {"Start-Process notepad " + filepath + " -Verb runAs"};
    std::cout << access_cmd;

    const char* comb = command.c_str();
    const char* ac_cmd = access_cmd.c_str();

    std::string access = execSSH(ac_cmd);

    std::string output = execSSH(comb);
    std::cerr << "ssh cmd ran for windows \n";
}


int main() {
    connectionInfo con = gatherInput();

    isWindows() ? doWinCmd(con) : doLinuxCmd(con);

    return 0;
}
