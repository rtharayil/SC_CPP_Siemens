The **OWASP Top 10 for IoT (Internet of Things)** is a well-researched and community-curated list from the **Open Web Application Security Project (OWASP)**, specifically addressing security concerns unique to embedded and connected devices.

### 🔗 **Official Source:**

**OWASP IoT Top 10 - 2018 Edition (latest stable)**
📎 [https://owasp.org/www-project-internet-of-things/](https://owasp.org/www-project-internet-of-things/)

As of now, the 2018 version is the most cited and accepted version, especially in embedded security training, though a newer edition may be under review. OWASP also maintains **OWASP Top 10 for Web**, **Mobile**, and **Firmware** categories.

---

### 🧩 Mapping to C/C++:

While the **original OWASP list is language-agnostic**, the **C/C++ examples** I provided were custom-developed to show how these vulnerabilities **manifest in real-world embedded codebases**. These examples reflect:

* Patterns observed in real-world CVEs (Common Vulnerabilities and Exposures)
* Research and exploit demos from platforms like:

  * [MITRE's CVE database](https://cve.mitre.org)
  * DEF CON & Black Hat talks
  * ICS-CERT & NVD reports
* Real firmware and embedded device bugs from vendors like: Jeep/Chrysler (Uconnect), Medtronic, TP-Link, Netgear, and more.

---

### 📚 Additional Research Sources for C/C++ in Embedded Security:

| Resource                                                                                           | Description                                         |
| -------------------------------------------------------------------------------------------------- | --------------------------------------------------- |
| [CERT C Coding Standard](https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard) | Secure coding standards for C                       |
| [MITRE CWE](https://cwe.mitre.org/)                                                                | Weaknesses like buffer overflows, command injection |
| [CVE Details](https://www.cvedetails.com/)                                                         | Lookup C/C++ embedded CVEs                          |
| [OWASP Firmware Security Testing Guide](https://owasp.org/www-project-fstg/)                       | Best practices for firmware reviews                 |
| [Black Hat & DEF CON Archives](https://media.defcon.org/)                                          | Real case studies & PoCs                            |



---

## 🔐 **OWASP Top 10 IoT/Embedded Vulnerabilities – with C/C++ Examples**

---

### 🔸 **1. Weak, Guessable, or Hardcoded Passwords**

**Description**: Devices ship with default credentials or use hardcoded values in firmware.

**C/C++ Example**:

```c
// Hardcoded password
const char* password = "admin123";
if (strcmp(input, password) == 0) {
    printf("Access granted\n");
}
```

**Fix**:

* Store credentials securely (e.g., encrypted flash, secure element).
* Require password change on first use.

---

### 🔸 **2. Insecure Network Services**

**Description**: Services exposed over TCP/UDP without encryption/authentication.

**C/C++ Example**:

```c
// Simple TCP server without authentication
listen(sockfd, 5);
while (1) {
    int newsockfd = accept(sockfd, NULL, NULL);
    handle_request(newsockfd);  // No user validation
}
```

**Fix**:

* Authenticate all clients.
* Disable unnecessary services.
* Encrypt traffic (TLS).

---

### 🔸 **3. Insecure Ecosystem Interfaces (Web, Mobile, Cloud)**

**Description**: Vulnerable APIs used by embedded devices or backends.

**C/C++ Example**:

```cpp
// Command injection via insecure web endpoint
std::string cmd = "ping " + user_input;
system(cmd.c_str());  // Dangerous!
```

**Fix**:

* Sanitize input.
* Use safer APIs (e.g., `fork/exec` with args).
* Authenticate API calls.

---

### 🔸 **4. Lack of Secure Update Mechanism**

**Description**: Firmware updates lack integrity or authenticity checks.

**C/C++ Example**:

```c
// Naively flashing firmware
FILE* f = fopen("/dev/mcu_flash", "wb");
fwrite(buf, 1, len, f); // No signature check!
```

**Fix**:

* Digitally sign firmware.
* Use secure bootloaders.
* Validate hash/signature before writing.

---

### 🔸 **5. Use of Insecure or Outdated Components**

**Description**: Outdated open-source libraries with known vulnerabilities.

**C/C++ Example**:

```c
// Using outdated OpenSSL vulnerable to Heartbleed
SSL_read(ssl, buf, 4096);  // Might leak memory
```

**Fix**:

* Regularly audit and patch third-party libraries.
* Track CVEs (e.g., CVE-2014-0160).

---

### 🔸 **6. Insufficient Privacy Protection**

**Description**: Sensitive data exposed or logged insecurely.

**C/C++ Example**:

```c
// Storing credentials in plain text
fprintf(log_file, "User: %s, Pass: %s\n", user, pass);
```

**Fix**:

* Avoid logging secrets.
* Encrypt stored data (e.g., AES).
* Mask passwords in logs/UI.

---

### 🔸 **7. Insecure Data Transfer and Storage**

**Description**: Data exchanged over plaintext or improperly stored.

**C/C++ Example**:

```c
// Sending over plain TCP
send(sockfd, data, strlen(data), 0);  // No TLS!
```

**Fix**:

* Use TLS (e.g., mbedTLS).
* Store sensitive data securely (e.g., encrypted EEPROM).

---

### 🔸 **8. Lack of Device Management**

**Description**: Inability to change credentials, apply patches, or monitor devices.

**C/C++ Note**:

* Lack of secure bootloader prevents OTA patches.
* Static configurations can't be changed post-deployment.

**Fix**:

* Provide CLI/UI to rotate credentials and apply updates.
* Implement audit logging.

---

### 🔸 **9. Insecure Default Settings**

**Description**: Devices ship with open ports, debug mode, etc.

**C/C++ Example**:

```c
// Default open debug interface
start_telnetd();  // Default username/password
```

**Fix**:

* Disable debug/logging in production builds.
* Require secure onboarding process.

---

### 🔸 **10. Lack of Physical Hardening**

**Description**: Attackers extract firmware, data, or debug via JTAG/UART.

**C/C++ Note**:

* Debug headers left exposed.
* Bootloader reads firmware from unprotected flash.

**Fix**:

* Disable debug ports post-manufacturing.
* Use secure boot and encryption.
* Tamper detection.

---

## ✅ Summary Table

| OWASP Issue               | C/C++ Failure Mode Example          | Prevention Tip                           |
| ------------------------- | ----------------------------------- | ---------------------------------------- |
| 1. Weak Passwords         | Hardcoded `strcmp()` checks         | Use user config + secure storage         |
| 2. Insecure Services      | Open TCP ports without auth         | Authenticate + use TLS                   |
| 3. Ecosystem APIs         | `system(cmd)` with user input       | Input validation                         |
| 4. Insecure Update        | No firmware verification            | Signed firmware + secure boot            |
| 5. Outdated Components    | Unpatched OpenSSL usage             | CVE audits + dependency updates          |
| 6. Privacy Leaks          | Logging passwords                   | Mask + encrypt sensitive data            |
| 7. Insecure Transmission  | Plain TCP communication             | Encrypt over-the-air data                |
| 8. Poor Device Management | No patch/update mechanisms          | Support OTA + CLI config                 |
| 9. Insecure Defaults      | Open debug ports, default passwords | Secure-by-default settings               |
| 10. Physical Exposure     | UART/JTAG access                    | Disable interfaces + secure chip storage |

---


