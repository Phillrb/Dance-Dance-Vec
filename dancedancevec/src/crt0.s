;;;
;;; Copyright 2006, 2007, 2008, 2009 by Brian Dominy <brian@oddchange.com>
;;; ported to Vectrex, 2013 by Frank Buss <fb@frank-buss.de>
;;; extended by Martin White 2014
;;;
;;; This file is part of GCC.
;;;
;;; GCC is free software; you can redistribute it and/or modify
;;; it under the terms of the GNU General Public License as published by
;;; the Free Software Foundation; either version 3, or (at your option)
;;; any later version.
;;;
;;; GCC is distributed in the hope that it will be useful,
;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.

;;; You should have received a copy of the GNU General Public License
;;; along with GCC; see the file COPYING3.  If not see
;;; <http://www.gnu.org/licenses/>.

	;; Include file defines which BIOS functions to switch on
	.include /crt.s/

	; Declare external for main()
	.globl _main

;#define __STACK_TOP 0xcbea

	; Declare all linker sections, and combine them into a single bank
	.bank prog
	.area .text  (BANK=prog)
;;;	.area .ctors (BANK=prog)

	; uncomment if we start using RAM
	.bank ram(BASE=0xc880,SIZE=0x36a,FSFX=_ram)
;;;	.area .data  (BANK=ram)
	.area .bss   (BANK=ram)


	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;;
	;;; cartridge init block
	;;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	.area	.text
	.ascii "g GCE 2015"				; cartrige id and year
	.byte 0x80						; string end
	.word music
	.byte 0xf8, 0x50, 0x20, -0x60	; height, width, rel y, rel x
	.ascii "DANCE DANCE VEC"		; game title
	.byte 0x80						; string end
	.byte 0							; header end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;;
	;;; __start : Entry point to the program
	;;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	.area	.text
	.globl __start
__start:

;;	;; copy .data and .bss areas to RAM
;;	ldx	#s_.data
;;	ldy	#0xc880
;;	ldb	#0xd
;;copyData:
;;	lda	,x+
;;	sta	,y+
;;	decb
;;	bne	copyData

	; start C program
	jmp	_main

music:
	.word   0xfee8
	.word   0xfeb6
	.byte   0x0, 0x80
	.byte   0x0, 0x80

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; General utility functions...
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.if d_RESET_0_REF
	.globl _reset0Ref
_reset0Ref:
	pshs	a, b, x, dp
	lda		#0xd0		; required input values for the positd executive subroutine:
	tfr		a, dp		; DP = 0xd0
	jsr		0xf354
	puls	a, b, x, dp, pc
.endif

.if	d_WAIT_RECAL
	.globl _waitRecal
_waitRecal:
	pshs	x, dp
	lda		#0xd0		; required input values for the positd executive subroutine:
	tfr		a, dp		; DP = 0xd0
	jsr		0xf192
	puls	x, dp, pc
.endif

;; input from C compiler:
;; - 8-bit argument in register b
.if d_INTENS_A
	.globl _intensA
_intensA:
	pshs	a, b, dp	; save registers
	lda		#0xd0		; required input values for the intens executive subroutine:
	tfr		a, dp		; DP = 0xd0
	tfr		b, a		; a = intensity
	jsr		0xf2ab
	puls	a, b, dp, pc	; restore registers and PC (=return)
.endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Delays...
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Numbered delays require no parameters from C
.if d_DELAY_0
	.globl _delay0
_delay0:
	jsr		0xf579
	rts
.endif

.if d_DELAY_1
	.globl _delay1
_delay1:
	jsr		0xf575
	rts
.endif

.if d_DELAY_2
	.globl _delay2
_delay2:
	jsr		0xf571
	rts
.endif

.if d_DELAY_3
	.globl _delay3
_delay3:
	jsr		0xf56d
	rts
.endif

.if d_DELAY_RTS
	.globl _delayRTS
_delayRTS:
	jsr		0xf57d
	rts
.endif

;; input from C compiler:
;; - 8-bit argument (unsigned int) count in register b
.if d_DELAY_B
	.globl _delayB
_delayB:
	jsr		0xf57a
	rts
.endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Move functions...
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; input from C compiler:
;; - first 8-bit argument x in register b
;; - second 8-bit argument y on stack
.if d_MOVETO_D
	.globl _moveToD
_moveToD:
	pshs	a, b, dp	; save registers
	lda		#0xd0		; required input values for the positd executive subroutine:
	tfr		a, dp		; DP = 0xd0
	lda		5, s		; a = y coordinate
	jsr		0xf312		; b = x coordinate
	puls	a, b, dp, pc	; restore registers and PC (=return)
.endif

;; input from C compiler:
;; - first 8-bit argument x in register b
;; - second 8-bit argument y on stack
.if d_MOVETO_D_7F
	.globl _moveToD7f
_moveToD7f:
	pshs	a, b, dp	; save registers
	lda		#0xd0		; required input values for the positd executive subroutine:
	tfr		a, dp		; DP = 0xd0
	lda		5, s		; a = y coordinate
	jsr		0xf2fc		; b = x coordinate
	puls	a, b, dp, pc	; restore registers and PC (=return)
.endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Rotate functions...
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; input from C compiler:
; - 1st 16-bit argument in register x: pointer to packet style list
; - 2nd 16-bit argument in register u: pointer to new packet style list
.if d_ROT_VL_MODE
	.globl _rotVLMode
