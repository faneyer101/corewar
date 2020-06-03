.name		"Docker tamalou"
.comment	"j'ai bobola"

start:	ld		%10		,r2
ld		%1		,r3
ld		%66343	,r5
ld		%-20 	,r4
st		r5		,r4
live	%42
fork	%:boucle1
live	%42
loop:	st		r1		,6
live	%42
st		r1		,6
live	%42
st		r1		,6
live	%42
st		r1		,6
live	%42
st		r1		,6
live	%42
st		r1		,6
live	%42
add		r16		,r16	,r16
fork	%:boucle2
zjmp	%:loop

boucle1:
live	%42
st		r2, -511
st		r2, -505
st		r2, -499
st		r2, -493
st		r2, -487
st		r2, -481
st		r2, -475
st		r2, -469
zjmp	%:boucle1

boucle2:
live	%42
st		r2, -471
st		r2, -465
st		r2, -459
st		r2, -453
st		r2, -447
st		r2, -441
st		r2, -435
zjmp	%:boucle2
