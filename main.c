#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MEMORY_SIZE (1024 * 1024)

enum Register { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REGISTERS_COUNT };
char* registers_name[] = {
    "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};

typedef struct {
    uint32_t registers[REGISTERS_COUNT];
    uint32_t eflags;
    uint8_t* memory;
    uint32_t eip;
} Emulator;

static Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp) {
    Emulator* emu = malloc(sizeof(Emulator));
    emu->memory = malloc(size);

    memset(emu->registers, 0, sizeof(emu->registers));

    emu->eip = eip;
    emu->registers[ESP] = esp;

    return emu;
}

void destroy_emu(Emulator* emu) {
    free(emu->memory);
    free(emu);
}

static void dump_registers(Emulator* emu) {
    int i;
    for (i = 0; i < REGISTERS_COUNT; i++) {
        printf("%s = %08x\n", registers_name[i], emu->registers[i]);
    }

    printf("EIP = %08x\n", emu->eip);
}

uint32_t get_code8(Emulator* emu, int index) {
    return emu->memory[emu->eip + index];
}

int32_t get_sign_code8(Emulator* emu, int index) {
    return (int8_t)emu->memory[emu->eip + index];
}

uint32_t get_code32(Emulator* emu, int index) {
    int i;
    uint32_t ret = 0;

    for (i = 0; i < 4; i++) {
        ret |= get_code8(emu, index + i) << (i * 8);
    }

    return ret;
}

int32_t get_sign_code32(Emulator* emu, int index) {
    return (int32_t)get_code32(emu, index);
}

void mov_r32_imm32(Emulator* emu) {
    uint8_t reg = get_code8(emu, 0) - 0xB8;
    uint32_t value = get_code32(emu, 1);
    emu->registers[reg] = value;
    emu->eip += 5;
}

void short_jump(Emulator* emu) {
    int8_t diff = get_sign_code8(emu, 1);
    emu->eip += (diff + 2);
}

void near_jump(Emulator* emu) {
    int32_t diff = get_sign_code32(emu, 1);
    emu->eip += (diff + 5);
}

typedef void instruction_func_t(Emulator*);
instruction_func_t* instructions[256];
void init_instructions(void) {
    int i;
    memset(instructions, 0, sizeof(instructions));
    for (i = 0; i < 8; i++) {
        instructions[0xB8 + i] = mov_r32_imm32;
    }
    instructions[0xE9] = near_jump;
    instructions[0xEB] = short_jump;
}

int main(int argc, char* argv[]) {
    FILE* binary;
    Emulator* emu;

    if (argc != 2) {
        printf("usage: px86 filename\n");
        return 1;
    }

    emu = create_emu(MEMORY_SIZE, 0x7c00, 0x7c00);

    binary = fopen(argv[1], "rb");
    if (binary == NULL) {
        printf("Can't open file: %s\n", argv[1]);
        return 1;
    }

    fread(emu->memory + 0x7c00, 1, 0x200, binary);
    fclose(binary);

    init_instructions();

    while (emu->eip < MEMORY_SIZE) {
        uint8_t code = get_code8(emu, 0);
        printf("EIP = %X, Code = %02X\n", emu->eip, code);

        if (instructions[code] == NULL) {
            printf("\n\nNot Implemented: %x\n", code);
            break;
        }

        instructions[code](emu);

        if (emu->eip == 0x00) {
            printf("\n\nend of program.\n\n");
            break;
        }
    }

    dump_registers(emu);
    destroy_emu(emu);
    return 0;
}