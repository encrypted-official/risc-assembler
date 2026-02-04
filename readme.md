# tcrs - The Custom Risc Assembler (by encrypted_)

**AI Usage Disclaimer:**  
This project was created entirely without the use of artificial intelligence tools or generative models. Entire codebase is written, as well as maintained manually (by me, for learning purpose). Kindly avoid using generative tools in this project.

This document describes the instruction set architecture (ISA) of **CUSTOM RISC CPU V1**. <br>CRC V1 uses general-purpose registers and two status flags:
- **Z** (Zero)
- **C** (Carry)

---

## 1. No-Operation

| # | Opcode | Flags | Description |
|---|--------|-------|-------------|
| 1 | NOP | -- | Skip one clock cycle |

---

## 2. Logical Instructions

| # | Opcode | Flags | Description |
|---|--------|-------|-------------|
| 2 | AND | Z | Rz ← Rx & Ry |
| 3 | ANDI | Z | Rz ← Rx & IMM |
| 4 | OR | Z | Rz ← Rx \| Ry |
| 5 | ORI | Z | Rz ← Rx \| IMM |
| 6 | EXR | Z | Rz ← Rx ^ Ry |
| 7 | EXRI | Z | Rz ← Rx ^ IMM |

---

## 3. Arithmetic Instructions

| # | Opcode | Flags | Description |
|---|--------|-------|-------------|
| 8 | ADD | Z, C | Rz ← Rx + Ry |
| 9 | ADDI | Z, C | Rz ← Rx + IMM |
| 10 | SUB | Z, C | Rz ← Rx − Ry |

---

## 4. Data Movement Instructions

| # | Opcode | Flags | Description |
|---|--------|-------|-------------|
| 11 | MOV | -- | Rz ← Rx |
| 12 | MOVI | -- | Rz ← IMM |
| 13 | LD | -- | Rz ← M[Address] |
| 14 | LDI | -- | Rz ← M[Rx] |
| 15 | STR | -- | M[Address] ← Rx |
| 16 | STRI | -- | M[Rx] ← Ry |

---

## 5. Control Flow Instructions

| # | Opcode | Flags | Description |
|---|--------|-------|-------------|
| 17 | JMP | -- | Jump to absolute Address |
| 18 | JMPZ | -- | Jump if Z = 1 |
| 19 | JMPZPR | -- | Relative jump if Z = 1 |
| 20 | JMPNZ | -- | Jump if Z = 0 |
| 21 | JMPNZPR | -- | Relative jump if Z = 0 |
| 22 | JMPC | -- | Jump if C = 1 |
| 23 | JMPCPR | -- | Relative jump if C = 1 |
| 24 | JMPNC | -- | Jump if C = 0 |
| 25 | JMPNCPR | -- | Relative jump if C = 0 |

---

## 6. Stack Instructions

| # | Opcode | Flags | Description |
|---|--------|-------|-------------|
| 26 | PUSH | -- | Push Rx onto stack |
| 27 | POP | -- | Pop stack into Rx |

---

## 7. I/O Instructions

| # | Opcode | Flags | Description |
|---|--------|-------|-------------|
| 28 | IN | -- | Rx ← Input port |
| 29 | OUT | -- | Output port ← Rx |

---

## 8. Shift Instructions

| # | Opcode | Flags | Description |
|---|--------|-------|-------------|
| 30 | SL | Z, C | Rz ← Rx << 1 |
| 31 | SR | Z, C | Rz ← Rx >> 1 |

---

## Notes
- Flags are updated only when specified
- Relative jumps are PC-relative
- Stack grows downward in memory