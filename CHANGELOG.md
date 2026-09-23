# C++ Change Comparison Changelog

## Overview

The new implementation moves the project away from a single-target, interactive prototype toward a more modular file-transfer utility.

The primary changes are:

- Removed interactive IP and username input.
    
- Removed runtime Windows/Linux detection.
    
- Removed the generic `doCmd()` command-execution function.
    
- Removed separate Windows and Linux command functions.
    
- Added `read_comp_list()` for reading multiple computers from a file.
    
- Added `secure_copy()` as the dedicated file-transfer function.
    
- Added `std::filesystem::path` for file paths.
    
- Added GoogleTest-based tests.
    
- Moved diagnostic/debug output out of the production source and into the test code.
    
- Added support for excluding `main()` during unit testing.
    

---

# Comparison

|Area|Old Implementation|New Implementation|
|---|---|---|
|Computer input|User enters IP manually|Computer addresses are read from a file|
|Username input|User enters username manually|Removed|
|Computer list|Single computer|`std::vector<std::string>` supports multiple computers|
|File paths|Hard-coded strings|`std::filesystem::path`|
|SCP functionality|Embedded in OS-specific functions|Centralized in `secure_copy()`|
|Command execution|Generic `doCmd()` using `popen()`|Intended to be handled by `secure_copy()`|
|OS detection|Runtime `wmic` + regex|Compile-time `_WIN32`|
|Windows handling|`doWinCmd()`|Removed/consolidated|
|Linux handling|`doLinuxCmd()`|Removed/consolidated|
|SSH verification|Performed after SCP|Removed/not yet replaced|
|Debug output|Mixed into production code|Test-specific output moved to `tests.cpp`|
|Testing|No automated tests|GoogleTest tests added|
|`main()` and testing|Always compiled|Protected with `UNIT_TESTING`|
|Secure copy implementation|Functional SCP command|`secure_copy()` currently a stub|

---

# Removed Components

## `connectionInfo`

### Old

```cpp
struct connectionInfo {
  std::string IP;
  std::string Username;
};
```

The structure was used to store information entered interactively by the user.

### New

Removed.

The new implementation instead passes the required information directly to functions such as:

```cpp
int secure_copy(std::filesystem::path path, std::string ip)
```

---

## `gatherInput()`

### Old

```cpp
connectionInfo gatherInput()
```

This function prompted the user for:

- IP address
    
- Username
    

### New

Removed.

Computer information is now intended to come from a computer-list file through:

```cpp
read_comp_list()
```

This removes the need for interactive input and provides a foundation for handling multiple computers.

# Added Components

## `read_comp_list()`

```cpp
std::vector<std::string> read_comp_list(
    std::filesystem::path file_name
)
```

This function reads computer addresses or hostnames from a file.

Each line is stored as an entry in a vector.

### Example

```text
computer_list.txt
```

```text
192.168.100.54
192.168.100.53
```

The function produces:

```text
[
    "192.168.100.54",
    "192.168.100.53"
]
```

This replaces the previous single-computer interactive input model.

---

## `secure_copy()`

```cpp
int secure_copy(std::filesystem::path path, std::string ip)
```

This function establishes a dedicated location for the secure-copy operation.

The previous implementation built SCP commands directly inside:

```text
doLinuxCmd()
doWinCmd()
```

The new design centralizes this responsibility in:

```text
secure_copy()
```

### Current Status

`secure_copy()` is currently a placeholder:

```cpp
int secure_copy(std::filesystem::path path, std::string ip) {
    return 0;
}
```

The actual SCP implementation still needs to be completed.

---

# Added `std::filesystem`

The new implementation includes:

```cpp
#include <filesystem>
```

and uses:

```cpp
std::filesystem::path
```

instead of relying entirely on strings for file paths.

### Old

```cpp
"sshd_config"
```

### New

```cpp
std::filesystem::path path
```

This makes file-path handling more explicit and allows the secure-copy function to work with different files rather than being tied specifically to `sshd_config`.

---

# Testing Changes

## GoogleTest Added

A new `tests.cpp` file was added using GoogleTest:

```cpp
#include <gtest/gtest.h>
```

Two areas are currently tested.

### Computer List

