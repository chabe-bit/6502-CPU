#include "t_instr.h"

void t_op_lda(nes_cpu* cpu, am_t mode, u8 cycle)
{
	printf("lda_");

	cpu->a = cpu->memory[mode.address];

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

////////////////////////////////////////////////////////////////////////////////


void op_lda(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("lda_");

	u16 address = address_mode(cpu, page_cross_toggle);
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

void op_ldx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("ldx_");

	u16 address = address_mode(cpu, page_cross_toggle);
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

void op_ldy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("ldy_");

	u16 address = address_mode(cpu, page_cross_toggle);
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

void op_sta(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("sta_");

	u16 address = address_mode(cpu, page_cross_toggle);
	cpu->memory[address] = cpu->a;

	cpu->clock_counter += cycle;
}

void op_stx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("stx_");

	u16 address = address_mode(cpu, page_cross_toggle);
	cpu->memory[address] = cpu->x;

	cpu->clock_counter += cycle;
}

void op_sty(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("sty_");

	u16 address = address_mode(cpu, page_cross_toggle);
	cpu->memory[address] = cpu->y;

	cpu->clock_counter += cycle;
}

void op_tax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("tax_");

	cpu->x = cpu->a;

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

void op_tay(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("tay_");

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

void op_tsx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("tsx_");

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

void op_txa(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("txa_");

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

void op_txs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("txs_");

	cpu->stack_pointer = cpu->x;

	cpu->clock_counter += cycle;
}

void op_tya(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("tya_");

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

void op_pha(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("pha_");

	push_stack(cpu, cpu->a);
	cpu->clock_counter += cycle;
}

void op_php(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("php_");

	push_stack(cpu, cpu->status_flag);
	cpu->clock_counter += cycle;
}

void op_pla(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("pla_");

	// Plus 0x10 to the memory location, 0x10 is the size per mem location, so we're adding to move on to the next
	u8 a = pull_stack(cpu);

	cpu->a = a;
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

void op_plp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("plp_");
	u8 am = address_mode(cpu, page_cross_toggle);

	u8 flags = pull_stack(cpu);

	// preserve bits 
	u8 ignore_bits = FLAG_UNUSED | FLAG_BREAK;

	// ignore bit 5 and the break flag
	cpu->status_flag = (cpu->status_flag & ignore_bits) | (flags & ~ignore_bits);

	// next time to ignore said bits:
	// first select those flags, 
	// second turn those flags on in the current status flag 
	// third turn them off in the value pulled flag.
	// then store back into sf.

	cpu->clock_counter += cycle;
}

void op_asl_a(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("asl_a\n");

	u8 carry = (cpu->a & FLAG_NEGATIVE) ? 1 : 0;
	u8 shift = cpu->a << 1;
	cpu->a = shift;

	if (carry)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

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

void op_asl(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("asl_");

	// 64kb memory address or Zero page address
	u16 addr = address_mode(cpu, page_cross_toggle);

	u8 shift;
	u8 carry;
	if (mem_type == ZPG)
	{
		carry = (cpu->memory[addr & 0xFF] & FLAG_NEGATIVE) ? 1 : 0;
		shift = cpu->memory[addr & 0xFF] << 1;
		cpu->memory[addr & 0xFF] = shift;
	}
	else if (mem_type == ABS)
	{
		carry = (cpu->memory[addr] & FLAG_NEGATIVE) ? 1 : 0;
		shift = cpu->memory[addr] << 1;
		cpu->memory[addr] = shift;
	}
	else
	{
		fprintf(stderr, "Invalid address mode: %d\n", mem_type);
		return;
	}
	
	if (carry)
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

void op_lsr_a(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("lsr_a");

	u8 carry = (cpu->a & FLAG_CARRY) ? 1 : 0;
	u8 shift = cpu->a >> 1;
	cpu->a = shift;
	
	if (carry & FLAG_CARRY)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}


void op_lsr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("lsr_");

	// 64kb memory address or Zero page address
	u16 address = address_mode(cpu, page_cross_toggle);

	u8 shift;
	u8 carry;

	if (mem_type == ZPG)
	{
		carry = cpu->memory[address & 0xFF] & FLAG_CARRY ? 1 : 0;
		shift = cpu->memory[address & 0xFF] >> 1;
		cpu->memory[address & 0xFF] = shift;
	}
	else if (mem_type == ABS)
	{
		carry = cpu->memory[address] & FLAG_CARRY ? 1 : 0;
		shift = cpu->memory[address] >> 1;
		cpu->memory[address] = shift;
	}
	else
	{
		fprintf(stderr, "Invalid address mode: %d\n", mem_type);
		return;
	}

	if (carry)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	cpu->status_flag &= ~FLAG_NEGATIVE;

	if (shift == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

// (TODO): Come back and redo the rotate instructions
void op_rol_a(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("rol_a");

	u8 carry_in = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;
	u8 carry_out = (cpu->a & FLAG_NEGATIVE) ? 1 : 0;

	u8 rotate = (cpu->a << 1) | (carry_in);
	cpu->a = rotate;

	if (carry_out)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

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

// (TODO): Come back and redo the rotate instructions
void op_rol(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("rol_");

	// 64kb memory address or Zero page address
	u16 mem_addr = address_mode(cpu, page_cross_toggle);
	u8 zpg_addr = mem_addr & 0xFF;

	u8 rotate;
	u8 input_bit;
	u8 carry = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;

	if (mem_type == ZPG)
	{
		input_bit = (cpu->memory[zpg_addr] & FLAG_NEGATIVE) ? 1 : 0;
		rotate = cpu->memory[zpg_addr] << 1 | carry;
		cpu->memory[zpg_addr] = rotate;
	}
	else if (mem_type == ABS)
	{
		input_bit = (cpu->memory[mem_addr] & FLAG_NEGATIVE) ? 1 : 0;
		rotate = cpu->memory[mem_addr] << 1 | carry;
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
void op_ror_a(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("ror_a_");

	// 64kb memory address or Zero page address
	u8 input_bit = cpu->a & FLAG_CARRY;
	u8 carry = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;
	u8 rotate = (cpu->a >> 1) | (carry << 7);

	cpu->a = rotate;

	if (input_bit)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

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

void op_ror(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("ror_");

	// 64kb memory address or Zero page address
	u16 address = address_mode(cpu, page_cross_toggle);
	
	u8 input_bit = cpu->memory[address] & FLAG_CARRY;
	u8 carry = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;
	u8 rotate = (cpu->memory[address] >> 1) | (carry << 7);

	cpu->memory[address] = rotate;
	
	if (input_bit)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (cpu->memory[address] & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->memory[address] == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_and(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("and_");

	u8 result = cpu->a & cpu->memory[address_mode(cpu, page_cross_toggle)];

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

void op_bit(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("bit_");

	u16 addr;
	u8 result;
	if (mem_type == ZPG)
	{
		addr = cpu->memory[address_mode(cpu, page_cross_toggle) & 0xFF];
		result = cpu->a & (addr & 0xFF);
	}
	else if (mem_type == ABS)
	{
		addr = cpu->memory[address_mode(cpu, page_cross_toggle)];
		result = cpu->a & addr;
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

void op_eor(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);
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

void op_ora(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("ora_");

	u16 address = address_mode(cpu, page_cross_toggle);

	if (mem_type == ZPG)
	{
		address &= 0xFF;
	}

	printf("cpu->a: %04X\n", cpu->a);
	printf("cpu->memory[address]: %04X\n", cpu->memory[address]);

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

void op_adc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("adc_");

	u8 a = cpu->a;
	u8 m = cpu->memory[address_mode(cpu, page_cross_toggle)];
	u8 c = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;

	u16 result = a + m + c;
	cpu->a = result & 0xFF;

	if (result > 0xFF)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;
	
	if ((a ^ cpu->a) & (m ^ cpu->a) & FLAG_NEGATIVE)
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

void op_cmp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("cmp_");

	u8 a = cpu->a;
	u8 m = cpu->memory[address_mode(cpu, page_cross_toggle)];

	printf("a: %0X2\n", cpu->a);
	printf("m: %0X2\n", m);

	u8 result = a - m;

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

void op_cpx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("cpx_");

	u8 x = cpu->x;
	u8 m = cpu->memory[address_mode(cpu, page_cross_toggle)];

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

void op_cpy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("cpy_");

	u8 y = cpu->y;
	u8 m = cpu->memory[address_mode(cpu, page_cross_toggle)];

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

void op_sbc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("sbc_");

	u8 a = cpu->a;
	u8 m = cpu->memory[address_mode(cpu, page_cross_toggle)];
	u8 c = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;

	u16 result = a - m - (1 - c);
	cpu->a = result & 0xFF;

	if (result < 0x100)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if ((a ^ m) & (a ^ cpu->a) & FLAG_NEGATIVE)
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

void op_dec(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("dec_");

	u16 m = address_mode(cpu, page_cross_toggle);
	cpu->memory[m] -= 1;

	if (cpu->memory[m] & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->memory[m] == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_dex(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("dex_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->x -= 1;

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

void op_dey(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("dey_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->y -= 1;

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

void op_inc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("inc_");

	u16 m = address_mode(cpu, page_cross_toggle);
	cpu->memory[m] += 1;

	if (cpu->memory[m] & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->memory[m] == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void op_inx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("inx_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->x += 1;

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

void op_iny(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("iny_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->y += 1;

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

void op_brk(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
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

void op_jmp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("jmp_");

	u16 target_address = address_mode(cpu, page_cross_toggle);

	cpu->program_counter = target_address;
	printf("Jumped to: 0x%04X\n", cpu->program_counter);

	cpu->clock_counter += cycle;
}

void op_jsr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("jsr_");

	u16 target_address = address_mode(cpu, page_cross_toggle);
	u16 return_address = cpu->program_counter - 1;

	push_stack(cpu, (return_address >> 8) & 0xFF); // hi
	push_stack(cpu, return_address & 0xFF); // lo

	printf("JSR return_address: 0x%X\n", return_address);

	cpu->program_counter = target_address;

	cpu->clock_counter += cycle;
}

void op_rti(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("rti_");

	u8 flags = pull_stack(cpu);

	// preserve bits 
	cpu->status_flag = flags | FLAG_UNUSED;

	u8 lo = pull_stack(cpu);
	u8 hi = pull_stack(cpu);

	u16 return_address = (hi << 8) | lo;

	cpu->program_counter = return_address;

	cpu->clock_counter += cycle;
}

void op_rts(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
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

void op_bcc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("bcc_");

	i8 signed_offset = (i8)cpu->memory[cpu->program_counter++];
	
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

void op_bcs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("bcs_");

	i8 signed_offset = (i8)cpu->memory[cpu->program_counter++];

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

void op_beq(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("beq_");

	i8 signed_offset = (i8)cpu->memory[cpu->program_counter++];

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

void op_bmi(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("bmi_");

	i8 signed_offset = (i8)cpu->memory[cpu->program_counter++];

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

void op_bne(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("bne_");

	i8 signed_offset = (i8)cpu->memory[cpu->program_counter++];

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

void op_bpl(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("bpl_");

	i8 signed_offset = (i8)cpu->memory[cpu->program_counter++];

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

void op_bvc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("bvc_");

	i8 signed_offset = (i8)cpu->memory[cpu->program_counter++];

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

void op_bvs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("bvs_");

	i8 signed_offset = (i8)cpu->memory[cpu->program_counter++];

	u16 current_address = cpu->program_counter;
	u16 target_address = current_address + signed_offset;

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

void op_clc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("clc_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->status_flag &= ~FLAG_CARRY;

	cpu->clock_counter += cycle;
}

void op_cld(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("cld_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->status_flag &= ~FLAG_DECIMAL;

	cpu->clock_counter += cycle;
}

void op_cli(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("cli_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->status_flag &= ~FLAG_INTERRUPT;

	cpu->clock_counter += cycle;
}

void op_clv(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("clv_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->status_flag &= ~FLAG_OVERFLOW;

	cpu->clock_counter += cycle;
}

void op_sec(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("sec_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->status_flag |= FLAG_CARRY;

	cpu->clock_counter += cycle;
}

void op_sed(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("sed_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->status_flag |= FLAG_DECIMAL;

	cpu->clock_counter += cycle;
}


void op_sei(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("sei_");
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->status_flag |= FLAG_INTERRUPT;

	cpu->clock_counter += cycle;
}

void nop(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("nop_");
	u8 address = address_mode(cpu, page_cross_toggle);

	cpu->clock_counter += cycle;
}

// Illegal
void jam(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("jam_");
	// Reset
}

void slo(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("slo_");
	u16 address = address_mode(cpu, page_cross_toggle);

	if (mem_type == ZPG)
	{
		address &= 0xFF;
	}

	u8 value = cpu->memory[address];

	if (value & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	u8 result = cpu->memory[address] << 1;

	cpu->memory[address] = result;
	cpu->a |= cpu->memory[address];

	if (cpu->a & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->memory[address] == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}

void anc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);

	u8 result = cpu->a & cpu->memory[address];
	cpu->a = result;


	if (cpu->a & FLAG_NEGATIVE)
	{
		cpu->status_flag |= FLAG_CARRY;
		cpu->status_flag |= FLAG_NEGATIVE;
	}
	else
	{
		cpu->status_flag |= FLAG_CARRY;
		cpu->status_flag &= ~FLAG_NEGATIVE;
	}

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	cpu->clock_counter += cycle;
}


void arr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);

	u8 carry = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;
	u8 result = (cpu->a & cpu->memory[address]) >> 1 | carry << 7;
	cpu->a = result;

	if (cpu->a & FLAG_OVERFLOW)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (cpu->a & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	// Binary mode (NES's default mode)
	if ((cpu->a ^ FLAG_OVERFLOW) & (cpu->a ^ FLAG_UNUSED))
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;


	cpu->clock_counter += cycle;
}

void asr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->clock_counter += cycle;

}

void rla(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);

	if (mem_type == ZPG)
	{
		address &= 0xFF;
	}

	u8 value = cpu->memory[address];
	u8 carry = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;

	if (value & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	u8 result = (value << 1) | carry;

	cpu->memory[address] = result;
	cpu->a &= result;

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

void sax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);

	cpu->memory[address] = cpu->a & cpu->x;

	cpu->clock_counter += cycle;
}

void dcp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);

	u8 result;
	if (mem_type == ZPG)
	{
		cpu->memory[address & 0xFF] -= 1;
		result = cpu->a - cpu->memory[address & 0xFF];
	}

	cpu->memory[address] -= 1;
	result = cpu->a - cpu->memory[address];
	
	if (cpu->memory[address] <= cpu->a)
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

void isc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);

	if (mem_type == ZPG)
	{
		address &= 0xFF;
	}

	u8 carry = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;
	cpu->memory[address] += 1;
	u8 mem = cpu->memory[address];

	u16 temp = (u16)cpu->a - (u16)mem - (1 - carry);
	u8 result = (u8)temp;

	cpu->a = result;

	if (temp < 0x100)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (((cpu->a ^ result) & (cpu->a ^ mem)) & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;

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

void las(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->clock_counter += cycle;

}

void lax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	printf("lax_");

	u16 address = address_mode(cpu, page_cross_toggle);
	cpu->x = cpu->memory[address];
	cpu->a = cpu->memory[address];

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

void lxa(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->clock_counter += cycle;

}

void sha(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);

	cpu->memory[address];


	cpu->clock_counter += cycle;

}

void shx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->clock_counter += cycle;

}

void shy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->clock_counter += cycle;

}

void shs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->clock_counter += cycle;

}

void sre(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);

	if (mem_type == ZPG)
	{
		address &= 0xFF;
	}

	u8 value = cpu->memory[address];

	if (value & FLAG_CARRY)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	u8 result = value >> 1;

	cpu->memory[address] = result;
	cpu->a ^= result;

	if (cpu->a & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (result == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;


	cpu->clock_counter += cycle;
}

void xaa(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->clock_counter += cycle;

}

void rra(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{
	u16 address = address_mode(cpu, page_cross_toggle);

	if (mem_type == ZPG)
	{
		address &= 0xFF;
	}

	u8 value = cpu->memory[address];
	u8 carry_old = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;

	if (value & FLAG_CARRY)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	u8 result = (value >> 1) | (carry_old << 7);

	cpu->memory[address] = result;

	u8 a = cpu->a;
	u8 m = result;
	u8 carry_new = (cpu->status_flag & FLAG_CARRY) ? 1 : 0;
	
	u16 add = (u16)a + (u16)m + (u16)carry_new;

	cpu->a = add & 0xFF;

	if (add > 0xFF)
		cpu->status_flag |= FLAG_CARRY;
	else
		cpu->status_flag &= ~FLAG_CARRY;

	if (cpu->a & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_NEGATIVE;
	else
		cpu->status_flag &= ~FLAG_NEGATIVE;

	if (cpu->a == 0)
		cpu->status_flag |= FLAG_ZERO;
	else
		cpu->status_flag &= ~FLAG_ZERO;

	if (~(a ^ result) & (a ^ cpu->a) & FLAG_NEGATIVE)
		cpu->status_flag |= FLAG_OVERFLOW;
	else
		cpu->status_flag &= ~FLAG_OVERFLOW;

	cpu->clock_counter += cycle;
}

void sbx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle)
{	u8 am = address_mode(cpu, page_cross_toggle);

	cpu->clock_counter += cycle;

}
 


