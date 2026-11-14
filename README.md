# 6502-CPU

A MOS 6502 emulator in C, the CPU inside the NES.

**It passes nestest**, the standard test ROM for this processor, across the official and the unofficial opcodes. After a run, nestest's two result bytes (`$02` and `$03`) are both `00`, and the trace ends exactly where the reference log does: instruction 8991, `C66E RTS`, `A:00 X:FF Y:15 P:27 SP:FD`, cycle 26554.

## Build and run

```
gcc *.c -o nes6502
./nes6502
```

It loads `nestest.nes` from the current folder, starts at `$C000` and writes a trace of every instruction to `my_nestest.txt`:

```
C000  4C F5 C5 JMP C5F5 = 00A2   00100100   A:00 X:00 Y:00 P:24 SP:FD CYC:7
```

## How it's built

- `cpu.c`: CPU state, the opcode table, the run loop and the trace.
- `instr.c`: the instructions, including the unofficial ones nestest checks (LAX, SAX, DCP, ISC, SLO, RLA, SRE, RRA).
- `am.c`: the thirteen addressing modes, with the extra cycle when an access crosses a page.
- `ines.c`: reads the iNES header and maps the program ROM at `$8000` and `$C000`.

## Limits

- CPU only: no PPU, APU or controllers yet.
- The ROM name and the run length (9,000 instructions) are hardcoded.
