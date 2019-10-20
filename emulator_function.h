#ifndef EMULATOR_FUNCTION_H_
#define EMULATOR_FUNCTION_H_

#include <stdint.h>

#include "emulator.h"

uint32_t get_code8(Emulator* emu, int index);
int32_t get_sign_code8(Emulator* emu, int index);
uint32_t get_code32(Emulator* emu, int index);
int32_t get_sign_code32(Emulator* emu, int index);
uint32_t get_register32(Emulator* emu, int index);
void set_register32(Emulator* emu, int index, uint32_t value);
uint32_t get_memory8(Emulator* emu, uint32_t address);
uint32_t get_memory32(Emulator* emu, uint32_t address);
void set_memory8(Emulator* emu, uint32_t address, uint32_t value);
void set_memory32(Emulator* emu, uint32_t address, uint32_t value);

#endif