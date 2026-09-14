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


void doLinuxCmd (const std::string& ip ,const std::string& username) {
    std::string combined {std::string(username) + "@" + std::string(ip)};

    std::string filepath {"/etc/ssh"};
    std::string command {"scp sshd_config " + combined + ":" + filepath};

    const char* comb = command.c_str();
    
    std::string output = execSSH(comb);
    std::cout << "ssh cmd ran for linux \n";
}


void doWinCmd (const std::string& ip, const std::string& username ){
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
    std::string ip;
    std::string username;
    std::regex match("(Windows)(.*)");

    std::ofstream log("log.txt");

    bool isWindows = false;

    std::cout << "please enter an ip: \n";
    std::cin >> ip;
    std::cout << "\n";

    std::cout << "please enter a username: \n";
    std::cin >> username;
    std::cout << "\n";

    std::string result = execSSH("wmic os get Caption"); // run win cmd
    std::cout << result << "\n";

    if (std::regex_search(result, match)){
        isWindows = true;
        std::cerr << "this is a windows computer.\n";
    }

    if (isWindows){
        doWinCmd(ip, username);
    }
    else{
        doLinuxCmd(ip, username);
    }

    if (!log.is_open()){
        std::cerr << "log file could not be opened. \n";
        return 1;
    }

    log << "program successfully ran \n";
    log << result << "\n";

    return 0;
}