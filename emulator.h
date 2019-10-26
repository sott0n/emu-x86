#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <stdint.h>

enum Register { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTERS_COUNT,
                AL = EAX, CL = ECX, DL = EDX, BL = EBX,
                AH = AL + 4, CH = CL + 4, DH = DL + 4, BH = BL + 4 };

typedef struct {
    uint32_t registers[REGISTERS_COUNT];
    uint32_t eflags;
    uint8_t* memory;
    uint32_t eip;
} Emulator;

#endif