.name "zork"
.comment "just a basic living prog"
		
l2: sti r1,r2,r3,r4
	and	r1,r2,r3
live:	live	%1
	zjmp	%:live

