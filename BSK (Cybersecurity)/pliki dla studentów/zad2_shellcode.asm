[BITS 64]

global _start
section .text

; execve("/bin/sh", NULL, NULL)
_start:
    mov rax, 0x0068732f6e69622f
    push rax
    mov rdi, rsp
    xor esi, esi
    xor edx, edx
    mov eax, 0x3b
    syscall
