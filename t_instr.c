#include "t_instr.h"

void op_lda(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("lda_");

	u16 address = address_mode(cpu);
	cpu->a = cpu->memory[address];

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if (cpu->a & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	cpu->clock_counter += cycle;
}

void op_ldx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("ldx_");

	u16 address = address_mode(cpu);
	cpu->x = cpu->memory[address];

	if (cpu->x == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if (cpu->x & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	cpu->clock_counter += cycle;
}

void op_ldy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("ldy_");

	u16 address = address_mode(cpu);
	cpu->y = cpu->memory[address];

	if (cpu->y == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if (cpu->y & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	cpu->clock_counter += cycle;
}

void op_sta(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("sta_");

	u16 address = address_mode(cpu);
	cpu->memory[address] = cpu->a;

	cpu->clock_counter += cycle;
}

void op_stx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("stx_");

	u16 address = address_mode(cpu);
	cpu->memory[address] = cpu->x;

	cpu->clock_counter += cycle;
}

void op_sty(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("sty_");

	u16 address = address_mode(cpu);
	cpu->memory[address] = cpu->y;

	cpu->clock_counter += cycle;
}

void op_tax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("tax_");
	u8 am = address_mode(cpu);

	cpu->x = cpu->a;

	if (cpu->x & FLAG_NEGATIVE)
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

	if (cpu->y & FLAG_NEGATIVE)
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

	if (cpu->x & FLAG_NEGATIVE)
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

	if (cpu->a & FLAG_NEGATIVE)
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

	if (cpu->a & FLAG_NEGATIVE)
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

	// Plus 0x10 to the memory location, 0x10 is the size per mem location, so we're adding to move on to the next
	u8 value = pull_stack(cpu);

	cpu->a = value;
	printf("pla pull value: %02X\n", cpu->a);

	if (cpu->a & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->a == 0)
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

	// preserve bits 
	u8 ignore_bits = FLAG_UNUSED | FLAG_BREAK;

	// ignore bit 5 and the break flag
	cpu->status_flag = (cpu->status_flag & ignore_bits) | (value & ~ignore_bits);

	// next time to ignore said bits:
	// first select those flags, 
	// second turn those flags on in the current status flag 
	// third turn them off in the value pulled flag.
	// then store back into sf.

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
		input_bit = cpu->a & FLAG_NEGATIVE;
		shift = cpu->a << 1;
		cpu->a = shift;
	}
	else if (mem_type == ZPG)
	{
		input_bit = cpu->memory[zpg_addr] & FLAG_NEGATIVE;
		shift = cpu->memory[zpg_addr] << 1;
		cpu->memory[zpg_addr] = shift;
	}
	else if (mem_type == ABS)
	{
		input_bit = cpu->memory[mem_addr] & FLAG_NEGATIVE;
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

	if (shift & FLAG_NEGATIVE)
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
		input_bit = cpu->a & FLAG_NEGATIVE;
		shift = cpu->a << 1;
		cpu->a = shift;
	}
	else if (mem_type == ZPG)
	{
		input_bit = cpu->memory[zpg_addr] & FLAG_NEGATIVE;
		shift = cpu->memory[zpg_addr] << 1;
		cpu->memory[zpg_addr] = shift;
	}
	else if (mem_type == ABS)
	{
		input_bit = cpu->memory[mem_addr] & FLAG_NEGATIVE;
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

	if (shift & FLAG_NEGATIVE)
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
		input_bit = cpu->a & FLAG_NEGATIVE;
		rotate = cpu->a << 1;
		cpu->a = rotate;
	}
	else if (mem_type == ZPG)
	{
		input_bit = cpu->memory[zpg_addr] & FLAG_NEGATIVE;
		rotate = cpu->memory[zpg_addr] << 1;
		cpu->memory[zpg_addr] = rotate;
	}
	else if (mem_type == ABS)
	{
		input_bit = cpu->memory[mem_addr] & FLAG_NEGATIVE;
		rotate = cpu->memory[mem_addr] << 1;
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

	if (rotate & FLAG_NEGATIVE)
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
	u8 input_bit = cpu->a & FLAG_CARRY;
	u8 carry = (cpu->status_flag >> FLAG_CARRY) & 1;
	u8 rotate = (cpu->a >> 1) | (carry << 7);

	cpu->a = rotate;

	if (input_bit)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (rotate & FLAG_NEGATIVE)
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
	
	u8 input_bit = cpu->memory[address] & FLAG_CARRY;
	u8 carry = (cpu->status_flag >> FLAG_CARRY) & 1;
	u8 rotate = (cpu->memory[address] >> 1) | (carry << 7);

	cpu->memory[address] = rotate;
	
	if (input_bit)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (rotate & FLAG_NEGATIVE)
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

	printf("and_result: %02X\n", result);

	cpu->a = result;

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if (cpu->a & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;


	cpu->clock_counter += cycle;
}

void op_bit(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bit_");

	u16 addr;
	u8 result;
	if (mem_type == ZPG)
	{
		addr = cpu->memory[(u8)address_mode(cpu)];
		result = cpu->a & addr;
	}
	else if (mem_type == ABS)
	{
		addr = cpu->memory[address_mode(cpu)];
		result = cpu->a & addr;
	}
	else
	{
		fprintf(stderr, "Invalid address mode: %d\n", mem_type);
		return;
	}

	view_status_flag(result);

	if (result == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if (addr & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (addr & FLAG_OVERFLOW)
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;


	cpu->clock_counter += cycle;

}

void op_eor(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu);
	u8 result = cpu->a ^ cpu->memory[address];
	cpu->a = result;

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if (cpu->a & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;


	cpu->clock_counter += cycle;
}

void op_ora(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("ora_");

	u16 address = address_mode(cpu);
	u8 result = cpu->a | cpu->memory[address];
	cpu->a = result;

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if (cpu->a & FLAG_NEGATIVE)
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


	if (cpu->a > 0xFF)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	u8 sign_check = (a ^ cpu->a) & (m ^ cpu->a);
	if (sign_check & FLAG_OVERFLOW)
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;

	if (cpu->a & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->a == 0)
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

	if (m <= a)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (result == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if (result & FLAG_NEGATIVE)
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

	if (result & FLAG_NEGATIVE)
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

	if (result & FLAG_NEGATIVE)
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
	cpu->a = result;

	if (result >= 0)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	u8 sign_check = (a ^ cpu->a) & (m ^ cpu->a);
	if (sign_check & FLAG_OVERFLOW)
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;

	if (result & FLAG_NEGATIVE)
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

	if (m & FLAG_NEGATIVE)
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

	if (x & FLAG_NEGATIVE)
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

	if (y & FLAG_NEGATIVE)
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

	if (m & FLAG_NEGATIVE)
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

	if (x & FLAG_NEGATIVE)
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

	if (y & FLAG_NEGATIVE)
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

	printf("brk PC: 0x%04X\n", cpu->program_counter);

	cpu->clock_counter += cycle;
}

void op_jmp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("jmp_");

	u16 target_address = address_mode(cpu);

	cpu->program_counter = target_address;
	printf("Jumped to: 0x%04X\n", cpu->program_counter);

	cpu->clock_counter += cycle;
}

void op_jsr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("jsr_");

	u16 target_address = address_mode(cpu);
	u16 return_address = cpu->program_counter - 1;

	push_stack(cpu, (return_address >> 8) & 0xFF); // hi
	push_stack(cpu, return_address & 0xFF); // lo

	printf("JSR return_address: 0x%X\n", return_address);

	cpu->program_counter = target_address;

	cpu->clock_counter += cycle;
}

void op_rti(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("rti_");

	cpu->status_flag = pull_stack(cpu);

	u8 lo = pull_stack(cpu);
	u8 hi = pull_stack(cpu);
	u16 addr = (hi << 8) | lo;

	cpu->program_counter = addr;

	cpu->clock_counter += cycle;
}

void op_rts(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("rts_");

	u8 lo = pull_stack(cpu);
	u8 hi = pull_stack(cpu);

	u16 return_address = (hi << 8) | lo;
	return_address += 1;

	printf("return_address: 0x%X\n", return_address);
	cpu->program_counter = return_address;

	cpu->clock_counter += cycle;
}

void op_bcc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*), int mem_type, u8 cycle)
{
	printf("bcc_");

	i8 signed_offset = (i8)address_mode(cpu);
	
	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;
	
	printf("bcc target_add: 0x%X\n", target_address);

	// branch taken is setting a new address to the pc, +1 clock
	if (!(cpu->status_flag & FLAG_CARRY))
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

	printf("bcs target_add: 0x%X\n", target_address);

	// branch taken is setting a new address to the pc, +1 clock
	if (cpu->status_flag & FLAG_CARRY)
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

	printf("beq target_add: 0x%X\n", target_address);

	// branch taken is setting a new address to the pc, +1 clock
	if (cpu->status_flag & FLAG_ZERO)
	{
		printf("BEQ branched\n");

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

	printf("bmi target_add: 0x%X\n", target_address);

	// branch taken is setting a new address to the pc, +1 clock
	if (cpu->status_flag & FLAG_NEGATIVE)
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

	printf("bne target_add: 0x%X\n", target_address);

	// branch taken is setting a new address to the pc, +1 clock
	if (!(cpu->status_flag & FLAG_ZERO))
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

	printf("bpl target_add: 0x%X\n", target_address);

	// branch taken is setting a new address to the pc, +1 clock
	if (!(cpu->status_flag & FLAG_NEGATIVE))
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

	printf("bvc target_add: 0x%X\n", target_address);

	// branch taken is setting a new address to the pc, +1 clock
	if (!(cpu->status_flag & FLAG_OVERFLOW))
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

	(cpu, signed_offset, 0);
	printf("bvs current_add: 0x%X\n", current_address);
	printf("bvs target_add: 0x%X\n", target_address);

	// branch taken is setting a new address to the pc, +1 clock
	if (cpu->status_flag & FLAG_OVERFLOW)
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
 


