nasm -DN=2 -f elf64 -w+all -w+error -o core.o core.asm
gcc -c -Wall -Wextra -std=c17 -O2 -o test.o test.c
gcc -z noexecstack -o test core.o test.o -lpthread
size core.o
./test