; general comments
; This is meant to emulate:
;   if(a + b == c){
;       check = 'Y';
;   } else {
;       check = 'N';
;   }
;   Where check is AL,
;   a, b, and c are DWORDS in memory
;   they are all unsigned
;   and the sum is always mathematically correct

; preprocessor directives
.586
.MODEL FLAT

; external files to link with

; stack configuration
.STACK 4096

; named memory allocation and initialization
.DATA
_a DWORD 3d
_b DWORD 4d
_c DWORD 5d

; names of procedures defined in other *.asm files in the project

; procedure code
.CODE
main	PROC

	mov EBX, _a
	add EBX, _b ; EBX now holds a + b

    cmp EBX, _c
    je yesBlock
    jmp noBlock
    yesBlock:
        mov AL, 'Y'
        jmp endBlock
    noBlock:
        mov AL, 'N'
        jmp endBlock
    endBlock:
        ; done

	mov EAX, 0
	ret
main	ENDP

END
