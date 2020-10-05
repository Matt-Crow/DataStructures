; general comments
; This is meant to emulate:
;   if(count > value){
;       count = 0;
;   }
; Where count is in AX,
; and value is a WORD in named memory
; both are signed

; preprocessor directives
.586
.MODEL FLAT

; external files to link with

; stack configuration
.STACK 4096

; named memory allocation and initialization
.DATA
value WORD -132d

; names of procedures defined in other *.asm files in the project

; procedure code
.CODE
main	PROC

	mov AX, 64d

    cmp AX, value
    jg ifBlock
    jmp endIfBlock ; skips over this line if AX > value
    ifBlock:
        mov AX, 0 ; the body of the original if
    	jmp endIfBlock
    endIfBlock:
    ; do nothing

	mov EAX, 0
	ret
main	ENDP

END
