# emu-x86
A emulator for 80386 cpu that is x86 architecture as 32bit.

# Requirements

This emulator assumes 32bit, so it requires a binary for 32bit. This project includes a gcc for i386 under tools directory. To make a 32bit binary of test code, please use it.

# Usage

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
# Sample

### input source code as c lang.
```c
int abs(int i) {
    if (i >= 0) {
        return i;
    } else {
        return -i;
    }
}

int main(void) {
    return abs(-3);
}
```

### assembler of c code.
```asm
$ ndisasm -b 32 test.bin
00000000  E81A000000        call 0x1f
00000005  E9F683FFFF        jmp 0xffff8400
0000000A  55                push ebp
0000000B  89E5              mov ebp,esp
0000000D  837D0800          cmp dword [ebp+0x8],byte +0x0
00000011  7805              js 0x18
00000013  8B4508            mov eax,[ebp+0x8]
00000016  EB05              jmp short 0x1d
00000018  8B4508            mov eax,[ebp+0x8]
0000001B  F7D8              neg eax
0000001D  5D                pop ebp
0000001E  C3                ret
0000001F  55                push ebp
00000020  89E5              mov ebp,esp
00000022  B803000000        mov eax,0x3
00000027  5D                pop ebp
00000028  C3                ret
```

### Result of this sample.
```
$ ./emux86 tests/test.bin
EIP = 7C00, Code = E8
EIP = 7C1F, Code = 55
EIP = 7C20, Code = 89
EIP = 7C22, Code = B8
EIP = 7C27, Code = 5D
EIP = 7C28, Code = C3
EAX = 00000003
ECX = 00000000
EDX = 00000000
EBX = 00000000
ESP = 00007c00
EBP = f3558260
ESI = 00000000
EDI = 00000000
EIP = f3558260
```