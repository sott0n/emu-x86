# emu-x86
A emulator for 80386 cpu that is x86 architecture as 32bit.

## Requirements

This emulator assumes 32bit, so it requires a binary for 32bit. This project includes a gcc for i386 under tools directory. To make a 32bit binary of test code, please use it.

## Usage

First, make a 32bit binary (ex, from assembly or c file).  

```
$ cd tests
$ make # create a 32bit binary
# -> make 'test.bin' binary
```

Second, make a x86 emulator program's binary.  

```
$ cd .. # move root directory this project
$ make # create a x86 emulator program's binary
# -> make 'emux86' binary
```

Finally, run a emulator to read a 32bit binary.

```
$ ./emux86 test.bin
```

## Sample

### input source code as c lang.
```c
BITS 32
    org 0x7c00
start:
    mov edx, 0x03f8
mainloop:
    mov al, '>'
    out dx, al
input:
    in al, dx
    cmp al, 'h'
    je puthello
    cmp al, 'w'
    je putworld
    cmp al, 'q'
    je fin
    jmp input
puthello:
    mov esi, msghello
    call puts
    jmp mainloop
putworld:
    mov esi, msgworld
    call puts
    jmp mainloop
fin:
    jmp 0

puts:
    mov al, [esi]
    inc esi
    cmp al, 0
    je putsend
    out dx, al
    jmp puts
putsend:
    ret

msghello:
    db "hello", 0x0d, 0x0a, 0
msgworld:
    db "world", 0x0d, 0x0a, 0
```

### assembler of c code.
```asm
$ ndisasm -b 32 tests/select.bin
00000000  BAF8030000        mov edx,0x3f8
00000005  B03E              mov al,0x3e
00000007  EE                out dx,al
00000008  EC                in al,dx
00000009  3C68              cmp al,0x68
0000000B  740A              jz 0x17
0000000D  3C77              cmp al,0x77
0000000F  7412              jz 0x23
00000011  3C71              cmp al,0x71
00000013  741A              jz 0x2f
00000015  EBF1              jmp short 0x8
00000017  BE3F7C0000        mov esi,0x7c3f
0000001C  E813000000        call 0x34
00000021  EBE2              jmp short 0x5
00000023  BE477C0000        mov esi,0x7c47
00000028  E807000000        call 0x34
0000002D  EBD6              jmp short 0x5
0000002F  E9CC83FFFF        jmp 0xffff8400
00000034  8A06              mov al,[esi]
00000036  46                inc esi
00000037  3C00              cmp al,0x0
00000039  7403              jz 0x3e
0000003B  EE                out dx,al
0000003C  EBF6              jmp short 0x34
0000003E  C3                ret
0000003F  68656C6C6F        push dword 0x6f6c6c65
00000044  0D0A00776F        or eax,0x6f77000a
00000049  726C              jc 0xb7
0000004B  64                fs
0000004C  0D                db 0x0d
0000004D  0A00              or al,[eax]
```

### Result of this sample.
```
$ ./emux86 -q tests/select.bin
>h
hello
>w
world
>q


end of program.

EAX = 00000071
ECX = 00000000
EDX = 000003f8
EBX = 00000000
ESP = 00007c00
EBP = 00000000
ESI = 00007c4f
EDI = 00000000
EIP = 00000000
```