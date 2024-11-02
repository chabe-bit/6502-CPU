#pragma once
#include "t_common.h"
#include "t_cpu.h"

//am_t t_impl(nes_cpu* cpu);
//am_t t_a(nes_cpu* cpu);
//am_t t_imm(nes_cpu* cpu);
//am_t t_abs(nes_cpu* cpu);
//am_t t_abs_x(nes_cpu* cpu);
//am_t t_abs_y(nes_cpu* cpu);
//am_t t_abs_ind(nes_cpu* cpu);
//am_t t_zpg(nes_cpu* cpu);
//am_t t_zpg_x(nes_cpu* cpu);
//am_t t_zpg_y(nes_cpu* cpu);
//am_t t_zpg_x_ind(nes_cpu* cpu);
am_t t_zpg_ind_y(nes_cpu* cpu);
am_t t_rel(nes_cpu* cpu);

void a_lda(nes_cpu* cpu, am_t mode);
void a_zpg_ind_y(nes_cpu* cpu, void(*instruction)(nes_cpu*, am_t), u8 cycle);


void page_cross_enabled(nes_cpu* cpu, u16 base_addr, u16 eff_addr);
u16 am_impl(nes_cpu* cpu, bool page_cross_toggle);
u16 am_a(nes_cpu* cpu, bool page_cross_toggle);
u16 am_imm(nes_cpu* cpu, bool page_cross_toggle);
u16 am_abs(nes_cpu* cpu, bool page_cross_toggle);
u16 am_abs_x(nes_cpu* cpu, bool page_cross_toggle);
u16 am_abs_y(nes_cpu* cpu, bool page_cross_toggle);
u16 am_abs_ind(nes_cpu* cpu, bool page_cross_toggle);
u16 am_zpg(nes_cpu* cpu, bool page_cross_toggle);
u16 am_zpg_x(nes_cpu* cpu, bool page_cross_toggle);
u16 am_zpg_y(nes_cpu* cpu, bool page_cross_toggle);
u16 am_zpg_x_ind(nes_cpu* cpu, bool page_cross_toggle);
u16 am_zpg_ind_y(nes_cpu* cpu, bool page_cross_toggle);
u16 am_rel(nes_cpu* cpu, bool page_cross_toggle);
