#include "t_instr.h"

void op_lda(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("lda_");

	u8 address = address_mode(cpu) & 0xFF;
	cpu->a = address;

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((cpu->a >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	cpu->clock_counter += cycle;
}

void op_ldx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("ldx_");

	u8 address = address_mode(cpu) & 0xFF;
	cpu->x = address;

	if (cpu->x == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((cpu->x >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	cpu->clock_counter += cycle;
}

void op_ldy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("ldy_");

	u8 address = address_mode(cpu) & 0xFF;
	cpu->y = address;

	if (cpu->y == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((cpu->y >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	cpu->clock_counter += cycle;
}

void op_sta(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("sta_");

	u8 address = address_mode(cpu) & 0xFF;
	cpu->memory[address] = cpu->a;

	cpu->clock_counter += cycle;
}

void op_stx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("stx_");

	u8 address = address_mode(cpu) & 0xFF;
	cpu->memory[address] = cpu->x;

	cpu->clock_counter += cycle;
}

void op_sty(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("sty_");

	u8 address = address_mode(cpu) & 0xFF;
	cpu->memory[address] = cpu->y;

	cpu->clock_counter += cycle;
}

void op_tax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("tax_");
	u8 am = address_mode(cpu);

	cpu->x = cpu->a;

	if ((cpu->x >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->x == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_tay(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("tay_");
	u8 am = address_mode(cpu);

	cpu->y = cpu->a;

	if ((cpu->y >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->y == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_tsx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("tsx_");
	u8 am = address_mode(cpu);

	cpu->x = cpu->stack_pointer;

	if ((cpu->x >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->x == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;


	cpu->clock_counter += cycle;
}

void op_txa(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("txa_");
	u8 am = address_mode(cpu);

	cpu->a = cpu->x;

	if ((cpu->a >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_txs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("txs_");
	u8 am = address_mode(cpu);

	cpu->stack_pointer = cpu->x;

	cpu->clock_counter += cycle;
}

void op_tya(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("tya_");
	u8 am = address_mode(cpu);

	cpu->a = cpu->y;

	if ((cpu->a >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_pha(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("pha_");
	u8 am = address_mode(cpu);

	push_stack(cpu, cpu->a);
	cpu->clock_counter += cycle;
}

void op_php(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("php_");
	u8 am = address_mode(cpu);

	push_stack(cpu, cpu->status_flag);
	cpu->clock_counter += cycle;
}

void op_pla(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("pla_");
	u8 am = address_mode(cpu);

	u8 value = pull_stack(cpu);
	cpu->a = value;

	if ((value >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (value == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_plp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("plp_");
	u8 am = address_mode(cpu);

	u8 value = pull_stack(cpu);
	cpu->status_flag = value;

	// N
	if ((value >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;
	
	// V
	if ((value ^ cpu->status_flag) == 1)
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;

	// I 
	if (cpu->interrupt_vector)
		cpu->status_flag |= FLAG_INTERRUPT;
	else
		cpu->status_flag &= ~FLAG_INTERRUPT;

	// Z
	if (value == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	// C
	if (value)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	cpu->clock_counter += cycle;
}

void op_asl(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("asl_");

	// 64kb memory address or Zero page address
	u16 mem_addr = address_mode(cpu);
	u8 zpg_addr = mem_addr & 0xFF;

	u8 shift;
	u8 input_bit;
	if (mem_type == ACCUMULATOR)
	{
		input_bit = (cpu->a >> 7) & 1;
		shift = cpu->a << 1;
		cpu->a = shift;
	}
	else if (mem_type == ZPG)
	{
		input_bit = (cpu->memory[zpg_addr] >> 7) & 1;
		shift = cpu->memory[zpg_addr] << 1;
		cpu->memory[zpg_addr] = shift;
	}
	else if (mem_type == ABS)
	{
		input_bit = (cpu->memory[mem_addr] >> 7) & 1;
		shift = cpu->memory[mem_addr] << 1;
		cpu->memory[mem_addr] = shift;
	}
	else
	{
		fprintf(stderr, "Invalid address mode: %d\n", mem_type);
		return;
	}
	
	if (input_bit)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if ((shift >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (shift == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_lsr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("lsr_");

	// 64kb memory address or Zero page address
	u16 mem_addr = address_mode(cpu);
	u8 zpg_addr = mem_addr & 0xFF;

	u8 shift;
	u8 input_bit;
	if (mem_type == ACCUMULATOR)
	{
		input_bit = (cpu->a >> 7) & 1;
		shift = cpu->a >> 1;
		cpu->a = shift;
	}
	else if (mem_type == ZPG)
	{
		input_bit = (cpu->memory[zpg_addr] >> 7) & 1;
		shift = cpu->memory[zpg_addr] >> 1;
		cpu->memory[zpg_addr] = shift;
	}
	else if (mem_type == ABS)
	{
		input_bit = (cpu->memory[mem_addr] >> 7) & 1;
		shift = cpu->memory[mem_addr] >> 1;
		cpu->memory[mem_addr] = shift;
	}
	else
	{
		fprintf(stderr, "Invalid address mode: %d\n", mem_type);
		return;
	}

	if (input_bit)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if ((shift >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (shift == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

// (TODO): Come back and redo the rotate instructions
void op_rol(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("rol_");

	// 64kb memory address or Zero page address
	u16 mem_addr = address_mode(cpu);
	u8 zpg_addr = mem_addr & 0xFF;

	u8 rotate;
	u8 input_bit;
	u8 carry = (cpu->status_flag >> FLAG_CARRY) & 1;

	if (mem_type == ACCUMULATOR)
	{
		input_bit = (cpu->a >> 7) & 1;
		rotate = (cpu->a << 1) | carry;
		cpu->a = rotate;
	}
	else if (mem_type == ZPG)
	{
		input_bit = (cpu->memory[zpg_addr] >> 7) & 1;
		rotate = (cpu->memory[zpg_addr] << 1) | carry;
		cpu->memory[zpg_addr] = rotate;
	}
	else if (mem_type == ABS)
	{
		input_bit = (cpu->memory[mem_addr] >> 7) & 1;
		rotate = (cpu->memory[mem_addr] << 1) | carry;
		cpu->memory[mem_addr] = rotate;
	}
	else
	{
		fprintf(stderr, "Invalid address mode: %d\n", mem_type);
		return;
	}

	if (input_bit)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if ((rotate >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (rotate == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

// (TODO): Come back and redo the rotate instructions
void op_ror_a(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("ror_a_");

	// 64kb memory address or Zero page address
	u8 input_bit = (cpu->a >> 0) & 1;
	u8 carry = (cpu->status_flag >> FLAG_CARRY) & 1;
	u8 rotate = (cpu->a >> 1) | (carry << 7);

	cpu->a = rotate;

	if (input_bit)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if ((rotate >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (rotate == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_ror(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("ror_");

	// 64kb memory address or Zero page address
	u16 address = address_mode(cpu);
	
	u8 input_bit = (cpu->memory[address] >> 0) & 1;
	u8 carry = (cpu->status_flag >> FLAG_CARRY) & 1;
	u8 rotate = (cpu->memory[address] >> 1) | (carry << 7);

	cpu->memory[address] = rotate;
	
	if (input_bit)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if ((rotate >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (rotate == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_and(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("and_");

	u8 result = cpu->a & cpu->memory[address_mode(cpu)];
	cpu->a = result;

	if (result == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((result >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;


	cpu->clock_counter += cycle;
}

void op_bit(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bit_");

	u8 result;
	if (mem_type == ZPG)
	{
		u8 zpg_addr = address_mode(cpu);
		result = cpu->a & cpu->memory[zpg_addr];
	}
	else if (mem_type == ABS)
	{
		u16 full_addr = address_mode(cpu);
		result = cpu->a & cpu->memory[full_addr];
	}
	else
	{
		fprintf(stderr, "Invalid address mode: %d\n", mem_type);
		return;
	}

	if (result == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((result >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if ((result >> 6) == 1)
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;


	cpu->clock_counter += cycle;

}

void op_eor(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 address = address_mode(cpu);
	u8 result = cpu->a ^ cpu->memory[address];
	cpu->a = result;

	if (result == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((result >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;


	cpu->clock_counter += cycle;
}

void op_ora(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("ora_");

	u8 address = address_mode(cpu);
	u8 result = cpu->a | cpu->memory[address];
	cpu->a = result;

	if (result == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((result >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;


	cpu->clock_counter += cycle;
}

void op_adc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("adc_");

	u8 a = cpu->a;
	u8 m = cpu->memory[address_mode(cpu)];
	u8 c = cpu->status_flag & 1;

	u8 result = a + m + c;

	cpu->a = result;

	if (result > 0xFF)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (((a ^ result) & (m ^ result) >> 7) == 1)
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;

	if ((result >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (result == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;


	cpu->clock_counter += cycle;
}

void op_cmp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("cmp_");

	u8 a = cpu->a;
	u8 m = cpu->memory[address_mode(cpu)];

	u8 result = m - a;

	if (m < a)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (cpu->a == result)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((result >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;


	cpu->clock_counter += cycle;
}

void op_cpx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("cpx_");

	u8 x = cpu->x;
	u8 m = cpu->memory[address_mode(cpu)];

	u8 result = x - m;

	if (x >= m)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (x == m)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((result >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;


	cpu->clock_counter += cycle;
}

void op_cpy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("cpy_");

	u8 y = cpu->y;
	u8 m = cpu->memory[address_mode(cpu)];

	u8 result = y - m;

	if (y >= m)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (y == m)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if ((result >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;


	cpu->clock_counter += cycle;
}

void op_sbc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("sbc_");

	u8 a = cpu->a;
	u8 m = cpu->memory[address_mode(cpu)];
	u8 carry = cpu->status_flag & 1;

	// 1 - carry -> 1 - (0) =  1 OR 
	// 1 - carry -> 1 - (1) = -1
	u8 result = a - m - (1 - carry);

	if (result >= 0)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (((a ^ result) & (m ^ result) >> 7) == 1)
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;

	if ((result >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (result == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;


	cpu->clock_counter += cycle;
}

void op_dec(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("dec_");

	u8 m = cpu->memory[address_mode(cpu)] - 1;
	cpu->memory[address_mode(cpu)] = m;

	if ((m >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (m == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_dex(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("dex_");
	u8 am = address_mode(cpu);

	u8 x = cpu->x - 1;
	cpu->x = x;

	if ((x >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (x == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_dey(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("dey_");
	u8 am = address_mode(cpu);

	u8 y = cpu->y - 1;
	cpu->y = y;

	if ((y >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (y == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_inc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("inc_");

	u8 m = cpu->memory[address_mode(cpu)] + 1;
	cpu->memory[address_mode(cpu)] = m;

	if ((m >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (m == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_inx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("inx_");
	u8 am = address_mode(cpu);

	u8 x = cpu->x + 1;
	cpu->x = x;

	if ((x >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (x == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_iny(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("iny_");
	u8 am = address_mode(cpu);

	u8 y = cpu->y + 1;
	cpu->y = y;

	if ((y >> 7) == 1)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (y == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_brk(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("brk_");

	// There's a pause that happens and we're saving the state by storing it into the stack

	// The opcode that comes after the brk is stored into the stack
	cpu->program_counter += 2;

	// Pushes the pc location
	push_stack(cpu, cpu->program_counter & 0xFF); // Grab the lo bits
	push_stack(cpu, (cpu->program_counter >> 8) & 0xFF); // Grab the hi bits and drop the rest

	// Pushes the break flag
	u8 status = cpu->status_flag | FLAG_BREAK;
	push_stack(cpu, status);

	// Set the interrupt flag
	cpu->status_flag |= FLAG_INTERRUPT; 

	cpu->interrupt_vector = (cpu->memory[BRK] << 8) | cpu->memory[IRQ];
	cpu->program_counter = cpu->interrupt_vector;

	view_status_flag(cpu->status_flag);
	printf("brk PC: 0x%04X\n", cpu->program_counter);

	cpu->clock_counter += cycle;
}

void op_jmp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u16 target_address = address_mode(cpu);

	cpu->program_counter = target_address;
	printf("Jumped to: 0x%04X\n", cpu->program_counter);

	cpu->clock_counter += cycle;
}

void op_jsr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("jsr_");

	u16 target_address = address_mode(cpu);

	u16 return_address = cpu->memory[cpu->program_counter] - 1;
	push_stack(cpu, return_address & 0xFF); // lo
	push_stack(cpu, (return_address >> 8) & 0xFF); // hi

	cpu->program_counter = target_address;

	cpu->clock_counter += cycle;
}

u8 pull_pc(nes_cpu *cpu, u8 addr)
{
	if (cpu->stack_pointer == 0xFF)
	{
		fprintf(stderr, "Stack is empty, cannot pull: 0x%02X off the stack.\n");
		return -1;
	}

	cpu->stack_pointer++;

	u8 value = cpu->memory[addr];


	printf("Pull from stack: 0x%04X\n", value);
	return value;
}

void op_rti(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("rti_");

	// target the instruction that was interrupted and return to it
	cpu->status_flag = pull_stack(cpu);

	u8 lo = pull_stack(cpu);
	u8 hi = pull_stack(cpu);
	u16 addr = (hi << 8) | lo;

	cpu->program_counter = addr;

	cpu->clock_counter += cycle;
}

void op_rts(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 lo = pull_stack(cpu);
	u8 hi = pull_stack(cpu);
	//u8 lo = cpu->program_counter & 0xFF;
	//u8 hi = (cpu->program_counter >> 8) & 0xFF;
	u16 addr = (hi << 8) | lo;

	//addr += 1;

	printf("return_address: %04X\n", addr);
	cpu->program_counter++;
	cpu->program_counter = addr;

	printf("rts_");
	cpu->clock_counter += cycle;
}

void op_bcc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bcc_");

	i8 signed_offset = (i8)address_mode(cpu);
	
	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;
	
	push_operand(cpu, target_address & 0xFF, (target_address >> 8) & 0xFF);

	printf("target_add: 0x%X\n", target_address);

	// branch taken is setting a new address to the pc, +1 clock
	if ((cpu->status_flag & FLAG_CARRY) == 0)
	{
		cpu->clock_counter += 1;
		
		// page crossed is to check if there was a carry from lo to hi byte, +1 clock
		if ((current_address & 0xFF00) != (target_address & 0xFF00))
		{
			cpu->clock_counter += 1;
		}
		cpu->program_counter = target_address;
	}

	cpu->clock_counter += cycle;
}

void op_bcs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bcs_");

	i8 signed_offset = (i8)address_mode(cpu);

	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;
	push_operand(cpu, target_address & 0xFF, (target_address >> 8) & 0xFF);

	// branch taken is setting a new address to the pc, +1 clock
	if ((cpu->status_flag & FLAG_CARRY) == 1)
	{
		cpu->clock_counter += 1;

		// page crossed is to check if there was a carry from lo to hi byte, +1 clock
		if ((current_address & 0xFF00) != (target_address & 0xFF00))
		{
			cpu->clock_counter += 1;
		}
		cpu->program_counter = target_address;
	}

	cpu->clock_counter += cycle;
}

void op_beq(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("beq_");

	i8 signed_offset = (i8)address_mode(cpu);

	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;
	push_operand(cpu, target_address & 0xFF, (target_address >> 8) & 0xFF);

	// branch taken is setting a new address to the pc, +1 clock
	if ((cpu->status_flag & FLAG_ZERO) == 1)
	{
		cpu->clock_counter += 1;

		// page crossed is to check if there was a carry from lo to hi byte, +1 clock
		if ((current_address & 0xFF00) != (target_address & 0xFF00))
		{
			cpu->clock_counter += 1;
		}
		cpu->program_counter = target_address;
	}

	cpu->clock_counter += cycle;
}

void op_bmi(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bmi_");

	i8 signed_offset = (i8)address_mode(cpu);

	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;
	push_operand(cpu, target_address & 0xFF, (target_address >> 8) & 0xFF);

	// branch taken is setting a new address to the pc, +1 clock
	if ((cpu->status_flag & FLAG_NEGATIVE) == 1)
	{
		cpu->clock_counter += 1;

		// page crossed is to check if there was a carry from lo to hi byte, +1 clock
		if ((current_address & 0xFF00) != (target_address & 0xFF00))
		{
			cpu->clock_counter += 1;
		}
		cpu->program_counter = target_address;
	}

	cpu->clock_counter += cycle;
}

void op_bne(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bne_");

	i8 signed_offset = (i8)address_mode(cpu);

	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;
	push_operand(cpu, target_address & 0xFF, (target_address >> 8) & 0xFF);

	// branch taken is setting a new address to the pc, +1 clock
	if ((cpu->status_flag & FLAG_ZERO) == 0)
	{
		cpu->clock_counter += 1;

		// page crossed is to check if there was a carry from lo to hi byte, +1 clock
		if ((current_address & 0xFF00) != (target_address & 0xFF00))
		{
			cpu->clock_counter += 1;
		}
		cpu->program_counter = target_address;
	}

	cpu->clock_counter += cycle;
}

void op_bpl(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bpl_");

	i8 signed_offset = (i8)address_mode(cpu);

	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;
	push_operand(cpu, target_address & 0xFF, (target_address >> 8) & 0xFF);

	// branch taken is setting a new address to the pc, +1 clock
	if ((cpu->status_flag & FLAG_NEGATIVE) == 0)
	{
		cpu->clock_counter += 1;

		// page crossed is to check if there was a carry from lo to hi byte, +1 clock
		if ((current_address & 0xFF00) != (target_address & 0xFF00))
		{
			cpu->clock_counter += 1;
		}
		cpu->program_counter = target_address;
	}

	cpu->clock_counter += cycle;
}

void op_bvc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bvc_");

	i8 signed_offset = (i8)address_mode(cpu);

	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;
	push_operand(cpu, target_address & 0xFF, (target_address >> 8) & 0xFF);

	// branch taken is setting a new address to the pc, +1 clock
	if ((cpu->status_flag & FLAG_OVERFLOW) == 0)
	{
		cpu->clock_counter += 1;

		// page crossed is to check if there was a carry from lo to hi byte, +1 clock
		if ((current_address & 0xFF00) != (target_address & 0xFF00))
		{
			cpu->clock_counter += 1;
		}
		cpu->program_counter = target_address;
	}

	cpu->clock_counter += cycle;
}

void op_bvs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bvs_");

	i8 signed_offset = (i8)address_mode(cpu);

	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;
	push_operand(cpu, target_address & 0xFF, (target_address >> 8) & 0xFF);

	// branch taken is setting a new address to the pc, +1 clock
	if ((cpu->status_flag & FLAG_OVERFLOW) == 1)
	{
		cpu->clock_counter += 1;

		// page crossed is to check if there was a carry from lo to hi byte, +1 clock
		if ((current_address & 0xFF00) != (target_address & 0xFF00))
		{
			cpu->clock_counter += 1;
		}
		cpu->program_counter = target_address;
	}

	cpu->clock_counter += cycle;
}

void op_clc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("clc_");
	u8 am = address_mode(cpu);

	cpu->status_flag &= ~FLAG_CARRY;

	cpu->clock_counter += cycle;
}

void op_cld(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("cld_");
	u8 am = address_mode(cpu);

	cpu->status_flag &= ~FLAG_DECIMAL;

	cpu->clock_counter += cycle;
}

void op_cli(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("cli_");
	u8 am = address_mode(cpu);

	cpu->status_flag &= ~FLAG_INTERRUPT;

	cpu->clock_counter += cycle;
}

void op_clv(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("clv_");
	u8 am = address_mode(cpu);

	cpu->status_flag &= ~FLAG_OVERFLOW;

	cpu->clock_counter += cycle;
}

void op_sec(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("sec_");
	u8 am = address_mode(cpu);

	cpu->status_flag |= FLAG_CARRY;

	cpu->clock_counter += cycle;
}

void op_sed(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("sed_");
	u8 am = address_mode(cpu);

	cpu->status_flag |= FLAG_DECIMAL;

	cpu->clock_counter += cycle;
}


void op_sei(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("sei_");
	u8 am = address_mode(cpu);

	cpu->status_flag |= FLAG_INTERRUPT;

	cpu->clock_counter += cycle;
}

void nop(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("nop_");

	u8 address = address_mode(cpu);

	cpu->clock_counter += cycle;
}

void jam(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("jam_");
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void slo(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("slo_");
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void anc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	cpu->clock_counter += cycle;

}

void alr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void arr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void asr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void rla(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void sax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void dcp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void isc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void usbc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void las(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void lax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void lxa(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void sha(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void shx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	cpu->clock_counter += cycle;

}

void shy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void shs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void sre(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	cpu->clock_counter += cycle;

}

void xaa(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void rra(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}

void sbx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{	u8 am = address_mode(cpu);

	cpu->clock_counter += cycle;

}
 


