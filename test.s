

.comment ".name"	
		.name    "
.name
		"

lol:
live %-42
live %42


#hehe:
#live %:hehe
haha:
	sti r1, 0, %:lol
	sti r15, %234532,r10
r10:
#live
	live %2
#store
	st r10, 0
	sti r10,0,r1

#bin
and r1, %10, r0

#load
	ld %10, r0
	lld %:r10, r10
	lldi 0,	%0, r1
	ldi r0, %4, r12
#fork zjmp
	fork %0
	lfork %0
	zjmp %100000
#aff
	aff r10
name:
.comment
