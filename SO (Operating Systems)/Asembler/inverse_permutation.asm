global  inverse_permutation			;Gets a number and a pointer to an array and returns the first element of array
inverse_permutation:
	dec 	rdi
	cmp 	rdi, 0x7FFFFFFF			;sprawdzamy czy n jest w przedziale od 1 do INT_MAX + 1 włacznie
	ja 	.returnFalse
	mov 	r8, 0x7FFFFFFF			;przypisujemy do r8 INT_MAX (jedynki na 31 najmłodszych bitach)
	mov 	r9, 0x80000000			;przypisujemy do r9 jedynkę na najstarszym bicie
	mov 	rdx, 0				;ustawiamy iterator na 0
.checkGivenValues:				;sprawdzamy czy elementy mieszczą się w przedziale od 0 do n - 1
	cmp 	rdx, rdi			;sprawdzamy czy iterator jest równy n
	jg 	.zeroBeforeRepeatCheck		;jeśli tak to zwracamy true
	cmp	[rsi + rdx * 4], edi		;sprawdzamy czy element tablicy jest w przedziale od 0 do n - 1
	ja 	.returnFalse
	cmp 	dword [rsi + rdx * 4], 0	;sprawdzamy czy element tablicy jest nieujemny
	jl 	.returnFalse
	inc 	rdx				;inkrementujemy iterator
	jmp 	.checkGivenValues		;powtarzamy
.zeroBeforeRepeatCheck:
	mov 	rdx, 0				;ustawiamy iterator na 0
.repeatCheck:					;sprawdzamy czy elementy tablicy są różne
	cmp 	rdx, rdi			;sprawdzamy czy iterator jest równy n
	jg 	.zeroBeforeInversing			;jeśli tak to zwracamy false
	mov	ecx, [rsi + rdx * 4]		;przypisujemy do ecx element tablicy
	and 	ecx, r8d			;zerujemy najstarszy bit w tablicy
	cmp 	dword [rsi + rcx * 4], 0	;sprawdzamy czy element tablicy jest nieujemny
	jl 	.zeroBeforeFixing
	or	[rsi + rcx * 4], r9d		;ustawiamy najstarszy bit w tablicy
	inc 	rdx				;inkrementujemy iterator
	jmp 	.repeatCheck			;powtarzamy
.zeroBeforeFixing:
	mov 	rdx, 0				;ustawiamy iterator na 0
.fixGivenValues: 
	cmp 	rdx, rdi			;sprawdzamy czy iterator jest równy n
	jg 	.returnFalse			;jeśli tak to zwracamy false
	and 	[rsi + rdx * 4], r8d		;zerujemy najstarszy bit w tablicy
	inc 	rdx				;inkrementujemy iterator
	jmp 	.fixGivenValues			;powtarzamy
.returnFalse:
	mov 	rax, 0
	ret
.zeroBeforeInversing:
	mov 	rdx, 0				;ustawiamy iterator na 0
	jmp 	.inversing
.increaseIterator:	
	inc 	rdx				;inkrementujemy iterator
.inversing:
	cmp 	rdx, rdi			;sprawdzamy czy iterator jest równy n
	jg 	.returnTrue			;jeśli tak to zwracamy true
.cycleLoop:
	cmp 	dword [rsi + rdx * 4], 0	;sprawdzamy czy element tablicy był już odwiedzony
	jnl 	.increaseIterator
	and 	[rsi + rdx * 4], r8d		;zerujemy najstarszy bit w tablicy
	mov 	rcx, rdx
	mov 	edx, dword [rsi + rdx * 4]	
	mov 	[rsi + rcx * 4], eax
	mov 	rax, rcx
	cmp 	dword [rsi + rdx * 4], 0
	jnl 	.fillEndCycle
	jmp 	.cycleLoop
.fillEndCycle:
	mov 	[rsi + rdx * 4], eax
	jmp 	.increaseIterator	
.returnTrue:
	mov 	rax, 1
	ret