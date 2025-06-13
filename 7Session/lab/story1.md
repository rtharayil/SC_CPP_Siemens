

## ✅ User Story 

**Title**: Secure Initialization and Mode-Based Access for Embedded Fire Panel

**As a** system engineer,
**I want** the fire panel software to securely collect and store user and admin PINs as hashes during initial configuration,
**So that** the system enforces access control based on the mode (User/Admin) and protects sensitive data from tampering.

### 🎯 Acceptance Criteria:

* During first-time setup:

  * The software prompts for a User PIN and an Admin PIN.
  * Both PINs are hashed using a secure algorithm ( bcrypt 12 rounds with salt).
  * The hashed values are stored (in memory for demo; in persistent storage in real systems).
* After initialization:

  * A console menu offers options to:

    * Log in as User
    * Log in as Admin
  * After PIN input, the entered value is hashed and compared to the stored hash.
  * On successful login, a message is shown confirming the mode.
  * On failure, access is denied.

---

Here’s how the **console UI menu** should look like — both for **initial configuration** and **post-initialization login menu**, based on your requirements:

---

## 🛠️ During First-Time Setup

```
=======================================
   Fire Panel Initial Configuration
=======================================

Please set the PINs for both modes.

Enter User PIN     : ****
Enter Admin PIN    : ****

Hashing and saving securely (bcrypt, 12 rounds)...
Initialization complete.
```

---

## 🔐 Login Menu After Initialization

```
=======================================
         Fire Panel Login Menu
=======================================

Select mode to log in:

1. Login as User
2. Login as Admin
3. Exit

Enter choice [1-3]: _
```

---

### ✅ On Successful Login

If User logs in:

```
---------------------------------------
Login successful: User Mode Access
---------------------------------------
[Accessing user functions...]
```

If Admin logs in:

```
---------------------------------------
Login successful: Admin Mode Access
---------------------------------------
[Accessing admin functions...]
```

---

### ❌ On Failed Login

```
---------------------------------------
❌ Invalid PIN. Access Denied.
---------------------------------------
```

---


