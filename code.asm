TITLE PGMx.x: ASSEMLY(8086) INTERMIDIATE CODE GENERATED(without PeepHole optimization) FOR C PROGRAM PROVIDED

.MODEL SMALL
.STACK 100H
.DATA
	aula1 dw ?
	foo_FunRetVar dw ?
	xx3 dw ?
	yy3 dw ?
	fib_FunRetVar dw ?
	n4 dw ?
	t0 dw ?
	t1 dw ?
	t2 dw ?
	t3 dw ?
	t4 dw ?
	t5 dw ?
	i4 dw ?
	t6 dw ?
	t7 dw ?
	t8 dw ?
	t9 dw ?
	t10 dw ?
	t11 dw ?
	t12 dw ?
	t13 dw ?
	t14 dw ?
	t15 dw ?
	t16 dw ?
	t17 dw ?
	t18 dw ?
	t19 dw ?
	t20 dw ?
	fibRec_FunRetVar dw ?
	n6 dw ?
	t21 dw ?
	t22 dw ?
	t23 dw ?
	t24 dw ?
	t25 dw ?
	t26 dw ?
	t27 dw ?
	t28 dw ?
	t29 dw ?
	gcd_FunRetVar dw ?
	x7 dw ?
	y7 dw ?
	t30 dw ?
	t31 dw ?
	t32 dw ?
	t33 dw ?
	main_FunRetVar dw ?
	t34 dw ?
	t35 dw ?
	t36 dw ?
	t37 dw ?
	t38 dw ?
	t39 dw ?
	t40 dw ?
	t41 dw ?
	var8 dw ?
	t42 dw ?
	t43 dw ?
	t44 dw ?
	t45 dw ?
	t46 dw ?
	t47 dw ?
	t48 dw ?
	t49 dw ?
	t50 dw ?
	t51 dw ?
	t52 dw ?
	t53 dw ?
	t54 dw ?
	t55 dw ?
	t56 dw ?
	t57 dw ?
	t58 dw ?
	t59 dw ?
	t60 dw ?
	t61 dw ?
	t62 dw ?
	t63 dw ?
	t64 dw ?
	t65 dw ?
	t66 dw ?
	t67 dw ?
	t68 dw ?
	t69 dw ?
	t70 dw ?
	t71 dw ?
	t72 dw ?
	t73 dw ?
	t74 dw ?
	t75 dw ?
	t76 dw ?
	t77 dw ?
	t78 dw ?
	t79 dw ?
	t80 dw ?
	t81 dw ?
	t82 dw ?
	t83 dw ?
	t84 dw ?
	t85 dw ?
	t86 dw ?
	t87 dw ?
	t88 dw ?
	t89 dw ?
	t90 dw ?
	t91 dw ?
	t92 dw ?
	t93 dw ?
	t94 dw ?
	t95 dw ?
	t96 dw ?
	t97 dw ?
	i8 dw ?
	j8 dw ?
	t98 dw ?
	t99 dw ?
	t100 dw ?
	t101 dw ?
	t102 dw ?
	t103 dw ?
	t104 dw ?
	t105 dw ?
	t106 dw ?
	t107 dw ?
	g11 dw ?
	t108 dw ?
	t109 dw ?
	t110 dw ?
	glb1 dw 100 dup(?)
	ara4 dw 100 dup(?)
	arr8 dw 20 dup(?)
.CODE
foo PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	MOV AX, aula1
	CALL PRINTLN
RETURN_LABEL_foo:
	POP DX
	POP CX
	POP BX
	POP AX
	ret
foo ENDP

fooa PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH xx3
	PUSH yy3
RETURN_LABEL_fooa:
	POP yy3
	POP xx3
	POP DX
	POP CX
	POP BX
	POP AX
	ret
fooa ENDP

