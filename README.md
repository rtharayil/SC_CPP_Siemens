# SC_CPP_Siemens



Step 1: Access the server
ssh username@128.199.23.136
( For eg : username : batch1
           Password : Training@XXXX )
Batch list attached
Step 2 : Run the containers
Access at https://training.quadralogics.com/port/<number>/


To **disable and enable address space layout randomization (ASLR)** on Ubuntu (and most Linux systems), you can use the following commands:

---

## 🔐 **Disable ASLR (for debugging, exploit development)**

```bash
sudo bash -c 'echo 0 > /proc/sys/kernel/randomize_va_space'
```

This sets ASLR to **0** — meaning **no address randomization** (all addresses stay fixed).

---

## 🔐 **Enable ASLR (default)**

```bash
sudo bash -c 'echo 2 > /proc/sys/kernel/randomize_va_space'
```

This sets ASLR to **full randomization**, which is the default on most modern Linux systems.

---

## 🧪 ASLR Modes

| Value | Mode               | Description                                       |
| ----- | ------------------ | ------------------------------------------------- |
| `0`   | Disabled           | No randomization                                  |
| `1`   | Conservative       | Randomize stack, heap, and shared libs            |
| `2`   | Full randomization | Full address space layout randomization (default) |

---