_rotVLMode:
    puls    u
    puls    u
	pshs	a, b, x, dp, pc
	lda		#0xc8	;
	tfr		a, dp
	lda     #05
	jsr		0xf61f
	puls	a, b, x, dp, pc
.endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Draw functions...
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; input from C compiler:
;; - 1st 16-bit argument in register x: pointer to packet style list
;; - 2nd 8-bit argument in register b: zskip: 0 = skip zeroing integrator, 1 = zero integrators
.if d_DRAW_VLP
	.globl _drawVLp
_drawVLp:
	pshs	a, b, x, dp	; save registers
	lda		#0xd0		; required input values for the executive subroutine
	tfr		a, dp		; DP = 0xd0
	stb		0xc824		; ZSKIP
	jsr		0xf410
	puls	a, b, x, dp, pc	; restore registers and PC (=return)
.endif

.if d_DRAW_LINE_D
	.globl _drawLineD
_drawLineD:
	pshs	a, b, dp		; save registers
	clr		0xc823			; Set number of lines to 1 by clearing 0xC823
	lda		#0xd0			; set page to d0 (required for call)
	tfr		a, dp			;
	lda		5, s			; get a back from the stack = Y pos (rel)
	jsr		0xf3df
	puls	a, b, dp, pc
.endif

; input from C compiler:
; - 1st 16-bit argument in register x: pointer to packet style list
; - 2nd 8-bit argument in register b: zskip: 0 = skip zeroing integrator, 1 = zero integrators
.if d_DRAW_VLP_7F
	.globl _drawVLp7F
_drawVLp7F:
	pshs	a, b, x, dp	; save registers
	lda		#0xd0		; required input values for the executive subroutine
	tfr		a, dp		; DP = 0xd0
	stb		0xc824		; ZSKIP
	jsr		0xf408
	puls	a, b, x, dp, pc	; restore registers and PC (=return)
.endif

; input from C compiler:
; - 1st 16-bit argument in register x: pointer to packet style list
; - 2nd 8-bit argument in register b: zskip: 0 = skip zeroing integrator, 1 = zero integrators
.if d_DRAW_VLP_SCALE
	.globl _drawVLpScale
_drawVLpScale:
	pshs	a, b, x, dp	; save registers
	lda		#0xd0		; required input values for the executive subroutine
	tfr		a, dp		; DP = 0xd0
	stb		0xc824		; ZSKIP
	jsr		0xf40C
	puls	a, b, x, dp, pc	; restore registers and PC (=return)
.endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; String functions...
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; input from C compiler:
;; - 1st 8-bit value argument Y in register b
;; - 2nd 8-bit value argument X on stack
;; - 3rd pointer to string in register X
.if d_PRINT_STR_D
    .globl _printStrD
_printStrD:
    pshs    a, b, x, u, dp   ; save registers
    lda     #0xd0
    tfr     a, dp
    lda     7, s
    tfr     x, u
    jsr     0xf37a
    puls    a, b, x, u, dp, pc
.endif

;; input from C compiler:
;; - 1st pointer to string in register X
.if d_PRINT_STR
	.globl _printStr
_printStr:
	pshs	d, x, dp
	lda		#0xd0
	tfr		a, dp
	tfr		x, u
	jsr		0xf495
	puls	d, x, dp, pc
.endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; I/O functions...
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
.if d_JOY_ANALOG
	.globl _joyAnalog
_joyAnalog:
	pshs	a, b, x, dp
	lda		#0xd0
	tfr		a, dp
	jsr		0xf1f5
	puls	a, b, x, dp, pc
.endif

.if d_JOY_DIGITAL
	.globl _joyDigital
_joyDigital:
	pshs	a, b, x, dp
	lda		#0xd0		; required input values for the positd executive subroutine:
	tfr		a, dp		; DP = 0xd0
	jsr		0xf1f8
	puls	a, b, x, dp, pc
.endif

.if d_READ_BTN
	.globl _readButton
_readButton:
	pshs	b, x, dp
	jsr		0xf1ba
	puls	b, x, dp, pc
.endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Music functions...
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
.if d_DO_SOUND
	.globl _doSound
_doSound:
	pshs	a, b, x, u, dp
	lda		#0xd0		; required input values for the positd executive subroutine:
	tfr		a, dp		; DP = 0xd0
	jsr		0xf289
	puls	a, b, x, u, dp, pc
.endif

; input from C compiler:
; - 1st 16-bit argument in register x: pointer to music list
.if d_INIT_MUSIC_CHK
	.globl _initMusicCHK
_initMusicCHK:
	pshs	a, b, x, u, dp	; save registers
	lda		#0xc8		; required input values for the executive subroutine
	tfr		a, dp		; DP = 0xc8
	tfr		x, u
	jsr		0xf687
	puls	a, b, x, u, dp, pc	; restore registers and PC (=return)
.endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Score functions...
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; input from C compiler:
;; - first 16-bit argument score location in register X
;;
.if d_CLEAR_SCORE
	.globl _clearScore
_clearScore:
	pshs	d
	lda		#0x80
	sta		6, x
	jsr		0xf84f
	puls	d, pc
.endif

;; 1st 8-bit argument value in register b
;; 1st 16-bit argument score location in register X
;; 
;; Not sure what to do about U? BIOS mentions it contains BCD value of 8bit value
.if d_ADD_SCORE_A
	.globl _addScoreA
_addScoreA:
	pshs	d, u
	tfr		b, a
	jsr		0xf85e
	puls	d, u, pc
.endif
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	.end __start
