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
  const char* IP;
  const char* Username;
};

// TODO: Move input gathering out of the main and into this function.
// It should return the newly created struct containing ip/username.
// The idea is this gather the info and pass the struct on to doLinux/DoWindows
// Example: connectionInfo con = gatherInput();
//          doWinCmd(con)
connectionInfo gatherInput() {
  conectionInfo ci;

  std::cout << "please enter an ip: \n";
  std::cin >> ci.IP;
  std::cout << "\n";

  std::cout << "please enter a username: \n";
  std::cin >> ci.Username;
  std::cout << "\n";

  return ci;
};

// TODO: Move operating system detection logic out of main() and into its own function here.
// With a boolean return, the OS detection can be used to run the appropriate command witha  ternary operator
// Example: isWindows() ? doWinCmd : doLinuxCmd;
// The above example checks the output of isWindows, and runs doWinCmd if true, and doLinuxCmd is false.
bool isWindows() {
  std::regex match("(Windows)(.*)");

  std::string result execSSH("wmic os get Caption");

  if (std::regex_search(result, match)){
    return 1;
    std::cerr << "This is a windows PC.\n";
  }

  return 0;
};

// TODO: Change the parameter to take in a 'connectionInfo' struct instead of individual string values.
void doLinuxCmd (const connectionInfo&) {
    std::string ip = connectionInfo.IP;
    std::string Username = connectionInfo.Username;

    std::string combined {std::string(username) + "@" + std::string(ip)};

    std::string filepath {"/etc/ssh"};
    std::string command {"scp sshd_config " + combined + ":" + filepath};

    const char* comb = command.c_str();
    
    std::string output = execSSH(comb);
    std::cout << "ssh cmd ran for linux \n";
}

// TODO: Change the parameter to take in a 'connectionInfo' struct instead of individual string values.
void doWinCmd (const connectionInfo&){
    std::string ip = connectionInfo.IP;
    std::string Username = connectionInfo.Username;

    std::string combined {std::string(username) + "@" + std::string(ip)};

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

    isWindows() ? dowWinCmd(con) : doLinuxCmd(con);

    return 0;
}
