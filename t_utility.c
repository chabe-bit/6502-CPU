#include "t_utility.h"

void print_binary(u8 value)
{
	printf("0b");
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", (value >> i) & 1);
	}
	printf("\n");
}

void push_stack(nes_cpu* cpu, u8 value)
{
	if (cpu->stack_pointer == 0x00)
	{
		fprintf(stderr, "Stack is full, cannot push: 0x%02X onto the stack.\n", value);
		return;
	}

	cpu->memory[STACK + cpu->stack_pointer] = value;
	cpu->stack_pointer--;

	printf("Pushed onto stack: 0x%02X at 0x%02X\n", value, STACK + cpu->stack_pointer);
}

u8 pull_stack(nes_cpu* cpu)
{
	if (cpu->stack_pointer > 0xFF)
	{
		fprintf(stderr, "Stack is empty, cannot pull: 0x%02X off the stack.\n");
		return -1;
	}

	cpu->stack_pointer++;
	u8 value = cpu->memory[STACK + cpu->stack_pointer];

	printf("Pulled from stack: 0x%02X at 0x%02X\n", value, STACK + cpu->stack_pointer);
	return value;
}

void print_internal_ram(nes_cpu* cpu, u8 start, u16 end)
{
	int count = 0;
	printf("RAM region: \n");
	for (int i = start; i <= end; ++i)
	{
		printf("0x%04X: %d\t", i, cpu->memory[i]);
		count++;
		if (count % 10 == 0) {
			printf("\n");
		}
	}
}

void print_stack(nes_cpu* cpu)
{
	int count = 0;
	printf("Stack region: \n");
	for (int i = 0x0100 + 0x00FF; i >= 0x0100; --i)
	{
		printf("0x%X: %c%c%c%c %c%c%c%c\t", i, BYTE_TO_BINARY(cpu->memory[i]));
		count++;
		if (count % 10 == 0) {
			printf("\n");
		}
	}
}

void view_status_flag(u8 value)
{
	printf("%d%d%d%d%d%d%d%d\n",
		(value >> 7) & 1,
		(value >> 6) & 1,
		(value >> 5) & 1,
		(value >> 4) & 1,
		(value >> 3) & 1,
		(value >> 2) & 1,
		(value >> 1) & 1,
		(value >> 0) & 1);
}

void push_operand(nes_cpu* cpu, u8 val1, u8 val2)
{
	for (int i = 0; i < 2; i++)
	{
		cpu->operands[i] = 0x00;
	}

	cpu->operands[0] = val1;
	cpu->operands[1] = val2;

}