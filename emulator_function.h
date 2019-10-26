#ifndef EMULATOR_FUNCTION_H_
#define EMULATOR_FUNCTION_H_

#include <stdint.h>

#include "emulator.h"

/* eflags */
#define CARRY_FLAG (1)
#define ZERO_FLAG (1 << 6)
#define SIGN_FLAG (1 << 7)
#define OVERFLOW_FLAG (1 << 11)

uint32_t get_code8(Emulator* emu, int index);
int32_t get_sign_code8(Emulator* emu, int index);
uint32_t get_code32(Emulator* emu, int index);
int32_t get_sign_code32(Emulator* emu, int index);
uint8_t get_register8(Emulator* emu, int index);
uint32_t get_register32(Emulator* emu, int index);
void set_register8(Emulator* emu, int index, uint8_t value);
void set_register32(Emulator* emu, int index, uint32_t value);
uint32_t get_memory8(Emulator* emu, uint32_t address);
uint32_t get_memory32(Emulator* emu, uint32_t address);
void set_memory8(Emulator* emu, uint32_t address, uint32_t value);
void set_memory32(Emulator* emu, uint32_t address, uint32_t value);
void push32(Emulator* emu, uint32_t value);
uint32_t pop32(Emulator* emu);

/* EFLAG setting function */
void set_carry(Emulator* emu, int is_carry);
void set_zero(Emulator* emu, int is_zero);
void set_sign(Emulator* emu, int is_sign);
void set_overflow(Emulator* emu, int is_overflow);

/* EFLAG getting function */
int32_t is_carry(Emulator* emu);
int32_t is_zero(Emulator* emu);
int32_t is_sign(Emulator* emu);
int32_t is_overflow(Emulator* emu);

void update_eflags_sub(Emulator* emu, uint32_t v1, uint32_t v2, uint64_t result);

#endif