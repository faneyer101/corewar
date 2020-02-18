.name "zork"
.comment "I'M ALIIIIVE"

#
# Warrior qui a gagne
# l'annee derniere
#     VOALA
#
#.name		"Celebration Funebre v0.99pl42"
#.comment	"Jour J"

		ld   %0,r3		
label:		zjmp %:avantdebt
		zjmp %0				# pour eviter ecrasement
						# de l'instruction suivante
code:


#l2:		sti r1, %:live, %1
#		and r1, %0, r1
#
#live:	live %1
#		zjmp %:live
