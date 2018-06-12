.name "zork"
.comment "just a basic living prog"

l2:	and	r2,%0,r2
	sti	r1,%:live,%0
live:	live	%1
	zjmp	%:live
