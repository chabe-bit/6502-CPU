#include "t_cpu.h"
#include "t_am.h"
#include "t_instr.h"
#include "t_ines.h"

int main()
{
	nes_cpu cpu = { 0 };
	nes_init_cpu(&cpu);
	nes_init_instructions(&cpu);

	ines_file_format ines = { 0 };
	ines_roms ines_roms = { 0 };

	nes_dump_file();
	nes_read_header(&ines);
	nes_load_rom(&ines, &ines_roms);
	nes_map_prg_rom(&cpu, &ines_roms);

	//print_opcode_table();
	nes_cpu_run(&cpu);


	return 0;
}