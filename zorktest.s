.name ""
.comment ""

debt:		live %42				#5
			sti  r4,%:label,%1		#7
			add  r4,r12,r4			#5
			sub  r10,r11,r10		#5
			zjmp %:init				#3
			fork %:debt
			live %3
level0:		fork %:level10
level11:	live %4
			fork %:level111

level110:	live %42
			ldi  %8,%:code,r15		#set des octets 9-12
			ld   %-186,r14			#=$A-6-8
			ld   %0,r2
			zjmp  %:label

