.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %10000000000000000000000999999999999999999999999999999
		zjmp %:live
