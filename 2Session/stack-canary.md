A **stack canary** is a security feature used to **detect and prevent buffer overflows** on the stack, especially when trying to overwrite important control data like the **return address**.

---

## 🛡️ What Is It?

A **stack canary** is a special value placed on the stack **between local variables** (like buffers) and **control data** (like the return address).

* If a buffer overflow happens, it will likely **overwrite the canary first** before reaching the return address.
* Before a function returns, the program checks if the canary value has been changed.

  * If it **has been modified**, the program **aborts execution immediately**, preventing the attack.

---

## 📦 Stack Layout With Canary (Simplified)

```
[ buffer (char input[8])   ] ← vulnerable area
[ canary value             ] ← inserted by compiler
[ saved base pointer (RBP) ]
[ return address (RIP)     ]
```

---

### 🔁 Function Flow With Stack Canary

1. When a function begins:

   * The canary value is **pushed** onto the stack.
2. If an overflow occurs (e.g., writing beyond `input[8]`), it may **overwrite the canary**.
3. Before returning from the function:

   * The program **checks the canary**.
   * If it's **unchanged**, return proceeds normally.
   * If it's **changed**, the program **calls `__stack_chk_fail()`** and exits immediately.

---

## 🐍 Why It's Called a "Canary"

Named after **"canary in a coal mine"** — early miners brought birds underground because they were more sensitive to toxic gases. If the canary died, miners knew to escape.

Likewise, if the stack canary is "killed" (overwritten), the program knows something went wrong.

---

## 🧪 Example Without and With Canary

### Without Canary:

```bash
gcc -no-pie -fno-stack-protector vuln.c -o vuln
```

### With Canary (default):

```bash
gcc vuln.c -o vuln
```

Use `checksec` (Linux tool) to confirm:

```bash
checksec --file=vuln
```

Output shows:

```
Canary found:    Yes
```

---

## 🧠 Mitigating Buffer Overflows

| Technique         | Protects Against             |
| ----------------- | ---------------------------- |
| ✅ Stack canary    | Stack-based buffer overflows |
| ✅ ASLR            | Return-to-libc, ROP          |
| ✅ DEP/NX bit      | Code execution on stack      |
| ✅ PIE executables | Code address predictability  |

---

## 🧬 Example Canary in Assembly

You might see this in disassembly:

```asm
mov    rax, QWORD PTR fs:0x28    ; load canary
mov    QWORD PTR [rbp-0x8], rax  ; store canary on stack
...
mov    rax, QWORD PTR [rbp-0x8]  ; load stored canary
xor    rax, QWORD PTR fs:0x28    ; compare with original
jne    __stack_chk_fail          ; abort if changed
```

---


