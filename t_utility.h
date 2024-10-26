#pragma once
#include "t_common.h"
#include "t_cpu.h"

//https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' :  '0') 

void print_binary(u8 value);
void push_stack(nes_cpu* cpu, u8 value);
u8 pull_stack(nes_cpu* cpu);
void print_stack(nes_cpu* cpu);
void print_internal_ram(nes_cpu* cpu, u8 start, u16 end);
void view_status_flag(u8 value);

void push_operand(nes_cpu* cpu, u8 val1, u8 val2);