;====================================================================
; Main.asm file generated by New Project wizard
;
; Created:   Di Mrz 16 2021
; Processor: 80C31
; Compiler:  ASEM-51 (Proteus)
;====================================================================

$NOMOD51
$INCLUDE (8051.MCU)

;====================================================================
; DEFINITIONS
;====================================================================
   
;====================================================================
; VARIABLES
;====================================================================

;====================================================================
; RESET and INTERRUPT VECTORS
;====================================================================

      ; Reset Vector
      org   0000h
      jmp   Main

;====================================================================
; CODE SEGMENT
;====================================================================

      org   0100h
      
      table:
      db 00000000b
      db 10000000b
      db 11000000b
      db 11100000b
      db 11110000b
      db 11111000b
      db 11111100b
      db 11111110b
      db 11111111b
      db 11111110b
      db 11111100b
      db 11111000b
      db 11110000b
      db 11100000b
      db 11000000b
      db 10000000b
      
Main:	

   MOV dptr, #table
   MOV P2, #0
   MOV R5, #0

   
   MOV R4, #16
Loop:
   MOV A, R5
   MOVC  A, @A+dptr
   MOV P2, A
   INC R5
   call zeit_2s
   DJNZ R4, Loop
   
   JMP Main
   
zeit_2s:
MOV R1, #16
a1:
   MOV R2, #250
a2:
   MOV R3, #250
   DJNZ R3, $
   DJNZ R2, a2
   DJNZ R1, a1

   RET
   
   
;====================================================================
      END