#include <iostream>
#include <cstdio>
#include <array>
#include <memory>

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


int main(){
    std::string ip;
    std::string username;

    std::cout << "please enter an ip: \n";
    std::cin >> ip;

    std::cout << "please enter a username: \n";
    std::cin >> username;

    std::string combined {std::string(username) + "@" + std::string(ip)};

    std::string filepath {"/etc/ssh"};
    std::string command {"scp sshd_config " + combined + ":" +filepath};

    const char* comb = command.c_str();
    
    std::string output = execSSH(comb);

    return 0;
}