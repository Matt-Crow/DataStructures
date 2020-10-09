; general comments
;    sum references a named memory doubleword
;    count is in ECX
;
;    count := 0
;    sum := 500
;    while ((count <= 60) and (sum > 200))
;        subtract count from sum
;        add 5 to count
;    end while

; preprocessor directives
.586
.MODEL FLAT

; external files to link with

; stack configuration
.STACK 4096

; named memory allocation and initialization
.DATA
sum	     DWORD 500d
countMax DWORD 60d
sumMin   DWORD 200d

; names of procedures defined in other *.asm files in the project

; procedure code
.CODE
main	PROC
	mov ECX, 0d
    mov EBX, sumMin     ; can't do cmp with two named memory locations, so I need this

    checkLoopCondition: ; need this in case it shouldn't enter the loop at all
        cmp ECX, countMax
        ja endOfLoop
        cmp sum, EBX
        jbe endOfLoop
        jmp startOfWhileLoop
    startOfWhileLoop:
        sub sum, ECX
        add ECX, 5
        jmp checkLoopCondition

    endOfLoop:
        ; done looping
	mov EAX, 0
	ret
main	ENDP

END
