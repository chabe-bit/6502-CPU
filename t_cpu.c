#include "t_cpu.h"
#include "t_am.h"
#include "t_instr.h"

void nes_init_cpu(nes_cpu* cpu)
{
	cpu->clock_frequency = 1.789773;
	cpu->clock_counter = 7;
	cpu->program_counter = 0xC000;
	cpu->stack_pointer = 0xFD;
	cpu->status_flag = 0x24;
}

void t_nes_init_instructions(nes_cpu* cpu)
{
	for (u8 i = 0; i < 256; i++) {
		t_opcode[i] = (t_opcode_definition){
			.instruction = NULL,
			.mode = NULL,
			.cycle = 0
		};
	}

	t_opcode_definition t_opcode_map[] = {
		{0xA9, t_op_lda, t_rel, 2},

	};


	size_t num_opcodes = sizeof(t_opcode_map) / sizeof(t_opcode_definition);

	for (u8 i = 0; i < num_opcodes; i++)
	{
		u8 opcode = t_opcode_map[i].opcode;
		t_opcode[opcode] = (t_opcode_definition)
		{
			.instruction = t_opcode_map[i].instruction,
			.mode = t_opcode_map[i].mode,
			.cycle = t_opcode_map[i].cycle
		};
	}



}

void nes_init_instructions(nes_cpu* cpu)
{
	for (int i = 0; i < 256; i++) {
		_opcode[i] = (opcode_definition){
			.instruction = NULL,
			.address_mode = NULL,
			.page_cross_toggle = false,
			.mem_type = 0,
			.cycle = 0
		};
	}

    opcode_definition opcode_map[] = {
        // Load Instructions

        // LDA Instructions
        {0xA9, op_lda, am_imm, false, 0, 2},             // LDA Immediate
        {0xAD, op_lda, am_abs, false, 0, 4},             // LDA Absolute
        {0xBD, op_lda, am_abs_x, true, 0, 4},            // LDA Absolute,X
        {0xB9, op_lda, am_abs_y, true, 0, 4},            // LDA Absolute,Y
        {0xA5, op_lda, am_zpg, false, 0, 3},             // LDA Zero Page
        {0xB5, op_lda, am_zpg_x, false, 0, 4},           // LDA Zero Page,X
        {0xA1, op_lda, am_zpg_x_ind, false, 0, 6},       // LDA (Indirect,X)
        {0xB1, op_lda, am_zpg_ind_y, true, 0, 5},        // LDA (Indirect),Y

        // LDX Instructions
        {0xA2, op_ldx, am_imm, false, 0, 2},             // LDX Immediate
        {0xAE, op_ldx, am_abs, false, 0, 4},             // LDX Absolute
        {0xBE, op_ldx, am_abs_y, true, 0, 4},            // LDX Absolute,Y
        {0xA6, op_ldx, am_zpg, false, 0, 3},             // LDX Zero Page
        {0xB6, op_ldx, am_zpg_y, false, 0, 4},           // LDX Zero Page,Y

        // LDY Instructions
        {0xA0, op_ldy, am_imm, false, 0, 2},             // LDY Immediate
        {0xAC, op_ldy, am_abs, false, 0, 4},             // LDY Absolute
        {0xBC, op_ldy, am_abs_x, true, 0, 4},            // LDY Absolute,X
        {0xA4, op_ldy, am_zpg, false, 0, 3},             // LDY Zero Page
        {0xB4, op_ldy, am_zpg_x, false, 0, 4},           // LDY Zero Page,X

        // Store Instructions

        // STA Instructions
        {0x8D, op_sta, am_abs, false, 0, 4},             // STA Absolute
        {0x9D, op_sta, am_abs_x, false, 0, 5},           // STA Absolute,X
        {0x99, op_sta, am_abs_y, false, 0, 5},           // STA Absolute,Y
        {0x85, op_sta, am_zpg, false, 0, 3},             // STA Zero Page
        {0x95, op_sta, am_zpg_x, false, 0, 4},           // STA Zero Page,X
        {0x81, op_sta, am_zpg_x_ind, false, 0, 6},       // STA (Indirect,X)
        {0x91, op_sta, am_zpg_ind_y, false, 0, 6},       // STA (Indirect),Y

        // STX Instructions
        {0x8E, op_stx, am_abs, false, 0, 4},             // STX Absolute
        {0x86, op_stx, am_zpg, false, 0, 3},             // STX Zero Page
        {0x96, op_stx, am_zpg_y, false, 0, 4},           // STX Zero Page,Y

        // STY Instructions
        {0x8C, op_sty, am_abs, false, 0, 4},             // STY Absolute
        {0x84, op_sty, am_zpg, false, 0, 3},             // STY Zero Page
        {0x94, op_sty, am_zpg_x, false, 0, 4},           // STY Zero Page,X

        // Transfer Instructions
        {0xAA, op_tax, am_impl, false, 0, 2},            // TAX
        {0xA8, op_tay, am_impl, false, 0, 2},            // TAY
        {0xBA, op_tsx, am_impl, false, 0, 2},            // TSX
        {0x8A, op_txa, am_impl, false, 0, 2},            // TXA
        {0x9A, op_txs, am_impl, false, 0, 2},            // TXS
        {0x98, op_tya, am_impl, false, 0, 2},            // TYA

        // Stack Instructions
        {0x48, op_pha, am_impl, false, 0, 3},            // PHA
        {0x08, op_php, am_impl, false, 0, 3},            // PHP
        {0x68, op_pla, am_impl, false, 0, 4},            // PLA
        {0x28, op_plp, am_impl, false, 0, 4},            // PLP

        // Shift Instructions

        // ASL Instructions
        {0x0A, op_asl_a, am_a, false, ACCUMULATOR, 2},   // ASL Accumulator
        {0x0E, op_asl, am_abs, false, ABS, 6},           // ASL Absolute
        {0x1E, op_asl, am_abs_x, false, ABS, 7},         // ASL Absolute,X
        {0x06, op_asl, am_zpg, false, ZPG, 5},           // ASL Zero Page
        {0x16, op_asl, am_zpg_x, false, ZPG, 6},         // ASL Zero Page,X

        // LSR Instructions
        {0x4A, op_lsr_a, am_a, false, ACCUMULATOR, 2},   // LSR Accumulator
        {0x4E, op_lsr, am_abs, false, ABS, 6},           // LSR Absolute
        {0x5E, op_lsr, am_abs_x, false, ABS, 7},         // LSR Absolute,X
        {0x46, op_lsr, am_zpg, false, ZPG, 5},           // LSR Zero Page
        {0x56, op_lsr, am_zpg_x, false, ZPG, 6},         // LSR Zero Page,X

        // ROL Instructions
        {0x2A, op_rol_a, am_a, false, ACCUMULATOR, 2},   // ROL Accumulator
        {0x2E, op_rol, am_abs, false, ABS, 6},           // ROL Absolute
        {0x3E, op_rol, am_abs_x, false, ABS, 7},         // ROL Absolute,X
        {0x26, op_rol, am_zpg, false, ZPG, 5},           // ROL Zero Page
        {0x36, op_rol, am_zpg_x, false, ZPG, 6},         // ROL Zero Page,X

        // ROR Instructions
        {0x6A, op_ror_a, am_a, false, ACCUMULATOR, 2},   // ROR Accumulator
        {0x6E, op_ror, am_abs, false, ABS, 6},           // ROR Absolute
        {0x7E, op_ror, am_abs_x, false, ABS, 7},         // ROR Absolute,X
        {0x66, op_ror, am_zpg, false, ZPG, 5},           // ROR Zero Page
        {0x76, op_ror, am_zpg_x, false, ZPG, 6},         // ROR Zero Page,X

        // Logic Instructions

        // AND Instructions
        {0x29, op_and, am_imm, false, IMMEDIATE, 2},     // AND Immediate
        {0x2D, op_and, am_abs, false, ABS, 4},           // AND Absolute
        {0x3D, op_and, am_abs_x, true, ABS, 4},          // AND Absolute,X
        {0x39, op_and, am_abs_y, true, ABS, 4},          // AND Absolute,Y
        {0x25, op_and, am_zpg, false, ZPG, 3},           // AND Zero Page
        {0x35, op_and, am_zpg_x, false, ZPG, 4},         // AND Zero Page,X
        {0x21, op_and, am_zpg_x_ind, false, 0, 6},       // AND (Indirect,X)
        {0x31, op_and, am_zpg_ind_y, true, 0, 5},        // AND (Indirect),Y

        // BIT Instructions
        {0x2C, op_bit, am_abs, false, ABS, 4},           // BIT Absolute
        {0x24, op_bit, am_zpg, false, ZPG, 3},           // BIT Zero Page

        // EOR Instructions
        {0x49, op_eor, am_imm, false, 0, 2},             // EOR Immediate
        {0x4D, op_eor, am_abs, false, 0, 4},             // EOR Absolute
        {0x5D, op_eor, am_abs_x, true, 0, 4},            // EOR Absolute,X
        {0x59, op_eor, am_abs_y, true, 0, 4},            // EOR Absolute,Y
        {0x45, op_eor, am_zpg, false, ZPG, 3},           // EOR Zero Page
        {0x55, op_eor, am_zpg_x, false, ZPG, 4},         // EOR Zero Page,X
        {0x41, op_eor, am_zpg_x_ind, false, 0, 6},       // EOR (Indirect,X)
        {0x51, op_eor, am_zpg_ind_y, true, 0, 5},        // EOR (Indirect),Y

        // ORA Instructions
        {0x09, op_ora, am_imm, false, 0, 2},             // ORA Immediate
        {0x0D, op_ora, am_abs, false, 0, 4},             // ORA Absolute
        {0x1D, op_ora, am_abs_x, true, 0, 4},            // ORA Absolute,X
        {0x19, op_ora, am_abs_y, true, 0, 4},            // ORA Absolute,Y
        {0x05, op_ora, am_zpg, false, ZPG, 3},           // ORA Zero Page
        {0x15, op_ora, am_zpg_x, false, ZPG, 4},         // ORA Zero Page,X
        {0x01, op_ora, am_zpg_x_ind, false, 0, 6},       // ORA (Indirect,X)
        {0x11, op_ora, am_zpg_ind_y, true, 0, 5},        // ORA (Indirect),Y

        // Arithmetic Instructions

        // ADC Instructions
        {0x69, op_adc, am_imm, false, 0, 2},             // ADC Immediate
        {0x6D, op_adc, am_abs, false, 0, 4},             // ADC Absolute
        {0x7D, op_adc, am_abs_x, true, 0, 4},            // ADC Absolute,X
        {0x79, op_adc, am_abs_y, true, 0, 4},            // ADC Absolute,Y
        {0x65, op_adc, am_zpg, false, ZPG, 3},           // ADC Zero Page
        {0x75, op_adc, am_zpg_x, false, ZPG, 4},         // ADC Zero Page,X
        {0x61, op_adc, am_zpg_x_ind, false, 0, 6},       // ADC (Indirect,X)
        {0x71, op_adc, am_zpg_ind_y, true, 0, 5},        // ADC (Indirect),Y

        // CMP Instructions
        {0xC9, op_cmp, am_imm, false, 0, 2},             // CMP Immediate
        {0xCD, op_cmp, am_abs, false, 0, 4},             // CMP Absolute
        {0xDD, op_cmp, am_abs_x, true, 0, 4},            // CMP Absolute,X
        {0xD9, op_cmp, am_abs_y, true, 0, 4},            // CMP Absolute,Y
        {0xC5, op_cmp, am_zpg, false, ZPG, 3},           // CMP Zero Page
        {0xD5, op_cmp, am_zpg_x, false, ZPG, 4},         // CMP Zero Page,X
        {0xC1, op_cmp, am_zpg_x_ind, false, 0, 6},       // CMP (Indirect,X)
        {0xD1, op_cmp, am_zpg_ind_y, true, 0, 5},        // CMP (Indirect),Y

        // CPX Instructions
        {0xE0, op_cpx, am_imm, false, 0, 2},             // CPX Immediate
        {0xEC, op_cpx, am_abs, false, 0, 4},             // CPX Absolute
        {0xE4, op_cpx, am_zpg, false, ZPG, 3},           // CPX Zero Page

        // CPY Instructions
        {0xC0, op_cpy, am_imm, false, 0, 2},             // CPY Immediate
        {0xCC, op_cpy, am_abs, false, 0, 4},             // CPY Absolute
        {0xC4, op_cpy, am_zpg, false, ZPG, 3},           // CPY Zero Page

        // SBC Instructions
        {0xE9, op_sbc, am_imm, false, 0, 2},             // SBC Immediate
        {0xEB, op_sbc, am_imm, false, 0, 2},             // SBC Immediate (Unofficial)
        {0xED, op_sbc, am_abs, false, 0, 4},             // SBC Absolute
        {0xFD, op_sbc, am_abs_x, true, 0, 4},            // SBC Absolute,X
        {0xF9, op_sbc, am_abs_y, true, 0, 4},            // SBC Absolute,Y
        {0xE5, op_sbc, am_zpg, false, ZPG, 3},           // SBC Zero Page
        {0xF5, op_sbc, am_zpg_x, false, ZPG, 4},         // SBC Zero Page,X
        {0xE1, op_sbc, am_zpg_x_ind, false, 0, 6},       // SBC (Indirect,X)
        {0xF1, op_sbc, am_zpg_ind_y, true, 0, 5},        // SBC (Indirect),Y

        // Increment and Decrement Instructions

        // DEC Instructions
        {0xCE, op_dec, am_abs, false, 0, 6},             // DEC Absolute
        {0xDE, op_dec, am_abs_x, false, 0, 7},           // DEC Absolute,X
        {0xC6, op_dec, am_zpg, false, ZPG, 5},           // DEC Zero Page
        {0xD6, op_dec, am_zpg_x, false, ZPG, 6},         // DEC Zero Page,X

        // DEX and DEY Instructions
        {0xCA, op_dex, am_impl, false, 0, 2},            // DEX
        {0x88, op_dey, am_impl, false, 0, 2},            // DEY

        // INC Instructions
        {0xEE, op_inc, am_abs, false, 0, 6},             // INC Absolute
        {0xFE, op_inc, am_abs_x, false, 0, 7},           // INC Absolute,X
        {0xE6, op_inc, am_zpg, false, ZPG, 5},           // INC Zero Page
        {0xF6, op_inc, am_zpg_x, false, ZPG, 6},         // INC Zero Page,X

        // INX and INY Instructions
        {0xE8, op_inx, am_impl, false, 0, 2},            // INX
        {0xC8, op_iny, am_impl, false, 0, 2},            // INY

        // Control Instructions

        {0x00, op_brk, am_impl, false, 0, 7},            // BRK

        // JMP Instructions
        {0x4C, op_jmp, am_abs, false, 0, 3},             // JMP Absolute
        {0x6C, op_jmp, am_abs_ind, false, 0, 5},         // JMP Indirect

        {0x20, op_jsr, am_abs, false, 0, 6},             // JSR Absolute

        // Return Instructions
        {0x40, op_rti, am_impl, false, 0, 6},            // RTI
        {0x60, op_rts, am_impl, false, 0, 6},            // RTS

        // Branch Instructions (Variable cycles handled in opcode function)
        {0x90, op_bcc, am_rel, false, 0, 2},             // BCC
        {0xB0, op_bcs, am_rel, false, 0, 2},             // BCS
        {0xF0, op_beq, am_rel, false, 0, 2},             // BEQ
        {0x30, op_bmi, am_rel, false, 0, 2},             // BMI
        {0xD0, op_bne, am_rel, false, 0, 2},             // BNE
        {0x10, op_bpl, am_rel, false, 0, 2},             // BPL
        {0x50, op_bvc, am_rel, false, 0, 2},             // BVC
        {0x70, op_bvs, am_rel, false, 0, 2},             // BVS

        // Flag Instructions
        {0x18, op_clc, am_impl, false, 0, 2},            // CLC
        {0xD8, op_cld, am_impl, false, 0, 2},            // CLD
        {0x58, op_cli, am_impl, false, 0, 2},            // CLI
        {0xB8, op_clv, am_impl, false, 0, 2},            // CLV
        {0x38, op_sec, am_impl, false, 0, 2},            // SEC
        {0xF8, op_sed, am_impl, false, 0, 2},            // SED
        {0x78, op_sei, am_impl, false, 0, 2},            // SEI

        // NOP Instructions (Including Unofficial NOPs)
        {0x1A, nop, am_impl, false, 0, 2},               // NOP
        {0x3A, nop, am_impl, false, 0, 2},               // NOP
        {0x5A, nop, am_impl, false, 0, 2},               // NOP
        {0x7A, nop, am_impl, false, 0, 2},               // NOP
        {0xDA, nop, am_impl, false, 0, 2},               // NOP
        {0xEA, nop, am_impl, false, 0, 2},               // NOP (Official)
        {0xFA, nop, am_impl, false, 0, 2},               // NOP

        {0x80, nop, am_imm, false, 0, 2},                // NOP Immediate
        {0x82, nop, am_imm, false, 0, 2},                // NOP Immediate
        {0x89, nop, am_imm, false, 0, 2},                // NOP Immediate
        {0xC2, nop, am_imm, false, 0, 2},                // NOP Immediate
        {0xE2, nop, am_imm, false, 0, 2},                // NOP Immediate

        {0x0C, nop, am_abs, false, 0, 4},                // NOP Absolute

        // NOP Absolute,X (May add extra cycle if page crossed)
        {0x1C, nop, am_abs_x, true, 0, 4},               // NOP Absolute,X
        {0x3C, nop, am_abs_x, true, 0, 4},               // NOP Absolute,X
        {0x5C, nop, am_abs_x, true, 0, 4},               // NOP Absolute,X
        {0x7C, nop, am_abs_x, true, 0, 4},               // NOP Absolute,X
        {0xDC, nop, am_abs_x, true, 0, 4},               // NOP Absolute,X
        {0xFC, nop, am_abs_x, true, 0, 4},               // NOP Absolute,X

        {0x04, nop, am_zpg, false, 0, 3},                // NOP Zero Page
        {0x44, nop, am_zpg, false, 0, 3},                // NOP Zero Page
        {0x64, nop, am_zpg, false, 0, 3},                // NOP Zero Page

        {0x14, nop, am_zpg_x, false, 0, 4},              // NOP Zero Page,X
        {0x34, nop, am_zpg_x, false, 0, 4},              // NOP Zero Page,X
        {0x54, nop, am_zpg_x, false, 0, 4},              // NOP Zero Page,X
        {0x74, nop, am_zpg_x, false, 0, 4},              // NOP Zero Page,X
        {0xD4, nop, am_zpg_x, false, 0, 4},              // NOP Zero Page,X
        {0xF4, nop, am_zpg_x, false, 0, 4},              // NOP Zero Page,X

        // Unofficial Opcodes (Illegal Instructions)

        // LAS Instruction
        {0xBB, las, am_abs_y, true, 0, 4},               // LAS Absolute,Y

        // LAX Instructions
        {0xAB, lax, am_imm, false, 0, 2},                // LAX Immediate
        {0xAF, lax, am_abs, false, 0, 4},                // LAX Absolute
        {0xBF, lax, am_abs_y, true, 0, 4},               // LAX Absolute,Y
        {0xA7, lax, am_zpg, false, 0, 3},                // LAX Zero Page
        {0xB7, lax, am_zpg_y, false, 0, 4},              // LAX Zero Page,Y
        {0xA3, lax, am_zpg_x_ind, false, 0, 6},          // LAX (Indirect,X)
        {0xB3, lax, am_zpg_ind_y, true, 0, 5},           // LAX (Indirect),Y

        // SAX Instructions
        {0x8F, sax, am_abs, false, 0, 4},                // SAX Absolute
        {0x87, sax, am_zpg, false, 0, 3},                // SAX Zero Page
        {0x97, sax, am_zpg_y, false, 0, 4},              // SAX Zero Page,Y
        {0x83, sax, am_zpg_x_ind, false, 0, 6},          // SAX (Indirect,X)

        // SHA Instructions
        {0x9F, sha, am_abs_y, false, 0, 5},              // SHA Absolute,Y
        {0x93, sha, am_zpg_ind_y, false, 0, 6},          // SHA (Indirect),Y

        // SHX and SHY Instructions
        {0x9E, shx, am_abs_y, false, 0, 5},              // SHX Absolute,Y
        {0x9C, shy, am_abs_x, false, 0, 5},              // SHY Absolute,X

        // SHS Instruction
        {0x9B, shs, am_abs_y, false, 0, 5},              // SHS Absolute,Y

        // ANC Instructions
        {0x0B, anc, am_imm, false, 0, 2},                // ANC Immediate
        {0x2B, anc, am_imm, false, 0, 2},                // ANC Immediate

        // ARR Instructions
        {0x4B, arr, am_imm, false, 0, 2},                // ARR Immediate
        {0x6B, arr, am_imm, false, 0, 2},                // ARR Immediate

        // DCP Instructions
        {0xCF, dcp, am_abs, false, 0, 6},                // DCP Absolute
        {0xDF, dcp, am_abs_x, false, 0, 7},              // DCP Absolute,X
        {0xDB, dcp, am_abs_y, false, 0, 7},              // DCP Absolute,Y
        {0xC7, dcp, am_zpg, false, 0, 5},                // DCP Zero Page
        {0xD7, dcp, am_zpg_x, false, 0, 6},              // DCP Zero Page,X
        {0xC3, dcp, am_zpg_x_ind, false, 0, 8},          // DCP (Indirect,X)
        {0xD3, dcp, am_zpg_ind_y, false, 0, 8},          // DCP (Indirect),Y

        // ISC Instructions
        {0xEF, isc, am_abs, false, 0, 6},                // ISC Absolute
        {0xFF, isc, am_abs_x, false, 0, 7},              // ISC Absolute,X
        {0xFB, isc, am_abs_y, false, 0, 7},              // ISC Absolute,Y
        {0xE7, isc, am_zpg, false, 0, 5},                // ISC Zero Page
        {0xF7, isc, am_zpg_x, false, 0, 6},              // ISC Zero Page,X
        {0xE3, isc, am_zpg_x_ind, false, 0, 8},          // ISC (Indirect,X)
        {0xF3, isc, am_zpg_ind_y, false, 0, 8},          // ISC (Indirect),Y

        // RLA Instructions
        {0x2F, rla, am_abs, false, 0, 6},                // RLA Absolute
        {0x3F, rla, am_abs_x, false, 0, 7},              // RLA Absolute,X
        {0x3B, rla, am_abs_y, false, 0, 7},              // RLA Absolute,Y
        {0x27, rla, am_zpg, false, 0, 5},                // RLA Zero Page
        {0x37, rla, am_zpg_x, false, 0, 6},              // RLA Zero Page,X
        {0x23, rla, am_zpg_x_ind, false, 0, 8},          // RLA (Indirect,X)
        {0x33, rla, am_zpg_ind_y, false, 0, 8},          // RLA (Indirect),Y

        // RRA Instructions
        {0x6F, rra, am_abs, false, 0, 6},                // RRA Absolute
        {0x7F, rra, am_abs_x, false, 0, 7},              // RRA Absolute,X
        {0x7B, rra, am_abs_y, false, 0, 7},              // RRA Absolute,Y
        {0x67, rra, am_zpg, false, 0, 5},                // RRA Zero Page
        {0x77, rra, am_zpg_x, false, 0, 6},              // RRA Zero Page,X
        {0x63, rra, am_zpg_x_ind, false, 0, 8},          // RRA (Indirect,X)
        {0x73, rra, am_zpg_ind_y, false, 0, 8},          // RRA (Indirect),Y

        // SBX Instruction
        {0xCB, sbx, am_imm, false, 0, 2},                // SBX Immediate

        // SLO Instructions
        {0x0F, slo, am_abs, false, 0, 6},                // SLO Absolute
        {0x1F, slo, am_abs_x, false, 0, 7},              // SLO Absolute,X
        {0x1B, slo, am_abs_y, false, 0, 7},              // SLO Absolute,Y
        {0x07, slo, am_zpg, false, 0, 5},                // SLO Zero Page
        {0x17, slo, am_zpg_x, false, 0, 6},              // SLO Zero Page,X
        {0x03, slo, am_zpg_x_ind, false, 0, 8},          // SLO (Indirect,X)
        {0x13, slo, am_zpg_ind_y, false, 0, 8},          // SLO (Indirect),Y

        // SRE Instructions
        {0x4F, sre, am_abs, false, 0, 6},                // SRE Absolute
        {0x5F, sre, am_abs_x, false, 0, 7},              // SRE Absolute,X
        {0x5B, sre, am_abs_y, false, 0, 7},              // SRE Absolute,Y
        {0x47, sre, am_zpg, false, 0, 5},                // SRE Zero Page
        {0x57, sre, am_zpg_x, false, 0, 6},              // SRE Zero Page,X
        {0x43, sre, am_zpg_x_ind, false, 0, 8},          // SRE (Indirect,X)
        {0x53, sre, am_zpg_ind_y, false, 0, 8},          // SRE (Indirect),Y

        // XAA Instruction
        {0x8B, xaa, am_imm, false, 0, 2},                // XAA Immediate

        // KIL Instructions (Halts the CPU)
        {0x02, jam, am_impl, false, 0, 0},               // JAM
        {0x12, jam, am_impl, false, 0, 0},               // JAM
        {0x22, jam, am_impl, false, 0, 0},               // JAM
        {0x32, jam, am_impl, false, 0, 0},               // JAM
        {0x42, jam, am_impl, false, 0, 0},               // JAM
        {0x52, jam, am_impl, false, 0, 0},               // JAM
        {0x62, jam, am_impl, false, 0, 0},               // JAM
        {0x72, jam, am_impl, false, 0, 0},               // JAM
        {0x92, jam, am_impl, false, 0, 0},               // JAM
        {0xB2, jam, am_impl, false, 0, 0},               // JAM
        {0xD2, jam, am_impl, false, 0, 0},               // JAM
        {0xF2, jam, am_impl, false, 0, 0},               // JAM
    };

	size_t num_opcodes = sizeof(opcode_map) / sizeof(opcode_definition);

	for (size_t i = 0; i < num_opcodes; i++) 
	{
		uint8_t opcode = opcode_map[i].opcode;
		_opcode[opcode] = (opcode_definition)
		{
			.instruction = opcode_map[i].instruction,
			.address_mode = opcode_map[i].address_mode,
			.page_cross_toggle = opcode_map[i].page_cross_toggle,
			.mem_type = opcode_map[i].mem_type,
			.cycle = opcode_map[i].cycle
		};
	}
}

