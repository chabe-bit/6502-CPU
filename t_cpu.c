#include "t_cpu.h"
#include "t_am.h"
#include "t_instr.h"

void nes_init_cpu(nes_cpu* cpu)
{
	cpu->clock_frequency = 1.789773;
	cpu->clock_counter = 0;

	cpu->program_counter = 0xC000;

	cpu->status_flag = 0;

	cpu->interrupt_vector = 0;
	cpu->stack_pointer = 0xFD; // 256 access range

	// thjs is makeshift
	int i = 0;
	while (i < 7)
	{
		cpu->clock_counter++;
		i++;
	}

	cpu->reset = (cpu->memory[0xFFFD] << 8) | cpu->memory[0xFFFC];
	cpu->nmi = (cpu->memory[0xFFFB] << 8) | cpu->memory[0xFFFA];
	cpu->irq = (cpu->memory[0xFFFF] << 8) | cpu->memory[0xFFFE];
}

void nes_init_instructions(nes_cpu* cpu)
{
	for (int i = 0; i < 256; i++) {
		_opcode[i] = (opcode_definition){
			.instruction = NULL,
			.address_mode = NULL,
			.mem_type = 0,
			.cycle = 0
		};
	}

	opcode_definition opcode_map[] = {
		// load
		{0xA9, op_lda, am_imm, 0, 2},
		{0xAD, op_lda, am_abs, 0, 4},
		{0xBD, op_lda, am_abs_x, 0, 4},
		{0xB9, op_lda, am_abs_y, 0, 4},
		{0xA5, op_lda, am_zpg, 0, 3},
		{0xB5, op_lda, am_zpg_x, 0, 4},
		{0xA1, op_lda, am_zpg_y, 0, 6},
		{0xB1, op_lda, am_zpg_ind_y, 0, 5},

		{0xA2, op_ldx, am_imm, 0, 2},
		{0xAE, op_ldx, am_abs, 0, 4},
		{0xBE, op_ldx, am_abs_y, 0, 4},
		{0xA6, op_ldx, am_zpg, 0, 3},
		{0xB6, op_ldx, am_zpg_y, 0, 4},

		{0xA0, op_ldy, am_imm, 0, 2},
		{0xAC, op_ldy, am_abs, 0, 4},
		{0xBC, op_ldy, am_abs_y, 0, 4},
		{0xA4, op_ldy, am_zpg, 0, 3},
		{0xB4, op_ldy, am_zpg_x, 0, 4},

		{0x8D, op_sta, am_abs, 0, 4},
		{0x9D, op_sta, am_abs_x, 0, 5},
		{0x99, op_sta, am_abs_y, 0, 6},
		{0x85, op_sta, am_zpg, 0, 3},
		{0x95, op_sta, am_zpg_x, 0, 4},
		{0x81, op_sta, am_zpg_y, 0, 6},
		{0x91, op_sta, am_zpg_ind_y, 0, 6},

		{0x8E, op_stx, am_abs, 0, 4},
		{0x86, op_stx, am_zpg, 0, 3},
		{0x96, op_stx, am_zpg_y, 0, 4},

		{0x8C, op_sty, am_abs, 0, 4},
		{0x84, op_sty, am_zpg, 0, 3},
		{0x94, op_sty, am_zpg_y, 0, 4},

		// transfer
		{0xAA, op_tax, am_impl, 0, 2},
		{0xA8, op_tay, am_impl, 0, 2},
		{0xBA, op_tsx, am_impl, 0, 2},
		{0x8A, op_txa, am_impl, 0, 2},
		{0x9A, op_txs, am_impl, 0, 2},
		{0x98, op_tya, am_impl, 0, 2},

		// Stack
		{0x48, op_pha, am_impl, 0, 3},
		{0x08, op_php, am_impl, 0, 3},
		{0x68, op_pla, am_impl, 0, 4},
		{0x28, op_plp, am_impl, 0, 4},

		// Shift
		{0x0A, op_asl, am_a, ACCUMULATOR, 2},
		{0x0E, op_asl, am_abs, ABS, 6},
		{0x1E, op_asl, am_abs_x, ABS, 7},
		{0x06, op_asl, am_zpg, ZPG, 5},
		{0x16, op_asl, am_zpg_x, ZPG, 6},

		{0x4A, op_lsr, am_a, ACCUMULATOR, 2},
		{0x4E, op_lsr, am_abs, ABS, 6},
		{0x5E, op_lsr, am_abs_x, ABS, 7},
		{0x46, op_lsr, am_zpg, ZPG, 5},
		{0x56, op_lsr, am_zpg_x, ZPG, 6},

		{0x2A, op_rol, am_a, ACCUMULATOR, 2},
		{0x2E, op_rol, am_abs, ABS, 6},
		{0x3E, op_rol, am_abs_x, ABS, 7},
		{0x26, op_rol, am_zpg, ZPG, 5},
		{0x36, op_rol, am_zpg_x, ZPG, 6},

		{0x6A, op_ror, am_a, ACCUMULATOR, 2},
		{0x6E, op_ror, am_abs, ABS, 6},
		{0x7E, op_ror, am_abs_x, ABS, 7},
		{0x66, op_ror, am_zpg, ZPG, 5},
		{0x76, op_ror, am_zpg_x, ZPG, 6},

		// Logic
		{0x29, op_and, am_imm, IMMEDIATE, 2},
		{0x2D, op_and, am_abs, ABS, 4},
		{0x3D, op_and, am_abs_x, ABS, 5},
		{0x39, op_and, am_abs_y, ABS, 6},
		{0x25, op_and, am_zpg, ZPG, 3},
		{0x35, op_and, am_zpg_x, ZPG, 4},
		{0x21, op_and, am_zpg_y, ZPG, 6},
		{0x31, op_and, am_zpg_ind_y, ZPG, 6},

		{0x2C, op_bit, am_abs, ABS, 4},
		{0x24, op_bit, am_zpg, ZPG, 3},

		{0x49, op_eor, am_imm, 0, 2},
		{0x4D, op_eor, am_abs, 0, 4},
		{0x5D, op_eor, am_abs_x, 0, 4},
		{0x59, op_eor, am_abs_y, 0, 4},
		{0x45, op_eor, am_zpg, 0, 3},
		{0x55, op_eor, am_zpg_x, 0, 4},
		{0x41, op_eor, am_zpg_x_ind, 0, 6},
		{0x51, op_eor, am_zpg_ind_y, 0, 5},

		{0x09, op_ora, am_imm, 0, 2},
		{0x0D, op_ora, am_abs, 0, 4},
		{0x1D, op_ora, am_abs_x, 0, 4},
		{0x19, op_ora, am_abs_y, 0, 4},
		{0x05, op_ora, am_zpg, 0, 3},
		{0x15, op_ora, am_zpg_x, 0, 4},
		{0x01, op_ora, am_zpg_x_ind, 0, 6},
		{0x11, op_ora, am_zpg_ind_y, 0, 5},

		// Arithmetic
		{0x69, op_adc, am_imm, 0, 2},
		{0x6D, op_adc, am_abs, 0, 4},
		{0x7D, op_adc, am_abs_x, 0, 4},
		{0x79, op_adc, am_abs_y, 0, 4},
		{0x65, op_adc, am_zpg, 0, 3},
		{0x75, op_adc, am_zpg_x, 0, 4},
		{0x61, op_adc, am_zpg_x_ind, 0, 6},
		{0x71, op_adc, am_zpg_ind_y, 0, 5},

		{0xC9, op_cmp, am_imm, 0, 2},
		{0xCD, op_cmp, am_abs, 0, 4},
		{0xDD, op_cmp, am_abs_x, 0, 4},
		{0xD9, op_cmp, am_abs_y, 0, 4},
		{0xC5, op_cmp, am_zpg, 0, 3},
		{0xD5, op_cmp, am_zpg_x, 0, 4},
		{0xC1, op_cmp, am_zpg_x_ind, 0, 6},
		{0xD1, op_cmp, am_zpg_ind_y, 0, 5},

		{0xE0, op_cpx, am_imm, 0, 2},
		{0xEC, op_cpx, am_abs, 0, 4},
		{0xE4, op_cpx, am_zpg, 0, 3},

		{0xC0, op_cpy, am_imm, 0, 2},
		{0xCC, op_cpy, am_abs, 0, 4},
		{0xC4, op_cpy, am_zpg, 0, 3},

		{0xE9, op_sbc, am_imm, 0, 2},
		{0xEB, op_sbc, am_imm, 0, 2},
		{0xED, op_sbc, am_abs, 0, 4},
		{0xFD, op_sbc, am_abs_x, 0, 4},
		{0xF9, op_sbc, am_abs_y, 0, 4},
		{0xE5, op_sbc, am_zpg, 0, 3},
		{0xF5, op_sbc, am_zpg_x, 0, 4},
		{0xE1, op_sbc, am_zpg_x_ind, 0, 6},
		{0xF1, op_sbc, am_zpg_ind_y, 0, 5},


		// Increment
		{0xCE, op_dec, am_abs, 0, 6},
		{0xDE, op_dec, am_abs_x, 0, 7},
		{0xC6, op_dec, am_zpg, 0, 5},
		{0xD6, op_dec, am_zpg_x, 0, 6},

		{0xCA, op_dex, am_impl, 0, 2},
		{0x88, op_dey, am_impl, 0, 2},

		{0xEE, op_inc, am_abs, 0, 6},
		{0xFE, op_inc, am_abs_x, 0, 7},
		{0xE6, op_inc, am_zpg, 0, 5},
		{0xF6, op_inc, am_zpg_x, 0, 6},

		{0xE8, op_inx, am_impl, 0, 2},
		{0xC8, op_iny, am_impl, 0, 2},

		// Control 
		{0x00, op_brk, am_impl, 0, 7},

		{0x4C, op_jmp, am_abs, 0, 3},
		{0x6C, op_jmp, am_abs_ind, 0, 5},

		{0x20, op_jsr, am_abs, 0, 6},

		{0x40, op_rti, am_impl, 0, 6},
		{0x60, op_rts, am_impl, 0, 6},

		// Branch
		{0x90, op_bcc, am_rel, 0, 2},
		{0xB0, op_bcs, am_rel, 0, 2},
		{0xF0, op_beq, am_rel, 0, 2},
		{0x30, op_bmi, am_rel, 0, 2},
		{0xD0, op_bne, am_rel, 0, 2},
		{0x10, op_bpl, am_rel, 0, 2},
		{0x50, op_bvc, am_rel, 0, 2},
		{0x70, op_bvs, am_rel, 0, 2},
	
		// Flags
		{0x18, op_clc, am_impl, 0, 2},
		{0xD8, op_cld, am_impl, 0, 2},
		{0x58, op_cli, am_impl, 0, 2},
		{0xB8, op_clv, am_impl, 0, 2},
		{0x38, op_sec, am_impl, 0, 2},
		{0xF8, op_sed, am_impl, 0, 2},
		{0x78, op_sei, am_impl, 0, 2},

		// Nop
		{0x1A, nop, am_impl, 0, 2},
		{0x3A, nop, am_impl, 0, 2},
		{0x5A, nop, am_impl, 0, 2},
		{0x7A, nop, am_impl, 0, 2},
		{0xDA, nop, am_impl, 0, 2},
		{0xEA, nop, am_impl, 0, 2},
		{0xFA, nop, am_impl, 0, 2},
		{0x80, nop, am_imm, 0, 2},
		{0x82, nop, am_imm, 0, 2},
		{0x89, nop, am_imm, 0, 2},
		{0xC2, nop, am_imm, 0, 2},
		{0xE2, nop, am_imm, 0, 2},
		{0x0C, nop, am_abs, 0, 4},
		{0x1C, nop, am_abs_x, 0, 4},
		{0x3C, nop, am_abs_x, 0, 4},
		{0x5C, nop, am_abs_x, 0, 4},
		{0x7C, nop, am_abs_x, 0, 4},
		{0xDC, nop, am_abs_x, 0, 4},
		{0xFC, nop, am_abs_x, 0, 4},
		{0x04, nop, am_zpg, 0, 3},
		{0x44, nop, am_zpg, 0, 3},
		{0x64, nop, am_zpg, 0, 3},
		{0x14, nop, am_zpg_x, 0, 4},
		{0x34, nop, am_zpg_x, 0, 4},
		{0x54, nop, am_zpg_x, 0, 4},
		{0x74, nop, am_zpg_x, 0, 4},
		{0xD4, nop, am_zpg_x, 0, 4},
		{0xF4, nop, am_zpg_x, 0, 4},

		// Illegal
		{0xBB, las, am_abs_y, 0, 4},

		{0xAB, lax, am_imm, 0, 2},
		{0xAF, lax, am_abs, 0, 4},
		{0xBF, lax, am_abs_y, 0, 4},
		{0xA7, lax, am_zpg, 0, 3},
		{0xB7, lax, am_zpg_y, 0, 4},
		{0xA3, lax, am_zpg_x_ind, 0, 6},
		{0xB3, lax, am_zpg_ind_y, 0, 5},

		{0x8F, sax, am_abs, 0, 4},
		{0x87, sax, am_zpg, 0, 3},
		{0x97, sax, am_zpg_y, 0, 4},
		{0x83, sax, am_zpg_x_ind, 0, 6},

		{0x9F, sha, am_abs_y, 0, 5},
		{0x93, sha, am_zpg_ind_y, 0, 6},

		{0x9E, shx, am_abs_x, 0, 5},
		{0x9C, shy, am_abs_y, 0, 5},

		{0x9B, shs, am_abs_y, 0, 5},

		{0x0B, anc, am_imm, 0, 2},
		{0x2B, anc, am_imm, 0, 2},

		{0x4B, arr, am_imm, 0, 2},
		{0x6B, arr, am_imm, 0, 2},

		{0xCF, dcp, am_abs, 0, 6},
		{0xDF, dcp, am_abs_y, 0, 7},
		{0xDB, dcp, am_abs_x, 0, 7},
		{0xC7, dcp, am_zpg, 0, 5},
		{0xD7, dcp, am_zpg_y, 0, 6},
		{0xC3, dcp, am_zpg_x_ind, 0, 8},
		{0xD3, dcp, am_zpg_ind_y, 0, 8},

		{0xEF, isc, am_abs, 0, 6},
		{0xFF, isc, am_abs_y, 0, 7},
		{0xFB, isc, am_abs_x, 0, 7},
		{0xE7, isc, am_zpg, 0, 5},
		{0xF7, isc, am_zpg_y, 0, 6},
		{0xE3, isc, am_zpg_x_ind, 0, 8},
		{0xF3, isc, am_zpg_ind_y, 0, 8},

		{0x2F, rla, am_abs, 0, 6},
		{0x3F, rla, am_abs_y, 0, 7},
		{0x3B, rla, am_abs_x, 0, 7},
		{0x27, rla, am_zpg, 0, 5},
		{0x37, rla, am_zpg_y, 0, 6},
		{0x23, rla, am_zpg_x_ind, 0, 8},
		{0x33, rla, am_zpg_ind_y, 0, 8},

		{0x6F, rra, am_abs, 0, 6},
		{0x7F, rra, am_abs_y, 0, 7},
		{0x7B, rra, am_abs_x, 0, 7},
		{0x67, rra, am_zpg, 0, 5},
		{0x77, rra, am_zpg_y, 0, 6},
		{0x63, rra, am_zpg_x_ind, 0, 8},
		{0x73, rra, am_zpg_ind_y, 0, 8},

		{0xCB, sbx, am_imm, 0, 2},

		{0x0F, slo, am_abs, 0, 6},
		{0x1F, slo, am_abs_y, 0, 7},
		{0x1B, slo, am_abs_x, 0, 7},
		{0x07, slo, am_zpg, 0, 5},
		{0x17, slo, am_zpg_y, 0, 6},
		{0x03, slo, am_zpg_x_ind, 0, 8},
		{0x13, slo, am_zpg_ind_y, 0, 8},

		{0x4F, sre, am_abs, 0, 6},
		{0x5F, sre, am_abs_y, 0, 7},
		{0x5B, sre, am_abs_x, 0, 7},
		{0x47, sre, am_zpg, 0, 5},
		{0x57, sre, am_zpg_y, 0, 6},
		{0x43, sre, am_zpg_x_ind, 0, 8},
		{0x53, sre, am_zpg_ind_y, 0, 8},

		{0x8B, xaa, am_imm, 0, 2},

		// Kill
		{0x02, jam, am_imm, 0, 0},
		{0x12, jam, am_imm, 0, 0},
		{0x22, jam, am_imm, 0, 0},
		{0x32, jam, am_imm, 0, 0},
		{0x42, jam, am_imm, 0, 0},
		{0x52, jam, am_imm, 0, 0},
		{0x62, jam, am_imm, 0, 0},
		{0x72, jam, am_imm, 0, 0},
		{0x82, jam, am_imm, 0, 0},
		{0x92, jam, am_imm, 0, 0},
		{0xB2, jam, am_imm, 0, 0},
		{0xD2, jam, am_imm, 0, 0},
		{0xF2, jam, am_imm, 0, 0},

	};

	size_t num_opcodes = sizeof(opcode_map) / sizeof(opcode_definition);

	for (size_t i = 0; i < num_opcodes; i++) {
		uint8_t opcode = opcode_map[i].opcode;
		_opcode[opcode] = (opcode_definition){
			.instruction = opcode_map[i].instruction,
			.address_mode = opcode_map[i].address_mode,
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

void nes_log(nes_cpu *cpu, u16 pc, u8 opcode)
{
	FILE* stream;
	if ((stream = fopen("my_nestest.txt", "w")) == 0)
	{
		fprintf(stderr, "fopen() failed to open: %s\n");
		return;
	}

	char buf[1024];
	sprintf(buf, "%04X\t %02X %02X %02X %02X %04X\t \t\t A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%d\n",
		pc, opcode, cpu->operands[0], cpu->operands[1], opcode, (cpu->operands[1] << 8) | cpu->operands[0],
		cpu->a, cpu->x, cpu->y, cpu->status_flag, cpu->stack_pointer, cpu->clock_counter);

	fprintf(stream, "%s", buf);


	printf("%04X \t", pc);
	printf("%02X ", opcode);

	printf("%02X ", cpu->operands[0]);
	printf("%02X ", cpu->operands[1]);

	printf("%02X ", opcode);
	printf("%04X\t", (cpu->operands[1] << 8) | cpu->operands[0]);

	printf("\t\t");

	printf("A:%02X ", cpu->a);
	printf("X:%02X ", cpu->x);
	printf("Y:%02X ", cpu->y);
	printf("P:%02X ", cpu->status_flag);

	printf("SP:%02X ", cpu->stack_pointer);

	printf("CYC:%d\n", cpu->clock_counter);


	fclose(stream);
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
	while (i < 100)
	{
		// fetch
		u16 pc = cpu->program_counter;
		//printf("pc: 0x%04X\n", pc);

		u8 opcode = cpu->memory[cpu->program_counter++];
		//printf("fetched: 0x%X\n", opcode);
		//printf("clock cycle: %d\n", cpu->clock_counter);
		//nes_log(cpu, pc, opcode);

		opcode_definition entry = _opcode[opcode];
		entry.instruction(cpu, entry.address_mode, entry.mem_type, entry.cycle);

		char buf[1024];
		sprintf(buf, "%04X\t %02X %02X %02X NAME %04X\t \t\t A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%d\n",
			pc, opcode, cpu->operands[0], cpu->operands[1], (cpu->operands[1] << 8) | cpu->operands[0],
			cpu->a, cpu->x, cpu->y, cpu->status_flag, cpu->stack_pointer, cpu->clock_counter);

		fprintf(stream, "%s", buf);
		i++;
	}
	fclose(stream);

}