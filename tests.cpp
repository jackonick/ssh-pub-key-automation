#include <gtest/gtest.h>
#include <string>
#include "pubkeyauth.h"
#include <filesystem>
#include <iostream>

TEST(ReadComputerListTest, ReadsIPs)
{   const std::filesystem::path computerFile = "computer_list.txt";
    const auto computers = read_comp_list("computer_list.txt");

    ASSERT_EQ(computers.size(), 2);

    EXPECT_EQ(computers[0], "192.168.100.54");
    EXPECT_EQ(computers[1], "192.168.100.53");
}

TEST(SecureCopyTest, CopiesFileSuccessfully)
{
    const std::filesystem::path filePath = "config.conf";
    const std::string ip = "192.168.100.54";

    int result = secure_copy(filePath, ip);

    if (result == 0)
    {
        std::cout << "PASS: secure copy completed successfully for " << ip << '\n';
    }
    else
    {
        std::cerr << "FAIL: secure copy failed for " << ip
                  << " (return code: " << result << ")\n";
    }

    EXPECT_EQ(result, 0);
    
}

