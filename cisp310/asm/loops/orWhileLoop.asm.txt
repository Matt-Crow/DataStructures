; general comments
;    sum references a named memory doubleword
;    count is in ECX
;
;    sum := 0
;    count := 100
;    while ((sum < 1000) or (count >= 0))
;        add count to sum
;        subtract 1 from count
;    end while

; preprocessor directives
.586
.MODEL FLAT

; external files to link with

; stack configuration
.STACK 4096

; named memory allocation and initialization
.DATA
sum	     DWORD 0d
limit    DWORD 1000d
minCount DWORD 0d

; names of procedures defined in other *.asm files in the project

; procedure code
.CODE
main	PROC
	mov ECX, 100d
    mov EBX, limit

    checkLoopCondition: ; need this in case it shouldn't enter the loop at all
        cmp sum, EBX
        jl startOfWhileLoop
        cmp ECX, minCount
        jge startOfWhileLoop ; ECX can be negative, so I must use signed check
        jmp endOfLoop
    startOfWhileLoop:
        add sum, ECX
        dec ECX
        jmp checkLoopCondition

    endOfLoop:
        ; done looping
	mov EAX, 0
	ret
main	ENDP

END
