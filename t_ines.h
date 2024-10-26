#pragma once
#include "t_common.h"
#include "t_cpu.h"

typedef struct
{
	u32 prg_rom_banks_size;
	u32 chr_rom_banks_size;

	u8 **prg_rom_banks;
	u8 *chr_rom_banks;
	u8 *chr_ram_banks;

} ines_roms;

typedef struct
{
	u8 n;
	u8 e;
	u8 s;
	u8 _;

	u8 n_prg_rom_banks;
	u8 n_chr_rom_banks;

	u8 flags_6;
	u8 flags_7;
	u8 flags_8;
	u8 flags_9;

	u8 reserved_1;
	u8 reserved_2;
	u8 reserved_3;
	u8 reserved_4;
	u8 reserved_5;

} ines_file_format;

void nes_dump_file();

void nes_read_header(ines_file_format *header);
void nes_load_rom(ines_file_format *header, ines_roms *rom);
void nes_map_prg_rom(nes_cpu *cpu, ines_roms *roms);

