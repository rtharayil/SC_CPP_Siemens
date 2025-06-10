
# 🔍 Buffer Overflow in C: Deep Dive into Code and Memory Layout

## 📄 Code Summary

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

const char *PASSWORD_FILE = "rictro";

int main() {
    char input[8];
    char password[8];

    std::sscanf(PASSWORD_FILE, "%s", password);

    std::cout << "Enter password: ";
    std::cin >> input;

    // Debug prints
    std::cout << "Address of input: " << &input << "\n";
    std::cout << "Address of password: " << &password << "\n";
    std::cout << "Input: " << input << "\n";
    std::cout << "Password: " << password << "\n";

    if (std::strncmp(password, input, 8) == 0)
        std::cout << "Access granted\n";
    else
        std::cout << "Access denied\n";

    return 0;
}
```

---

## 🧪 Compilation: Building the Vulnerable Binary

To compile the code in a way that makes it vulnerable to buffer overflow, use:

```bash
gcc -g -fno-stack-protector -no-pie BO.c -o BO
```

### 🔧 Explanation of Flags

| Flag                   | Meaning                                                                |
| ---------------------- | ---------------------------------------------------------------------- |
| `-g`                   | Includes debug information for tools like `gdb`                        |
| `-fno-stack-protector` | Disables stack canary protection, allowing easier buffer overflow      |
| `-no-pie`              | Disables Position Independent Executable (PIE), keeps static addresses |
| `-o BO`                | Names the output binary as `BO`                                        |

---

## 🧠 Memory Layout: Stack Frame for `main()`

```
Stack grows ↓

+------------------+ <--- Higher address (e.g., 0x7ffee2a1d888)
|  char password[8]|
+------------------+ <--- e.g., 0x7ffee2a1d880
|   char input[8]  |
+------------------+ <--- Lower address (e.g., 0x7ffee2a1d878)
```

### 📌 Observation:

* Stack memory is allocated from higher to lower addresses.
* In memory, `input` is located **below** `password`.
* If you overflow `input`, you may overwrite `password`.

---

## 💥 How Buffer Overflow Happens

* `input` is an 8-byte buffer.
* Using `std::cin >> input` doesn't restrict input size.
* If a user inputs more than 8 bytes (e.g., 20 characters), it spills over to `password`.

### 🧫 Exploitation Example

User enters:

```
abcdefgh12345678
```

Memory after input:

```
input:    'abcdefgh'
password: '12345678' (overwritten!)
```

Even though `password` was originally set to `"rictro"`, now it's changed by the overflow.

---

## 🛡️ How to Mitigate This

### ✅ 1. Use Safer Input Functions

Avoid `std::cin >> input` for `char[]`. Instead, use `std::cin.getline()` or `fgets()`:

```cpp
std::cin.getline(input, sizeof(input));
```

### ✅ 2. Enable Compiler Protections

Compile with security features:

```bash
gcc -g -fstack-protector-all -D_FORTIFY_SOURCE=2 -O2 BO.c -o BO
```

* `-fstack-protector-all`: Enables stack canary for all functions
* `-D_FORTIFY_SOURCE=2`: Adds bounds checking on common functions

### ✅ 3. Use Position Independent Executables (PIE)

```bash
gcc -fPIE -pie BO.c -o BO
```

This makes memory layout randomized, reducing predictability.

### ✅ 4. Use Modern C++ Practices

Use `std::string` instead of raw character arrays:

```cpp
std::string input;
std::cin >> input;
```

---

## 🔎 Visual Diagram

```plaintext
Memory Layout:

     Stack
   +----------+  <-- Higher Address
   | password |  --> Can be OVERWRITTEN if input overflows
   +----------+
   |  input   |  <-- Overflow happens here
   +----------+  <-- Lower Address

Input > 8 bytes
   ↓
Overwrites adjacent memory (password)
```

---

## 🚫 Real-World Impact

If `password` were storing a real secret or controlling access:

* Buffer overflow could let an attacker bypass authentication.
* Worse, could overwrite return addresses (control execution).

---

## ✅ Final Best Practices

* **Use C++ strings**: `std::string` is safer and easier.
* **Validate input sizes**: Always check or restrict input.
* **Enable compiler protections**: Use all security flags.
* **Run with ASLR**: Use modern OS protections.

---

