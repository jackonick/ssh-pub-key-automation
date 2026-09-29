add_test([=[SSHTest.AllHostsReachable]=]  /mnt/c/Users/joegf/Documents/Personal/CPP/ssh-pub-key-automation/build_wsl/MySCPProject_Tests [==[--gtest_filter=SSHTest.AllHostsReachable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SSHTest.AllHostsReachable]=]  PROPERTIES DEF_SOURCE_LINE /mnt/c/Users/joegf/Documents/Personal/CPP/ssh-pub-key-automation/tests.cpp:34 WORKING_DIRECTORY /mnt/c/Users/joegf/Documents/Personal/CPP/ssh-pub-key-automation/build_wsl SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  MySCPProject_Tests_TESTS SSHTest.AllHostsReachable)
