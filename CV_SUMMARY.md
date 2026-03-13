# Xv6 Process Limiter — CV Summary

## Project Summary

A kernel-level extension to the **xv6 RISC-V operating system** that enforces **per-user process limits**. The project adds User ID (UID) tracking and dynamic process-capacity management directly into the xv6 kernel, demonstrating deep operating-system internals skills: system-call design, process-table manipulation, synchronisation, and user-space testing.

---

## CV Bullet Points

- **Extended the xv6 RISC-V kernel** with per-user process limiting by modifying the core `fork()` path to reject new processes when a user's active-process count reaches a configurable global threshold (`g_maxProcs`).
- **Designed and implemented four new system calls** — `getuid`, `setuid`, `getProcCap`, and `setProcCap` — covering the full stack from syscall-number assignment (`syscall.h`) and dispatch table registration (`syscall.c`) through kernel implementation (`sysproc.c`) to user-space declarations (`user.h`).
- **Augmented the kernel process structure** (`struct proc`) with a `uid` field and enforced UID inheritance in `fork()`, ensuring child processes always run under the same user identity as their parent.
- **Implemented `count_user_procs(int uid)`**, a kernel utility that iterates the process table under locking to count all RUNNABLE/SLEEPING/RUNNING processes belonging to a given user.
- **Wrote a user-space test utility (`processlimiter`)** that programmatically sets UIDs, spawns configurable numbers of child processes, verifies enforcement of the process cap, and optionally benchmarks fork latency.
- **Navigated a real-world OS codebase** (xv6 RISC-V, ~4 000 lines of C and assembly across 64 source files), making minimal, targeted changes while preserving all existing kernel behavior.

---

## Tools & Technologies Used

| Category | Tool / Technology |
|---|---|
| **Programming Language** | C (systems-level, bare-metal) |
| **Instruction Set Architecture** | RISC-V 64-bit |
| **Compiler** | RISC-V GCC toolchain (`riscv64-unknown-elf-gcc`) |
| **Assembler** | GNU Assembler (RISC-V assembly, `.S` files) |
| **Build System** | GNU Make |
| **Emulator / Virtualisation** | QEMU (`qemu-system-riscv64`) |
| **Debugging** | GDB with QEMU remote-debugging target |
| **Synchronisation Primitives** | Spinlocks, sleep locks (kernel-level) |
| **Version Control** | Git / GitHub |
| **Operating System Base** | xv6 RISC-V (MIT, open-source teaching OS) |
