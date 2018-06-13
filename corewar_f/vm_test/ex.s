.name "zork"
.comment "just a basic living prog"

	sti	r1,%:live,%1
	and	r2,%0,r2
live:	live	%1
	zjmp	%:live
