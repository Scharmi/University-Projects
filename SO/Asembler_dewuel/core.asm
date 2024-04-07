global  core
section .bss
	values:   resq  N			;W tej tablicy trzymamy wartości przekazywane między wątkami
section .data
	requests: times N dq 0xffffffffffffffff ;W tej tablicy trzymamy informację o tym z który wątek chce się skomunikować z którym.
						;Po komunikacji ustawiana jest wartość odpowiadająca próbie komunikacji wątku z samym sobą
extern  get_value, put_value
section .text
core:	
	push 	rbp
	mov 	rbp, rsp
	push 	r12				;Zachowujemy poprzednie wartości rejestrów r12-r15 na stosie, żeby móc je przywrócić po zakończeniu działania funkcji
	push 	r13
	push 	r14
	push 	r15
	push 	rdi
	mov 	r12, rsi			;r12 to wskaźnik na aktualnie czytany znak
.readCharacter:
	xor 	rax, rax
	mov 	al, BYTE [r12]			;Wczytujemy znak i wywołujemy odpowiedni fragment kodu
	cmp 	al, 0				;Sprawdzamy czy dotarliśmy do końca napisu
	je 	.End
	cmp 	al, 'n'
	je 	.n
	cmp 	al, '+'
	je	.add
	cmp 	al, '*'
	je 	.multiply
	cmp 	al, '-'
	je 	.neg
	cmp 	al, 'B'
	je 	.B
	cmp 	al, 'C'
	je 	.C
	cmp 	al, 'D'
	je 	.D
	cmp 	al, 'E'	
	je 	.E
	cmp 	al, 'G'
	je 	.G
	cmp 	al, 'P'
	je 	.P
	cmp 	al, 'S'
	je 	.S
	jmp 	.putNumber			;Jeśli nie jest to żaden znak specjalny to jest to cyfra, więc przechodzimy do funkcji putNumber

.putNumber:
	sub 	rax, 48				;Zamieniamy znak na cyfrę
	push 	rax
	jmp	.nextChar

.add:	
	mov 	r15, QWORD [rsp]		;Zapisujemy pierwszą liczbę ze stosu
	add 	r15, QWORD [rsp + 8]		;Dodajemy pierwszą liczbę do drugiej na stosie
	add 	rsp, 16				;Usuwamy obie liczby ze stosu przesuwając wskaźnik stosu o 2 razy 8 bajtów
	push 	r15				;Dodajemy wynik
	jmp 	.nextChar
.multiply:
	mov 	r15, QWORD [rsp]		;Zapisujemy pierwszą liczbę ze stosu
	imul 	r15, QWORD [rsp + 8]		;Mnożymy pierwszą liczbę przez drugą na stosie
	add 	rsp, 16				;Usuwamy obie liczby ze stosu
	push 	r15				;Wrzucamy wynik na stos
	jmp 	.nextChar
.neg: 
	neg 	QWORD [rsp]
	jmp 	.nextChar
.n:
	push 	QWORD [rbp - 40]		;W tym miejscu zapisujemy numer wątku
	jmp 	.nextChar
.B:
	pop 	r15
	cmp	QWORD [rsp], 0
	je 	.nextChar
	add 	r12, r15		
	jmp 	.nextChar
.C:
	add 	rsp, 8				;Usuwamy wartość ze stosu przesuwając wskaźnik stosu o 8 bajtów
	jmp	.nextChar
.D:
	push 	QWORD [rsp]			;Kopiujemy wartość na szczycie stosu
	jmp 	.nextChar
.E:
	pop 	r15				;Zdejmujemy dwie wartości i zamieniamy je miejscami
	pop 	r14
	push 	r15
	push 	r14
	jmp 	.nextChar
.nextChar:
	inc 	r12				;Przechodzimy do następnego znaku
	jmp 	.readCharacter
