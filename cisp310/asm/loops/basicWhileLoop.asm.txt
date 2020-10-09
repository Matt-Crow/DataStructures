; general comments
;    sum references a named memory doubleword
;    count is in ECX
;
;    sum := 0
;    count := 1
;    while (sum < 1000)
;        add count to sum
;        add 1 to count
;    end while

; preprocessor directives
.586
.MODEL FLAT

; external files to link with

; stack configuration
.STACK 4096

; named memory allocation and initialization
.DATA
sum	  DWORD 0d
limit DWORD 1000d

; names of procedures defined in other *.asm files in the project

; procedure code
.CODE
main	PROC
	mov ECX, 1d
    mov EBX, limit

    checkLoopCondition:
        cmp sum, EBX
        jb startOfWhileLoop
        jmp endOfLoop
    startOfWhileLoop:
        add sum, ECX
        inc ECX
        jmp checkLoopCondition
    endOfLoop:
        ; done looping

	mov EAX, 0
	ret
main	ENDP

END
