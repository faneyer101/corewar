#st	r1, :ld+1
#a tester
#l2:		
#		sti:%live,:test
#
#		
#l2:	
.name "zork"
.comment "I'M ALIIIIVE"

l2:	
	stir1, :live , %1
#	and r1, %0, r1

t1:
t2:

live:	live %1
		zjmp %:live

ld2:	live	%:l2
	fork	%:t1
	# process qui dit live pour T2
	st	r1, :live
	ld	%-10, r2
	ld	%1, r3
