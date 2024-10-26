#include "t_ines.h"
#include "t_utility.h"

void nes_dump_file()
{
	FILE* stream;
	if ((stream = fopen("nestest.nes", "rb")) == 0)
	{
		fprintf(stderr, "fopen() failed to open: %s\n");
		return;
	}

	if (fseek(stream, 16, SEEK_SET) == 1)
	{
		fprintf(stderr, "fseek() failed to seek .nes file: %s\n");
		fclose(stream);
		return;
	}

	char ch;
	int count = 0;
	while ((ch = fgetc(stream)) != EOF) {
		count++;
		printf("%02X \t", (u8)ch);
		if (count % 10 == 0)
			printf("\n");
	}
	printf("\n");

	fclose(stream);
}

void nes_read_header(ines_file_format *header)
{
	// Open the file
	FILE* stream;
	if ((stream = fopen("nestest.nes", "rb")) == 0)
	{
		fprintf(stderr, "fopen() failed to open: %s\n");
		return;
	}

	// Read the file 1 byte at a time
	if (fread(header, sizeof(*header), 1, stream) == 0)
	{
		fprintf(stderr, "fread() failed to read .nes file: %s\n");
		fclose(stream);
		return;
	}

	// Check the signature
	if (header->n != 'N' || header->e != 'E' || header->s != 'S' || header->_ != 0x1A)
	{
		printf("Failed to match .nes signature: %s\n");
		fclose(stream);
		return;
	}

	printf("PRG ROM Banks: %d\n", header->n_prg_rom_banks);
	printf("CHR ROM Banks: %d\n", header->n_chr_rom_banks);

	// Close the file
	fclose(stream);
}


void allocate_prg_rom_bank(FILE *stream, ines_file_format* header, ines_roms *rom)
{
	rom->prg_rom_banks_size = header->n_prg_rom_banks; 
	rom->prg_rom_banks = malloc(sizeof(u8*) * rom->prg_rom_banks_size);
	if (rom->prg_rom_banks == NULL)
	{
		printf("Failed to allocate: rom->prg_rom_banks\n");
		return;
	}

	for (u32 i = 0; i < rom->prg_rom_banks_size; i++) 
	{
		rom->prg_rom_banks[i] = malloc(16 * 1024); // Allocate 16 KB for each bank
		if (!rom->prg_rom_banks[i]) 
		{
			fprintf(stderr, "Failed to allocate memory for PRG ROM bank %u.\n", i);
			fclose(stream);
			exit(1);
		}
	}
}

// (TODO): free_prg_rom_bank

void load_prg_rom_bank(FILE *stream, ines_roms *rom)
{
	for (u32 i = 0; i < rom->prg_rom_banks_size; i++) 
	{
		size_t bytes_read = fread(rom->prg_rom_banks[i], 1, 16 * 1024, stream);
		if (bytes_read != 16 * 1024) 
		{
			fprintf(stderr, "Failed to read PRG ROM bank %u.\n", i);
			fclose(stream);
			exit(1);
		}
	}
}


void nes_load_rom(ines_file_format *header, ines_roms *rom)
{
	// Open file
	FILE *stream;
	if ((stream = fopen("nestest.nes", "rb")) == 0)
	{
		fprintf(stderr, "fopen() failed to open .nes file: %s\n");
		return;
	}

	// Skip 16 bytes ahead
	if (fseek(stream, 16, SEEK_SET) == 1)
	{
		fprintf(stderr, "fseek() failed to seek .nes file: %s\n");
		fclose(stream);
		return;
	}

	allocate_prg_rom_bank(stream, header, rom);
	load_prg_rom_bank(stream, rom);
	
	// Allocate memory into chr_rom bank 
	rom->chr_rom_banks_size = header->n_chr_rom_banks * 8 * 1024;
	if (rom->chr_rom_banks_size > 0)
	{
		rom->chr_rom_banks = malloc(sizeof(u8*) * rom->chr_rom_banks_size);
		if (rom->chr_rom_banks == NULL)
		{
			printf("Failed to allocate: rom->chr_rom_banks\n");
			fclose(stream);
			return;
		}

		// Read and store chr_rom size into chr_rom bank  
		if (fread(rom->chr_rom_banks, rom->chr_rom_banks_size, 1, stream) == 0)
		{
			fprintf(stderr, "fread() failed to read .nes file: %s\n");
			fclose(stream);
			return;
		}
	}
	else
	{
		// Read and store chr_ram size into chr_ram bank   
		rom->chr_ram_banks = malloc(sizeof(u8*) * 8 * 1024);
		if (rom->chr_ram_banks == NULL)
		{
			fprintf(stderr, "Failed to allocate to chr_ram\n");
			fclose(stream);
			return;
		}
		memset(rom->chr_ram_banks, 0, 8192); 
	}
	

	printf("nes_read_rom\n");
	fclose(stream);
}

void nes_map_prg_rom(nes_cpu *cpu, ines_roms *roms)
{
	int count = 0;
	if (roms->prg_rom_banks_size == 1) 
	{
		memcpy(&cpu->memory[0x8000], roms->prg_rom_banks[0], 16 * 1024);
		memcpy(&cpu->memory[0xC000], roms->prg_rom_banks[0], 16 * 1024);

		for (int i = 0xC000; i <= 0xC000 + 10; i++)
		{
			count++;
			printf("0x%X: 0x%X\t", i, cpu->memory[i]);
			if ((count % 10) == 0)
			{
				printf("\n");
			}
		}
		printf("\n");

		printf("0x%04X\t", cpu->memory[0xC5F5]);


	}
	else if (roms->prg_rom_banks_size == 2) 
	{
		memcpy(&cpu->memory[0x8000], roms->prg_rom_banks[0], 16 * 1024);
		memcpy(&cpu->memory[0xC000], roms->prg_rom_banks[1], 16 * 1024);

		printf("After memcpy:\n");
		for (int i = 0x8000; i <= 0x8000 + 10; i++)
		{
			count++;
			printf("0x%04X: 0x%04X\t", i, cpu->memory[i]);
			if ((count % 10) == 0)
			{
				printf("\n");
			}
		}
		printf("\n");

	}
	else
	{
		printf("Unsupported PRG ROM size: %u banks.\n", roms->prg_rom_banks_size);
		return;
	}

	printf("Successfully mapped PRG ROM.\n");

}