.G:
	mov 	rdi, QWORD [rbp - 40]
	test 	rsp, 8
	jnz 	.Gshift	
	call 	get_value
	push 	rax
	jmp 	.nextChar
.Gshift:					;Jeśli stos nie jest podzielny przez 16 to musimy go przesunąć o 8 bajtów na czas wywołania funkcji get_value
	sub 	rsp, 8
	call 	get_value
	add 	rsp, 8
	push 	rax
	jmp 	.nextChar
.P:
	pop 	rsi
	mov 	rdi, QWORD [rbp - 40]
	test 	rsp, 8
	jnz	.Pshift
	call 	put_value
	jmp 	.nextChar
.Pshift:					;Jeśli stos nie jest podzielny przez 16 to musimy go przesunąć o 8 bajtów na czas wywołania funkcji put_value
	sub 	rsp, 8
	call 	put_value
	add 	rsp, 8
	jmp 	.nextChar
.S:
	pop 	r9				;r9 to numer  wątku z którym chcemy się komunikować
	mov 	r10, r9				;kopujemy numer wątku do r10 bo utracimy go przy xchg
	pop 	r13				;r13 to wartość do przekazania wątkowi
	mov 	r15, QWORD [rbp - 40]		;r15 to numer naszego wątku
	mov 	rdx, r15			;Kopiujemy numer naszego wątku do rdx bo utracimy go potem przy cmpxchg
	lea 	r8, [rel values]		
	lea 	r8, [r8 + r15 * 8]
	xchg    r13, QWORD [r8]			;Wstawiamy wartość ze stosu do globalnej tablicy values na pozycji odpowiadającej numerowi wątku;
						;Żeby umożliwić kolejnemu wątkowi pobranie tej wartości
	lea 	r14, [rel requests]             
	lea 	r14, [r14 + r15 * 8]
	xchg    r9, QWORD [r14]			;Wstawiamy do tablicy requests informację o tym, że nasz wątek jest gotowy do komunikacji
	lea 	r14, [rel requests]
.waitForThread:					;Czekamy aż drugi wątek będzie gotowy do komunikacji
	mov 	rax, r15
	lock 	\
	cmpxchg QWORD [r14 + r10 * 8], r15	;Czekamy aż w tablicy requests na pozycji indeksu wątku na który oczekujemy znajdzie się indeks naszego wątku
	jnz 	.waitForThread
	mov 	r15, rdx			;Przywracamy wartość r15 zmienioną linijkę wyżej
	mov 	r9, r10				;Przywracamy wartość r9 zmienioną w xchg	
	lea 	r8, [rel values]
	lea 	r8, [r8 + r9 * 8]		
	xchg    r11, QWORD [r8]			;Pobieramy wartość przekazaną przez drugi wątek z tablicy values
	push 	r11				;I wrzucamy ją na nasz stos
	lea 	r14, [rel requests]
	mov 	rdx, r9
	xchg 	QWORD [r14 + 8 * r9], rdx	;Zmieniamy wartość requests na pozycji indeksu wątku z którym się komunikowaliśmy na jego samego żeby zaznaczyć
						;że zakończyliśmy komunikację
.waitForFinishing:				;Czekamy aż drugi wątek weźmie naszą wartość z tablicy values i powiadomi nas o tym 
						;zmieniając wartość w tablicy requests na indeks naszego wątku
	mov 	rax, r15
	lock 	\
	cmpxchg QWORD [r14 + r15 * 8], r15
	jnz 	.waitForFinishing
	jmp 	.nextChar
.End:
	pop 	rax
	mov 	r12, QWORD [rbp - 8]		;Przywracamy wartości rejestrów r12-r15
	mov 	r13, QWORD [rbp - 16]
	mov 	r14, QWORD [rbp - 24]
	mov 	r15, QWORD [rbp - 32]
	mov 	rsp, rbp			;Przywracamy stos do stanu przed wywołaniem funkcji
	pop 	rbp
	ret
	
