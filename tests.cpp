#include <gtest/gtest.h>
#include <string>
#include "pubkeyauth.h"
// Include or declare your structs/functions if they aren't in a header

// Example Test 1: Test connectionInfo structure handling
TEST(ConnectionInfoTest, FieldsAreStoredCorrectly) {
    connectionInfo ci;
    ci.IP = "192.168.1.50";
    ci.Username = "root";

    EXPECT_EQ(ci.IP, "192.168.1.50");
    EXPECT_EQ(ci.Username, "root");
}

// Example Test 2: Basic string formatting logic used in your commands
TEST(CommandLogicTest, UsernameAndIpCombination) {
    connectionInfo ci{"10.0.0.5", "testuser"};
    std::string combined {ci.Username + "@" + ci.IP};
    
    EXPECT_EQ(combined, "testuser@10.0.0.5");
}

TEST(LinuxCommandStructureTest, AssembleTest) {
    connectionInfo ci;
    ci.IP = "192.168.1.50";
    ci.Username = "root";
    
    EXPECT_EQ(assemble_linux_command(ci,"TESTPATH"),"TEST");
}