fib PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH n4
	PUSH i4
	MOV t0, 0
	MOV BX, t0
	ADD BX, BX
	MOV t1, BX
	MOV t2, 0
	MOV AX, t2
	MOV BX, t1
	MOV ara4[BX], AX
	MOV t3, 1
	MOV BX, t3
	ADD BX, BX
	MOV t4, BX
	MOV t5, 1
	MOV AX, t5
	MOV BX, t4
	MOV ara4[BX], AX
	MOV t6, 2
	MOV AX, t6
	MOV i4, AX
L2:
	MOV AX, i4
	CMP AX, n4
	JLE L0
	MOV t7, 0
	JMP L1
L0:
	MOV t7, 1
L1:
	MOV AX, t7
	CMP AX, 0
	JE L3
	MOV BX, i4
	ADD BX, BX
	MOV t9, BX
	MOV t10, 1
	MOV AX, i4
	SUB AX, t10
	MOV t11, AX
	MOV BX, t11
	ADD BX, BX
	MOV t12, BX
	MOV AX, ara4[BX]
	MOV t13, AX
	MOV t14, 2
	MOV AX, i4
	SUB AX, t14
	MOV t15, AX
	MOV BX, t15
	ADD BX, BX
	MOV t16, BX
	MOV AX, ara4[BX]
	MOV t17, AX
	MOV AX, t13
	ADD AX, t17
	MOV t18, AX
	MOV AX, t18
	MOV BX, t9
	MOV ara4[BX], AX
	MOV AX, i4
	MOV t8, AX
	INC i4
	JMP L2
L3:
	MOV BX, n4
	ADD BX, BX
	MOV t19, BX
	MOV AX, ara4[BX]
	MOV t20, AX
	MOV AX, t20
	MOV fib_FunRetVar, AX
	JMP RETURN_LABEL_fib
RETURN_LABEL_fib:
	POP i4
	POP n4
	POP DX
	POP CX
	POP BX
	POP AX
	ret
fib ENDP

fibRec PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH n6
	MOV t21, 1
	MOV AX, n6
	CMP AX, t21
	JLE L4
	MOV t22, 0
	JMP L5
L4:
	MOV t22, 1
L5:
	MOV AX, t22
	CMP AX, 0
	JE L6
	MOV AX, n6
	MOV fibRec_FunRetVar, AX
	JMP RETURN_LABEL_fibRec
L6:
	MOV t23, 1
	MOV AX, n6
	SUB AX, t23
	MOV t24, AX
	MOV AX, t24
	MOV n6, AX
	CALL fibRec
	MOV AX, fibRec_FunRetVar
	MOV t25, AX
	MOV t26, 2
	MOV AX, n6
	SUB AX, t26
	MOV t27, AX
	MOV AX, t27
	MOV n6, AX
	CALL fibRec
	MOV AX, fibRec_FunRetVar
	MOV t28, AX
	MOV AX, t25
	ADD AX, t28
	MOV t29, AX
	MOV AX, t29
	MOV fibRec_FunRetVar, AX
	JMP RETURN_LABEL_fibRec
RETURN_LABEL_fibRec:
	POP n6
	POP DX
	POP CX
	POP BX
	POP AX
	ret
fibRec ENDP

gcd PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH x7
	PUSH y7
	MOV t30, 0
	MOV AX, y7
	CMP AX, t30
	JE L7
	MOV t31, 0
	JMP L8
L7:
	MOV t31, 1
L8:
	MOV AX, t31
	CMP AX, 0
	JE L9
	MOV AX, x7
	MOV gcd_FunRetVar, AX
	JMP RETURN_LABEL_gcd
	JMP L10
L9:
	MOV AX, x7
	MOV BX, y7
	MOV DX, 0
	DIV BX
	MOV t32, DX
	MOV AX, y7
	MOV x7, AX
	MOV AX, t32
	MOV y7, AX
	CALL gcd
	MOV AX, gcd_FunRetVar
	MOV t33, AX
	MOV AX, t33
	MOV gcd_FunRetVar, AX
	JMP RETURN_LABEL_gcd
