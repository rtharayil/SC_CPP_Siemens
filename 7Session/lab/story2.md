Here’s a **user story** to cover your new feature: the ability for the Admin to set a **Wi-Fi passcode**, which must be encrypted using **AES-256**.

---

## ✅ User Story (Agile Format)

**Title**: Admin Can Securely Set Wi-Fi Passcode Encrypted with AES-256

**As an** administrator of the embedded fire panel,
**I want** to be able to set or update the Wi-Fi passcode after logging in,
**So that** the passcode is securely encrypted using AES-256 and cannot be retrieved in plain text by unauthorized users.

---

### 🎯 Acceptance Criteria:

* After a successful Admin login:

  * The system shows a menu option to **Set Wi-Fi Passcode**.
  * When the passcode is entered:

    * It is encrypted using AES-256.
    * The encrypted passcode is stored (for the prototype: in memory; real-world: EEPROM or file).
* The passcode must be:

  * Encrypted using a **hardcoded symmetric key** (for the prototype).
  * Decryptable only with the correct key.
* There must be no option to **display** the plain text password (only to set or clear it).

---

## 🔐 Technical Notes:

* **AES-256** requires:

  * A 256-bit key (32 bytes).
  * A 128-bit IV (Initialization Vector, 16 bytes).
* You can use OpenSSL’s EVP interface.

---

## 🔧 Suggested Program Structure Update:

Extend the existing menu (post admin login) with options like:

```text
=== Admin Menu ===
1. Set Wi-Fi Passcode
2. Logout
```

On selecting “Set Wi-Fi Passcode”:

* Prompt for passcode.
* Encrypt with AES-256-CBC.
* Store encrypted value.

---
