#include "t_cpu.h"
#include "t_utility.h"

u16 am_rel(nes_cpu* cpu)
{
	u8 signed_value = cpu->memory[cpu->program_counter++];
	
	push_operand(cpu, signed_value, 0);

	printf("rel\n");

	return signed_value;
}

u16 am_zpg_ind_y(nes_cpu* cpu)
{
	u8 operand = cpu->memory[cpu->program_counter++];
	push_operand(cpu, operand, 0);

	u8 zpg_eff_addr = cpu->y + operand;

	u8 zpg_lo = cpu->memory[zpg_eff_addr] & 0xFF;
	u8 zpg_hi = cpu->memory[zpg_eff_addr + 1] & 0xFF;

	u16 eff_addr = (zpg_hi << 8) & zpg_lo;

	printf("zpg_ind_y\n");
	return eff_addr;
}


u16 am_zpg_x_ind(nes_cpu* cpu)
{
	u8 operand = cpu->memory[cpu->program_counter++];
	push_operand(cpu, operand, 0);

	u8 zpg_eff_addr = cpu->x + operand;

	u8 zpg_lo = cpu->memory[zpg_eff_addr] & 0xFF;
	u8 zpg_hi = cpu->memory[zpg_eff_addr + 1] & 0xFF;

	u16 eff_addr = (zpg_hi << 8) & zpg_lo;

	printf("zpg_ind_y\n");
	return eff_addr;
}

u16 am_zpg_y(nes_cpu* cpu)
{
	u8 operand = cpu->memory[cpu->program_counter++];
	push_operand(cpu, operand, 0);

	u16 eff_addr = cpu->y + operand;

	printf("zpg_y\n");
	return eff_addr;
}

u16 am_zpg_x(nes_cpu* cpu)
{
	u8 operand = cpu->memory[cpu->program_counter++];
	push_operand(cpu, operand, 0);

	u16 eff_addr = cpu->x + operand;

	printf("zpg_x\n");
	return eff_addr;
}

u16 am_zpg(nes_cpu* cpu)
{
	u8 operand = cpu->memory[cpu->program_counter++];
	push_operand(cpu, operand, 0);

	//u16 eff_addr = (1 << 8 | operand);

	printf("zpg\n");
	return operand;
}

u16 am_abs_ind(nes_cpu* cpu)
{
	u8 lo = cpu->memory[cpu->program_counter++];
	u8 hi = cpu->memory[cpu->program_counter++];
	push_operand(cpu, lo, hi);

	u16 base_addr = (hi << 8) | lo;

	u8 eff_lo = cpu->memory[base_addr];
	u8 eff_hi = cpu->memory[base_addr + 1];

	u16 eff_addr = (eff_hi << 8) | eff_lo;

	// (TODO): Implement page boundary bug

	printf("abs_ind\n");
	return eff_addr;
}

u16 am_abs_y(nes_cpu* cpu)
{
	u8 prev_pc = cpu->program_counter;
	u8 lo = cpu->memory[cpu->program_counter++];
	u8 hi = cpu->memory[cpu->program_counter++];
	u8 curr_pc = cpu->program_counter;

	u16 base_addr = (hi << 8) | lo;
	u16 eff_addr = cpu->y + base_addr;

	if ((prev_pc & 0xFF00) != (curr_pc & 0xFF00))
	{
		cpu->clock_counter += 1;
	}

	push_operand(cpu, lo, hi);

	printf("abs_y\n");
	return eff_addr;
}

u16 am_abs_x(nes_cpu* cpu)
{
	u8 prev_pc = cpu->program_counter;
	u8 lo = cpu->memory[cpu->program_counter++];
	u8 hi = cpu->memory[cpu->program_counter++];
	u8 curr_pc = cpu->program_counter;

	u16 base_addr = (hi << 8) | lo;
	u16 eff_addr = cpu->x + base_addr;

	if ((prev_pc & 0xFF00) != (curr_pc & 0xFF00))
	{
		cpu->clock_counter += 1;
	}

	push_operand(cpu, lo, hi);

	printf("abs_x\n");
	return eff_addr;
}

u16 am_abs(nes_cpu* cpu)
{
	u8 lo = cpu->memory[cpu->program_counter++];
	u8 hi = cpu->memory[cpu->program_counter++];

	u16 eff_addr = (hi << 8) | lo;

	push_operand(cpu, lo, hi);

	printf("abs\n");

	return eff_addr;
}

u16 am_impl(nes_cpu* cpu)
{
	u16 addr = cpu->program_counter;

	push_operand(cpu, cpu->memory[addr], 0);

	printf("impl\n");
	return addr;
}

u16 am_a(nes_cpu* cpu)
{
	u16 a = cpu->a;

	push_operand(cpu, a, 0);

	printf("acc\n");
	return a;
}

u16 am_imm(nes_cpu* cpu)
{
	u16 addr = cpu->program_counter++;

	push_operand(cpu, cpu->memory[addr], 0);

	printf("imm\n");
	return addr;
}