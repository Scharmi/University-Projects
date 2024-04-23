global  inverse_permutation			
inverse_permutation:
	dec 	rdi				;Dekrementujemy n, żeby jednym rozkazem sprawdzić czy n jest w przedziale od 1 do INT_MAX + 1 włącznie.
	cmp 	rdi, 0x7FFFFFFF			;Sprawdzamy czy n jest w przedziale od 1 do INT_MAX + 1 włącznie.
	ja 	.returnFalse			;Jeśli nie to zwracamy false.
	mov 	r8, 0x7FFFFFFF			;Przypisujemy do r8 INT_MAX (jedynki na 31 najmłodszych bitach).
	mov 	r9, 0x80000000			;Przypisujemy do r9 jedynkę na najstarszym bicie (INT_MAX + 1).
	mov 	rdx, 0				;Ustawiamy iterator na 0.
.checkGivenValues:				;Sprawdzamy czy elementy mieszczą się w przedziale od 0 do n - 1.
	cmp 	rdx, rdi			;sprawdzamy czy iterator jest równy n.
	jg 	.zeroBeforeRepeatCheck		;jeśli tak to zwracamy true.
	cmp	[rsi + rdx * 4], edi		;Sprawdzamy czy element tablicy jest mniejszy niż n.
	ja 	.returnFalse			;Jeśli tak to zwracamy false.
	cmp 	dword [rsi + rdx * 4], 0	;sprawdzamy czy element tablicy jest nieujemny.
	jl 	.returnFalse			;Jeśli nie to zwracamy false.
	inc 	rdx				;Inkrementujemy iterator.
	jmp 	.checkGivenValues		;Powtarzamy.
.zeroBeforeRepeatCheck:
	mov 	rdx, 0				
.repeatCheck:					;Sprawdzamy czy wartości w tablicy są parami różne.
	cmp 	rdx, rdi			;Sprawdzamy czy iterator jest równy n.
	jg 	.zeroBeforeInversing		;Jeśli tak to przechodzimy do odwracania.
	mov	ecx, [rsi + rdx * 4]		;Przepisujemy wartość z tablicy do ecx.
	and 	ecx, r8d			;Zerujemy najstarszy bit dla tej wartości (bo mógł zostać ustawiony na 1 przez or kilka linijek niżej).
	cmp 	dword [rsi + rcx * 4], 0	;Sprawdzamy czy najstarszy bit w miejscu o indeksie wskazanym przez wartość sczytaną do ecx 
						;jest ustawiony na 1.
	jl 	.zeroBeforeFixing		;Jeśli tak to znaczy że w tablicy był już element o wartości takiej jak ecx, 
						;więc przechodzimy do naprawy tablicy i zwrócenia false.
	or	[rsi + rcx * 4], r9d		;Oznaczamy wartość w tablicy jako odwiedzoną ustawiając najstarszy bit na 1 
						;(jako że wartości są dodatnie i typu int to ten bit zawsze jest początkowo zerem.
	inc 	rdx				;Inkrementujemy iterator.
	jmp 	.repeatCheck			;Powtarzamy.
.zeroBeforeFixing:
	mov 	rdx, 0				
.fixGivenValues: 
	cmp 	rdx, rdi			;Sprawdzamy czy iterator jest równy n.
	jg 	.returnFalse			;Jeśli tak to kończymy pętlę i zwracamy false.
	and 	[rsi + rdx * 4], r8d		;Zerujemy najstarszy bit w tablicy (bo mógł zostać ustawiony na 1 przy sprawdzaniu poprawności).
	inc 	rdx				;Inkrementujemy iterator.
	jmp 	.fixGivenValues			;Powtarzamy.
.returnFalse:
	mov 	rax, 0
	ret
.zeroBeforeInversing:
	mov 	rdx, 0				
	jmp 	.inversing
.increaseIterator:		
	inc 	rdx				;Inkrementujemy iterator.
.inversing:					;Odwracamy permutację w następujący sposób:
						;Iterujemy po kolejnych wyrazach i za każdym razem odwracamy cykl w którym się znajdujemy,
						;O ile nie został on już wcześniej odwrócony.
	cmp 	rdx, rdi			;Sprawdzamy czy iterator jest równy n.
	jg 	.returnTrue			;Jeśli tak to znaczy że skończyliśmy odwracanie i zwracamy true.
.cycleLoop:					;Przechodzimy po cyklu w permutacji i go odwracamy
	cmp 	dword [rsi + rdx * 4], 0	;sprawdzamy czy element tablicy był już odwiedzony
	jnl 	.increaseIterator		;Jeśli tak to przechodzimy do następnego elementu
	and 	[rsi + rdx * 4], r8d		;Zmieniając najstarszy bit na 0 (po tym jak przy sprawdzaniu poprawności ustawiliśmy go na 1) 
						;oznaczamy element jako odwiedzony
	mov 	rcx, rdx			;W rcx wpisujemy aktualny indeks, żeby przekazać go do rax (bo zmieniamy rdx)
	mov 	edx, dword [rsi + rdx * 4]	;Zmieniamy wartość iteratora na następną wartość w cyklu
	mov 	[rsi + rcx * 4], eax		;Zmieniamy wartość w tablicy na poprzedni indeks
	mov 	rax, rcx			;Przepisujemy indeks z rcx do rax (z rax korzystamy linijkę wyżej)	
	cmp 	dword [rsi + rdx * 4], 0	;Sprawdzamy czy dochodzimy z powrotem do pierwszego elementu w cyklu
						;Jeśli tak to zmieniamy w nim wartość (za pomocą etykiety fillEndCycle, gdybyśmy tego 
						;nie zrobili to wartość nie zostałaby zmieniona jako że indeks ten był już odwiedzony i 
						;przeszkoczylibyśmy do zwiększania iteratora).
	jnl 	.fillEndCycle
	jmp 	.cycleLoop
.fillEndCycle:
	mov 	[rsi + rdx * 4], eax		;Zmieniamy wartość w pierwszym elemencie cyklu i przechodzimy do zwiększania iteratora.
	jmp 	.increaseIterator	
.returnTrue:
	mov 	rax, 1
	ret