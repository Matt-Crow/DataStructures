; general comments
;     sum references a named memory doubleword
;     count is the smallest register necessary for the loop and the calculations
;
;     sum := 0
;     for count goes from 1 to 51 by 5
;         add (count*count) to sum
;     end for

; preprocessor directives
.586
.MODEL FLAT

; external files to link with

; stack configuration
.STACK 4096

; named memory allocation and initialization
.DATA
sum	     DWORD 0d
limit    BYTE  51d

; names of procedures defined in other *.asm files in the project

; procedure code
.CODE
main	PROC
	mov CL, 1d              ; store count in low bits of C

    checkLoopCondition:     ; need this in case it shouldn't enter the loop at all
        cmp CL, limit
        jb startOfWhileLoop ; should it be jbe?
        jmp endOfLoop
    startOfWhileLoop:
        mov EAX, 0          ; zero-out the first 16 bits of A register...
        mov AL, CL
        mul CL              ; AX is now count * count
        add sum, EAX        ; ... as sum must be a DWORD, and I need to add AX
        add CL, 5d
        jmp checkLoopCondition

    endOfLoop:
        ; done looping
	mov EAX, 0
	ret
main	ENDP

END
