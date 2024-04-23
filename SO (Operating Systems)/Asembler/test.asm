; ----------------------------------------------------------------------------------------
; Checks if the given number is prime or not.
; mov, cmp, j, xor, or, and, test, loop, lea, inc, dec, shr, shl,
; ustawiam w rax i robię ret

; To assemble and run:
;
;     nasm -felf64 hello.asm && ld hello.o && ./a.out
; ----------------------------------------------------------------------------------------
global    dodaj
dodaj: 
.tuskacze
        mov     rax, rdi
        add     rax, rsi
        ret
.returnFalse
        mov     rax, 0
        ret

        
