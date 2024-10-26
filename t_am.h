#pragma once
#include "t_common.h"
#include "t_cpu.h"


u16 am_impl(nes_cpu* cpu);
u16 am_a(nes_cpu* cpu);
u16 am_imm(nes_cpu* cpu);
u16 am_abs(nes_cpu* cpu);
u16 am_abs_x(nes_cpu* cpu);
u16 am_abs_y(nes_cpu* cpu);
u16 am_abs_ind(nes_cpu* cpu);
u16 am_zpg(nes_cpu* cpu);
u16 am_zpg_x(nes_cpu* cpu);
u16 am_zpg_y(nes_cpu* cpu);
u16 am_zpg_x_ind(nes_cpu* cpu);
u16 am_zpg_ind_y(nes_cpu* cpu);
u16 am_rel(nes_cpu* cpu);
