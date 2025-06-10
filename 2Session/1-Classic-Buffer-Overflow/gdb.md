

# 🧪 GDB Demo: Buffer Overflow in Real Time

We'll:

1. Compile the program with buffer overflow vulnerability.
2. Run it in GDB.
3. Input more than 8 bytes to overflow `input[]`.
4. Observe how `password[]` is modified in memory.

---

## ✅ Step 1: Compile the Code

Use this command:

```bash
g++ -g  BO.cpp -o BO
```



---

## ✅ Step 2: Start GDB

```bash
gdb ./BO
```

---

## ✅ Step 3: Set Breakpoints

At the end of `main()` to inspect memory after the overflow:

```gdb
(gdb) break main
(gdb) run
```

GDB will pause at the start of `main()`.

---

## ✅ Step 4: Step Through and Observe Memory

### 1. Step through initialization

```gdb
(gdb) next   # char input[8]
(gdb) next   # char password[8]
(gdb) next   # sscanf(...)
(gdb) next   # cout << "Enter password: "
```

### 2. Print the memory addresses

```gdb
(gdb) print &input
(gdb) print &password
```

You’ll get something like:

```gdb
$1 = (char (*)[8]) 0x7fffffffe320
$2 = (char (*)[8]) 0x7fffffffe328
```

→ `input` is at a **lower address**, `password` is right **above it** in memory.

---

## ✅ Step 5: Enter Overflow Input

Let the program continue:

```gdb
(gdb) continue
```

When prompted, **enter more than 8 characters**, like:

```
12345678ABCDEFGH
```

That's **16 characters** — the first 8 go to `input`, the next 8 overwrite `password`.

---

## ✅ Step 6: Inspect Memory After Overflow

After entering input, GDB will break at the next line (after std::cin).

Now dump memory:

```gdb
(gdb) x/16bx &input
```

### Output Example:

```
0x7fffffffe320: 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38  --> '1'-'8'
0x7fffffffe328: 0x41 0x42 0x43 0x44 0x45 0x46 0x47 0x48  --> 'A'-'H'
```

The overflow continued into `password`!

---

## ✅ Step 7: Print Password Content

```gdb
(gdb) print password
$3 = "ABCDEFGH"
```

This confirms `password[]` was **overwritten** by the overflow from `input[]`.

Originally, it was set from `"rictro"` by `sscanf`.

---

## 🔚 Conclusion: What Happened?

```plaintext
input:    12345678        <-- buffer ends here
password: A B C D E F G H <-- got overwritten!
```

This shows a classic **stack-based buffer overflow**, overwriting adjacent variables in memory.

---

## 🛡️ Final Tip: Enable Protections Again

After experimenting, **recompile safely**:

```bash
gcc -g -fstack-protector-all -D_FORTIFY_SOURCE=2 -O2 BO.c -o BO
```


