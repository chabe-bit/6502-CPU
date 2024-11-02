#pragma once
#include "t_common.h"
#include "t_cpu.h"
#include "t_utility.h"

// Load
void t_op_lda(nes_cpu* cpu, am_t address_mode, u8 cycle);

void op_lda(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_ldx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_ldy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_sta(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_stx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_sty(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Transfer
void op_tax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_tay(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_tsx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_txa(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_txs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_tya(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Stack
void op_pha(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_php(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_pla(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_plp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Shift
void op_asl(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_asl_a(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_lsr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_lsr_a(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_rol(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_rol_a(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_ror(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_ror_a(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Logic
void op_and(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_bit(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_eor(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_ora(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Arithmetic
void op_adc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_cmp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_cpx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_cpy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_sbc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Increment
void op_dec(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_dex(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_dey(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_inc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_inx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_iny(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Control
void op_brk(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_jmp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_jsr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_rti(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_rts(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Branch
void op_bcc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_bcs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_beq(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_bmi(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_bne(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_bpl(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_bvc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_bvs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Flags
void op_clc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_cld(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_cli(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_clv(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_sec(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_sed(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void op_sei(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);


// Nop
void nop(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

// Illegal
void las(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void lax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void lxa(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void sax(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void sha(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void shx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void shy(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

void shs(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

void anc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void arr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void asr(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void dcp(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void isc(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void rla(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void rra(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void sbx(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void slo(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void sre(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);
void xaa(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);

void jam(nes_cpu* cpu, u16(*address_mode)(nes_cpu*, bool), bool page_cross_toggle, int mem_type, u8 cycle);