L10:
RETURN_LABEL_gcd:
	POP y7
	POP x7
	POP DX
	POP CX
	POP BX
	POP AX
	ret
gcd ENDP

main PROC
	MOV AX, @DATA
	MOV DS, AX

	CALL foo
	MOV AX, foo_FunRetVar
	MOV t34, AX
	MOV t35, 44
	MOV t36, 4
	MOV AX, t35
	MOV BX, t36
	MOV DX, 0
	DIV BX
	MOV t37, AX
	MOV t38, 45
	MOV t39, 5
	MOV AX, t38
	MOV BX, t39
	MOV DX, 0
	DIV BX
	MOV t40, AX
	MOV AX, t37
	MOV xx3, AX
	MOV AX, t40
	MOV yy3, AX
	CALL fooa
	MOV t41, AX
	MOV t42, 0
	MOV BX, t42
	ADD BX, BX
	MOV t43, BX
	MOV t44, 10
	MOV AX, t44
	MOV BX, t43
	MOV arr8[BX], AX
	MOV t45, 0
	MOV BX, t45
	ADD BX, BX
	MOV t46, BX
	MOV AX, arr8[BX]
	MOV t47, AX
	MOV AX, t47
	MOV var8, AX
	MOV AX, var8
	CALL PRINTLN
	MOV t48, 1
	MOV BX, t48
	ADD BX, BX
	MOV t49, BX
	MOV t50, 0
	MOV BX, t50
	ADD BX, BX
	MOV t51, BX
	MOV AX, arr8[BX]
	MOV t52, AX
	MOV AX, t52
	MOV BX, t49
	MOV arr8[BX], AX
	MOV t53, 1
	MOV BX, t53
	ADD BX, BX
	MOV t54, BX
	MOV AX, arr8[BX]
	MOV t55, AX
	MOV AX, t55
	MOV var8, AX
	MOV AX, var8
	CALL PRINTLN
	MOV t56, 2
	MOV AX, t56
	MOV var8, AX
	MOV BX, var8
	ADD BX, BX
	MOV t57, BX
	MOV t58, 1
	MOV AX, var8
	SUB AX, t58
	MOV t59, AX
	MOV BX, t59
	ADD BX, BX
	MOV t60, BX
	MOV AX, arr8[BX]
	MOV t61, AX
	MOV t62, 2
	MOV AX, var8
	SUB AX, t62
	MOV t63, AX
	MOV BX, t63
	ADD BX, BX
	MOV t64, BX
	MOV AX, arr8[BX]
	MOV t65, AX
	MOV AX, t61
	ADD AX, t65
	MOV t66, AX
	MOV AX, t66
	MOV BX, t57
	MOV arr8[BX], AX
	MOV BX, var8
	ADD BX, BX
	MOV t67, BX
	MOV AX, arr8[BX]
	MOV t68, AX
	MOV AX, t68
	MOV var8, AX
	MOV AX, var8
	CALL PRINTLN
	MOV t69, 2
	MOV BX, t69
	ADD BX, BX
	MOV t70, BX
	MOV AX, arr8[BX]
	MOV t71, AX
	MOV t72, 1
	MOV BX, t72
	ADD BX, BX
	MOV t73, BX
	MOV AX, arr8[BX]
	MOV t74, AX
	MOV AX, t71
	ADD AX, t74
	MOV t75, AX
	MOV t76, 0
	MOV BX, t76
	ADD BX, BX
	MOV t77, BX
	MOV AX, arr8[BX]
	MOV t78, AX
	MOV AX, t75
	ADD AX, t78
	MOV t79, AX
	MOV AX, t79
	ADD AX, var8
	MOV t80, AX
	MOV AX, t80
	MOV var8, AX
	MOV AX, var8
	CALL PRINTLN
	MOV t81, 5
	MOV AX, t81
	MOV var8, AX
	MOV AX, var8
	MOV n4, AX
	CALL fib
	MOV AX, fib_FunRetVar
	MOV t82, AX
	MOV AX, t82
	MOV var8, AX
	MOV AX, var8
	CALL PRINTLN
	MOV t83, 6
	MOV AX, t83
	MOV n4, AX
	CALL fib
	MOV AX, fib_FunRetVar
	MOV t84, AX
	MOV AX, t84
	MOV var8, AX
	MOV AX, var8
	CALL PRINTLN
	MOV t85, 0
	MOV AX, t85
	MOV var8, AX
