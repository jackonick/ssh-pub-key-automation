#include <gtest/gtest.h>
#include <string>
#include "pubkeyauth.h"
#include <filesystem>
#include <iostream>
#include <fstream>

// TEST(ReadComputerListTest, ReadsIPs)
// {   const std::filesystem::path computerFile = "computer_list.txt";
//     const auto computers = read_comp_list("computer_list.txt");

//     ASSERT_EQ(computers.size(), 2);

//     EXPECT_EQ(computers[0], "192.168.100.54");
//     EXPECT_EQ(computers[1], "192.168.100.53");
// }

// TEST (PingTest, AllHostsReachable) {
//     std::ofstream failure_log("ping_failures.log");
//     std::vector<std::string> failed_hosts;

//     ASSERT_TRUE(failure_log.is_open())
//         << "Could not open ping_failures.log";
    
//     for (const auto& ip : read_comp_list(Globals().hostList)) {
//         const std::string command = "ping -c 1 " + ip;

//         const auto result = run_command(command);
//         std::cout << result.exit_code;
//         std::cout << result.output;
//     }
// }

TEST (SSHTest, AllHostsReachable) {
    // SSH AUTOMATED CONNECTION RELIES ON SSHPASS 
    // OTHERWISE WILL BE PROMPTED FOR PASSWORD INPUT
    // NEED TO STORE PASSWORD IN ENV
    // export SSHPASS=<password>
    std::ofstream failure_log("ssh_failures.log");
    std::vector<std::string> failed_hosts;

    ASSERT_TRUE(failure_log.is_open())
        << "Could not open ssh_failures.log";
    
    for (const auto& ip : read_comp_list(Globals().hostList)) {

        // Command to be executed on the remote target goes here.
        
        const std::string target {" ub-serv@" + ip};
        const std::string target_cmd {" scp ./sshd_config " + target + ":" + Globals().linuxDestinationPath.string()};
        const std::string commandSCP {
        std::string("sshpass -e scp ./sshd_config " + target + ":" + Globals().linuxDestinationPath.string())
        };
        const std::string pubkeyMove {" ssh-copy-id -i " + Globals().pubkeyPath.string() + target };

        std::cout << "\nRunning command: " << commandSCP << std::endl;
        const auto result1 = run_command(pubkeyMove);
        const auto result2 = run_command(commandSCP);

        std::cout << "Host: " << ip << "\n";
        std::cout << "Result: " << result1.exit_code << "\n";
        std::cout << "Output:\n" << result1.output << "\n";

        std::cout << "Host: " << ip << "\n";
        std::cout << "Result: " << result2.exit_code << "\n";
        std::cout << "Output:\n" << result2.output << "\n";

        if (result2.exit_code != 0 || result2.output.find("No route to host") != std::string::npos) {
            failed_hosts.push_back(ip);
            failure_log 
                << "========================================\n"
                << "Host: " << ip << "\n"
                << "Command: " << commandSCP << "\n"
                << "Output:\n"
                << result2.output
                << "========================================\n\n";
        }
        EXPECT_EQ(failed_hosts.size(), 0);

    }
}




