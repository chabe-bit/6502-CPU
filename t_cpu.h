#pragma once
#include "t_common.h"

typedef enum
{
    OPERAND_NONE,
    OPERAND_ADDRESS,
    OPERAND_VALUE,
    OPERAND_ACCUMULATOR
} am_return_type;

typedef struct
{
    am_return_type type;
    union
    {
        u8 value; 
        u16 address; // 8 or 16 bit
    };
} am_t;

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
#define FLAG_UNUSED		 0x20
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
	u8 status_flag;

	f32 clock_frequency;
	u64 clock_counter;

	u8 interrupt_vector;
	u8 reset;
	u8 nmi;
	u8 irq;

    u16 program_counter;
	u8 memory[65536];
	u8 operands[2];
} nes_cpu;


typedef void (*Instructions)(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

typedef struct
{
	u8 opcode;
	Instructions instruction;
	u16(*address_mode)(nes_cpu*, bool);
    bool page_cross_toggle;
	int mem_type;
	u8 cycle;
} opcode_definition;
internal opcode_definition _opcode[256];

///////////////////////////////////////////////////////////////////////////////
typedef void (*instructions_t)(nes_cpu* cpu, am_t mode, u8 cycle);

typedef struct
{
    u8 opcode;
    instructions_t instruction;
    am_t(*mode)(nes_cpu*);
    u8 cycle;
} t_opcode_definition;
internal t_opcode_definition t_opcode[256];

typedef struct
{
	// address and name
	char name[4];
} disassemble;

internal disassemble disassemble_table[256] = {
    {.name = "BRK"}, {.name = "ORA"}, {.name = "KIL"}, {.name = "SLO"}, {.name = "NOP"}, {.name = "ORA"}, {.name = "ASL"}, {.name = "SLO"},
    {.name = "PHP"}, {.name = "ORA"}, {.name = "ASL"}, {.name = "ANC"}, {.name = "NOP"}, {.name = "ORA"}, {.name = "ASL"}, {.name = "SLO"},
    {.name = "BPL"}, {.name = "ORA"}, {.name = "KIL"}, {.name = "SLO"}, {.name = "NOP"}, {.name = "ORA"}, {.name = "ASL"}, {.name = "SLO"},
    {.name = "CLC"}, {.name = "ORA"}, {.name = "NOP"}, {.name = "SLO"}, {.name = "NOP"}, {.name = "ORA"}, {.name = "ASL"}, {.name = "SLO"},
    {.name = "JSR"}, {.name = "AND"}, {.name = "KIL"}, {.name = "RLA"}, {.name = "BIT"}, {.name = "AND"}, {.name = "ROL"}, {.name = "RLA"},
    {.name = "PLP"}, {.name = "AND"}, {.name = "ROL"}, {.name = "ANC"}, {.name = "BIT"}, {.name = "AND"}, {.name = "ROL"}, {.name = "RLA"},
    {.name = "BMI"}, {.name = "AND"}, {.name = "KIL"}, {.name = "RLA"}, {.name = "NOP"}, {.name = "AND"}, {.name = "ROL"}, {.name = "RLA"},
    {.name = "SEC"}, {.name = "AND"}, {.name = "NOP"}, {.name = "RLA"}, {.name = "NOP"}, {.name = "AND"}, {.name = "ROL"}, {.name = "RLA"},
    {.name = "RTI"}, {.name = "EOR"}, {.name = "KIL"}, {.name = "SRE"}, {.name = "NOP"}, {.name = "EOR"}, {.name = "LSR"}, {.name = "SRE"},
    {.name = "PHA"}, {.name = "EOR"}, {.name = "LSR"}, {.name = "ALR"}, {.name = "JMP"}, {.name = "EOR"}, {.name = "LSR"}, {.name = "SRE"},
    {.name = "BVC"}, {.name = "EOR"}, {.name = "KIL"}, {.name = "SRE"}, {.name = "NOP"}, {.name = "EOR"}, {.name = "LSR"}, {.name = "SRE"},
    {.name = "CLI"}, {.name = "EOR"}, {.name = "NOP"}, {.name = "SRE"}, {.name = "NOP"}, {.name = "EOR"}, {.name = "LSR"}, {.name = "SRE"},
    {.name = "RTS"}, {.name = "ADC"}, {.name = "KIL"}, {.name = "RRA"}, {.name = "NOP"}, {.name = "ADC"}, {.name = "ROR"}, {.name = "RRA"},
    {.name = "PLA"}, {.name = "ADC"}, {.name = "ROR"}, {.name = "ARR"}, {.name = "JMP"}, {.name = "ADC"}, {.name = "ROR"}, {.name = "RRA"},
    {.name = "BVS"}, {.name = "ADC"}, {.name = "KIL"}, {.name = "RRA"}, {.name = "NOP"}, {.name = "ADC"}, {.name = "ROR"}, {.name = "RRA"},
    {.name = "SEI"}, {.name = "ADC"}, {.name = "NOP"}, {.name = "RRA"}, {.name = "NOP"}, {.name = "ADC"}, {.name = "ROR"}, {.name = "RRA"},
    {.name = "NOP"}, {.name = "STA"}, {.name = "NOP"}, {.name = "SAX"}, {.name = "STY"}, {.name = "STA"}, {.name = "STX"}, {.name = "SAX"},
    {.name = "DEY"}, {.name = "NOP"}, {.name = "TXA"}, {.name = "XAA"}, {.name = "STY"}, {.name = "STA"}, {.name = "STX"}, {.name = "SAX"},
    {.name = "BCC"}, {.name = "STA"}, {.name = "KIL"}, {.name = "SHA"}, {.name = "STY"}, {.name = "STA"}, {.name = "STX"}, {.name = "SHA"},
    {.name = "TYA"}, {.name = "STA"}, {.name = "TXS"}, {.name = "TAS"}, {.name = "SHY"}, {.name = "STA"}, {.name = "SHX"}, {.name = "SHA"},
    {.name = "LDY"}, {.name = "LDA"}, {.name = "LDX"}, {.name = "LAX"}, {.name = "LDY"}, {.name = "LDA"}, {.name = "LDX"}, {.name = "LAX"},
    {.name = "TAY"}, {.name = "LDA"}, {.name = "TAX"}, {.name = "LAX"}, {.name = "LDY"}, {.name = "LDA"}, {.name = "LDX"}, {.name = "LAX"},
    {.name = "BCS"}, {.name = "LDA"}, {.name = "KIL"}, {.name = "LAX"}, {.name = "LDY"}, {.name = "LDA"}, {.name = "LDX"}, {.name = "LAX"},
    {.name = "CLV"}, {.name = "LDA"}, {.name = "TSX"}, {.name = "LAS"}, {.name = "LDY"}, {.name = "LDA"}, {.name = "LDX"}, {.name = "LAX"},
    {.name = "CPY"}, {.name = "CMP"}, {.name = "NOP"}, {.name = "DCP"}, {.name = "CPY"}, {.name = "CMP"}, {.name = "DEC"}, {.name = "DCP"},
    {.name = "INY"}, {.name = "CMP"}, {.name = "DEX"}, {.name = "AXS"}, {.name = "CPY"}, {.name = "CMP"}, {.name = "DEC"}, {.name = "DCP"},
    {.name = "BNE"}, {.name = "CMP"}, {.name = "KIL"}, {.name = "DCP"}, {.name = "NOP"}, {.name = "CMP"}, {.name = "DEC"}, {.name = "DCP"},
    {.name = "CLD"}, {.name = "CMP"}, {.name = "NOP"}, {.name = "DCP"}, {.name = "NOP"}, {.name = "CMP"}, {.name = "DEC"}, {.name = "DCP"},
    {.name = "CPX"}, {.name = "SBC"}, {.name = "NOP"}, {.name = "ISC"}, {.name = "CPX"}, {.name = "SBC"}, {.name = "INC"}, {.name = "ISC"},
    {.name = "INX"}, {.name = "SBC"}, {.name = "NOP"}, {.name = "SBC"}, {.name = "CPX"}, {.name = "SBC"}, {.name = "INC"}, {.name = "ISC"},
    {.name = "BEQ"}, {.name = "SBC"}, {.name = "KIL"}, {.name = "ISC"}, {.name = "NOP"}, {.name = "SBC"}, {.name = "INC"}, {.name = "ISC"},
    {.name = "SED"}, {.name = "SBC"}, {.name = "NOP"}, {.name = "ISC"}, {.name = "NOP"}, {.name = "SBC"}, {.name = "INC"}, {.name = "ISC"},
};



internal bool running = false;

void nes_init_instructions(nes_cpu* cpu);
void nes_init_cpu(nes_cpu *cpu);
void print_opcode_table();
void nes_cpu_run(nes_cpu* cpu);


void t_nes_init_instructions(nes_cpu* cpu);
