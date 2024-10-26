#pragma once
#include "t_common.h"

typedef enum
{
	IMMEDIATE,
	ACCUMULATOR,
	ZPG,
	ABS
} address_mode_access;

// Status flags
#define FLAG_CARRY		 0x01
#define FLAG_ZERO		 0x02
#define FLAG_INTERRUPT	 0x04
#define FLAG_DECIMAL	 0x08
#define FLAG_BREAK		 0x10
#define FLAG_OVERFLOW	 0x40
#define FLAG_NEGATIVE	 0x80

// Memory map
#define STACK 0x0100

#define IRQ	0xFFFE
#define BRK	0xFFFF

typedef struct
{
	// registers
	u8 a;
	u8 x;
	u8 y;
	u8 status_register;
	u8 stack_pointer;
	u8 stack_op_pointer;

	u16 program_counter;

	u8 status_flag;

	// NES NTSC
	f32 clock_frequency;
	u64 clock_counter;

	u16 interrupt_vector;
	u16 reset;
	u16 nmi;
	u16 irq;

	// 0x0000 - 0xFFFF
	u8 memory[65536];
	u8 operands[2];
} nes_cpu;


typedef void (*Instructions)(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle);

typedef struct
{
	u8 opcode;
	Instructions instruction;
	u16(*address_mode)(nes_cpu*);
	int mem_type;
	u8 cycle;
} opcode_definition;

typedef struct
{
	u8 opcode;
	char name[4];
	Instructions instruction;
	u16(*address_mode)(nes_cpu*);
	int mem_type;
	u8 cycle;
} opcode_test;

internal opcode_definition _opcode[256];
internal bool running = false;

void nes_init_instructions(nes_cpu* cpu);
void nes_init_cpu(nes_cpu *cpu);
void print_opcode_table();
void nes_cpu_run(nes_cpu* cpu);

