.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %165456464646456446464646456464646464646464646464564646456
		zjmp %:live
