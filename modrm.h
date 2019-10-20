#ifndef MODRM_H_
#define MODRM_H_

#include <stdint.h>

#include "emulator.h"

typedef struct {
    uint8_t mod;

    union {
        /* data */
        uint8_t opecode;
        uint8_t reg_index;
    };

    uint8_t rm;

    uint8_t sib;

    union {
        /* data */
        int8_t disp8;
        uint8_t disp32;
    };
} ModRM;

void parse_modrm(Emulator* emu, ModRM* modrm);

uint32_t calc_memory_address(Emulator* emu, ModRM* modrm);

uint32_t get_rm32(Emulator* emu, ModRM* modrm);

void set_rm32(Emulator* emu, ModRM* modrm, uint32_t value);

uint32_t get_r32(Emulator* emu, ModRM* modrm);

void set_r32(Emulator* emu, ModRM* modrm, uint32_t value);

#endif