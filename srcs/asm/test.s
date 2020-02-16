#st	r1, :ld1+1
#.name "zork"
#.comment "I'M ALIIIIVE"

#l2:	
#	sti r1, :live , %1
#	and r1, %0, r1

t1:fork

#live:	live %1
#		zjmp %:live

ld2:	live	%0
	fork	%:t1
	# process qui dit live pour T2
	st	r1, :live2-1
	ld	%-10, r2
	ld	%1, r3
