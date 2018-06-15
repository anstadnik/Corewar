.name "zork"
.comment "just a basic living prog"

l2:	lldi %-1,%1,r2
	st r2,0
	and	r2,%0,r2
live:	live	%1
	zjmp	%:live