```cpp
TEST(ReadComputerListTest, ReadsIPs)
```

The test verifies that:

- Two computers are read.
    
- The first IP is correct.
    
- The second IP is correct.
    

### Secure Copy

```cpp
TEST(SecureCopyTest, CopiesFileSuccessfully)
```

The test calls:

```cpp
secure_copy(filePath, ip);
```

and verifies:

```cpp
EXPECT_EQ(result, 0);
```

---

# Debug Output Refactoring

The old source code contained numerous `std::cout` and `std::cerr` statements used for status and debugging.

Examples included:

```cpp
std::cerr << command << "\n";
std::cerr << output << "\n";
std::cerr << check_out << "\n";
```

These statements were removed from the production implementation.

Diagnostic output associated with testing is now contained in `tests.cpp`.

For example:

```cpp
if (result == 0)
{
    std::cout << "PASS: secure copy completed successfully for "
              << ip << '\n';
}
else
{
    std::cerr << "FAIL: secure copy failed for "
              << ip
              << " (return code: " << result << ")\n";
}
```

The actual verification is performed through the GoogleTest assertion:

```cpp
EXPECT_EQ(result, 0);
```

This separates:

```text
Production code
    ↓
Application functionality
```

from:

```text
Test code
    ↓
Assertions + diagnostic output
```

The result is a cleaner production source file with less debugging/status output mixed into the implementation.

---

# Unit Testing Support

The new implementation wraps `main()` with:

```cpp
#ifndef UNIT_TESTING
int main() {
    ...
}
#endif
```

This allows the application entry point to be excluded when compiling the code for unit tests.

The functions can therefore be tested independently without also compiling the application's normal `main()` entry point.

---

# Architectural Comparison

## Old

```text
main()
│
├── gatherInput()
│     └── IP + Username
│
├── isWindows()
│     └── wmic + regex
│
├── doWinCmd()
│     └── doCmd()
│           └── scp
│
└── doLinuxCmd()
      └── doCmd()
            ├── scp
            └── ssh
```

## New

```text
main()
│
└── Future application logic
      │
      ├── read_comp_list()
      │      └── Computer list
      │
      └── secure_copy()
             └── SCP
```

Testing is separated into:

```text
tests.cpp
│
├── ReadComputerListTest
│
└── SecureCopyTest
```

---

# Functionality Removed vs. Replaced

|Removed Functionality|Replacement|
|---|---|
|Manual IP entry|`read_comp_list()`|
|`connectionInfo`|Function parameters|
|Manual username entry|Not currently replaced|
|`doCmd()`|Function-specific command execution|
|`isWindows()`|`_WIN32` compile-time check|
|`doLinuxCmd()`|`secure_copy()`|
|`doWinCmd()`|`secure_copy()`|
|Hard-coded file path|`std::filesystem::path`|
|Production debug output|Test diagnostics in `tests.cpp`|
|Manual verification|GoogleTest assertions|
|Runtime OS detection|Compile-time platform selection|

---

# Functionality Removed Without a Current Replacement

The following functionality existed in the old implementation but is not currently present in the new implementation:

- Username handling.
    
- SSH remote file-existence verification.
    
- SCP command execution itself.
    
- Command output capture.
    
- Runtime command logging.
    
- Windows-specific SCP implementation.
    
- Linux-specific SCP implementation.
    

These may need to be addressed as `secure_copy()` and the rest of the application are implemented.

---

# Summary

The change restructures the application from an interactive prototype into a more modular design.

The old implementation combined:

- User input
    
- OS detection
    
- Command construction
    
- Command execution
    
- SCP
    
- SSH verification
    
- Debug output
    

within the application source.

The new implementation separates these responsibilities by introducing:

- `read_comp_list()` for computer input.
    
- `secure_copy()` for file-transfer functionality.
    
- `std::filesystem::path` for file paths.
    
- GoogleTest for automated verification.
    
- `tests.cpp` for test-specific diagnostic output.
    
- `_WIN32` for compile-time platform-specific behavior.
    
- `UNIT_TESTING` support for test builds.
    

The new structure provides a cleaner foundation for implementing the remaining secure-copy functionality and expanding the application to process multiple target computers.