void print_opcode_table() {
	printf("Opcode Table:\n");
	printf("Opcode | Instruction | Address Mode | Mem Type | Cycle\n");
	printf("--------------------------------------------------------\n");
	for (size_t i = 0; i < 256; i++) {
		opcode_definition entry = _opcode[i];
		// Check if the opcode is defined
		if (entry.instruction != NULL) {
			printf("  0x%02X  | %p | %p | %d | %d\n",
				(unsigned int)i,
				(void*)entry.instruction,
				(u16*)entry.address_mode,
				entry.mem_type,
				entry.cycle);
		}
	}
}

void nes_log(nes_cpu* cpu, u16 pc, u8 opcode)
{

}

void nes_cpu_run(nes_cpu *cpu)
{
	running = true;
	int i = 0;
	FILE* stream;
	if ((stream = fopen("my_nestest.txt", "w")) == 0)
	{
		fprintf(stderr, "fopen() failed to open: %s\n");
		return;
	}

	size_t sz = 0;
	fseek(stream, 0L, SEEK_END);
	sz = ftell(stream);

	while (i < 9000)
	{
		u16 pc = cpu->program_counter;
		u8 opcode = cpu->memory[cpu->program_counter++];

		printf("%04X ", pc);

		char buf1[1024];
		sprintf(buf1, "%d%d%d%d%d%d%d%d \t\t A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%d\n",
			(cpu->status_flag >> 7) & 1,
			(cpu->status_flag >> 6) & 1,
			(cpu->status_flag >> 5) & 1,
			(cpu->status_flag >> 4) & 1,
			(cpu->status_flag >> 3) & 1,
			(cpu->status_flag >> 2) & 1,
			(cpu->status_flag >> 1) & 1,
			(cpu->status_flag >> 0) & 1,
			cpu->a,
			cpu->x,
			cpu->y,
			cpu->status_flag,
			cpu->stack_pointer,
			cpu->clock_counter);

		opcode_definition entry = _opcode[opcode];
		entry.instruction(cpu, entry.address_mode, entry.page_cross_toggle, entry.mem_type, entry.cycle);

		u16 address = cpu->operands[1] << 8 | cpu->operands[0];

		char buf2[1024];
		sprintf(buf2, "%04X\t %02X %02X %02X %s %04X = %04X \t\t",
			pc, 
			opcode, 
			cpu->operands[0], 
			cpu->operands[1], 
			disassemble_table[opcode].name, 
			address,
			cpu->memory[address]);

		fprintf(stream, "%s", buf2);
		fprintf(stream, "%s", buf1);

		i++;
	}

	fclose(stream);
}