L13:
	MOV t86, 10
	MOV AX, var8
	CMP AX, t86
	JL L11
	MOV t87, 0
	JMP L12
L11:
	MOV t87, 1
L12:
	MOV AX, t87
	CMP AX, 0
	JE L14
	MOV BX, var8
	ADD BX, BX
	MOV t88, BX
	MOV AX, var8
	ADD AX, var8
	MOV t89, AX
	MOV t90, 2
	MOV AX, t89
	MOV BX, t90
	MOV DX, 0
	DIV BX
	MOV t91, AX
	MOV AX, t91
	MOV BX, t88
	MOV glb1[BX], AX
	MOV BX, var8
	ADD BX, BX
	MOV t92, BX
	MOV AX, glb1[BX]
	MOV t93, AX
	MOV BX, var8
	ADD BX, BX
	MOV t94, BX
	MOV AX, glb1[BX]
	MOV t95, AX
	MOV AX, t93
	MOV BX, t95
	MUL BX
	MOV t96, AX
	MOV AX, t96
	MOV aula1, AX
	MOV AX, var8
	MOV t97, AX
	INC var8
	MOV AX, aula1
	CALL PRINTLN
	JMP L13
L14:
	MOV t98, 0
	MOV AX, t98
	MOV var8, AX
	MOV t99, 0
	MOV AX, t99
	MOV i8, AX
L21:
	MOV t100, 6
	MOV AX, i8
	CMP AX, t100
	JL L15
	MOV t101, 0
	JMP L16
L15:
	MOV t101, 1
L16:
	MOV AX, t101
	CMP AX, 0
	JE L22
	MOV t103, 1
	MOV AX, i8
	ADD AX, t103
	MOV t104, AX
	MOV AX, t104
	MOV j8, AX
L19:
	MOV t105, 6
	MOV AX, j8
	CMP AX, t105
	JL L17
	MOV t106, 0
	JMP L18
L17:
	MOV t106, 1
L18:
	MOV AX, t106
	CMP AX, 0
	JE L20
	MOV AX, i8
	MOV x7, AX
	MOV AX, j8
	MOV y7, AX
	CALL gcd
	MOV AX, gcd_FunRetVar
	MOV t108, AX
	MOV AX, var8
	ADD AX, t108
	MOV t109, AX
	MOV AX, t109
	MOV var8, AX
	MOV AX, j8
	MOV t107, AX
	INC j8
	JMP L19
L20:
	MOV AX, i8
	MOV t102, AX
	INC i8
	JMP L21
L22:
	MOV AX, var8
	CALL PRINTLN
	MOV t110, 0
	MOV AX, t110
	MOV main_FunRetVar, AX
	JMP RETURN_LABEL_main
RETURN_LABEL_main:

	MOV AH, 4CH
	INT 21H
main ENDP

PRINTLN PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	CMP AX,0
	JGE BEGIN
	PUSH AX
	MOV DX, '-'
	MOV AH, 2
	INT 21H
	POP AX
	NEG AX
BEGIN:
	XOR CX, CX
	MOV BX, 10
REPEAT:
	XOR DX, DX
	DIV BX
	PUSH DX
	INC CX
	OR AX, AX
	JNE REPEAT
	MOV AH, 2
PRINT_LOOP:
	POP DX
	ADD DX, 30H
	INT 21H
	LOOP PRINT_LOOP
	MOV AH, 2
	MOV DX, 10
	INT 21H
	MOV DX, 13
	INT 21H
	POP DX
	POP CX
	POP BX
	POP AX
	ret
PRINTLN ENDP
		END MAIN

