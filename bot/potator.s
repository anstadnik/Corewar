.name "Potator"
.comment "The beater"

beg:
	sti  r1, %:live,  %1
	sti  r1, %:loop,  %1
	sti  r1, %:loop2, %1
	ld   %0, r2
	fork %:loop

live:
	live %42
	zjmp %:live

loop:
	live %42
	fork %:live
loop2:
	live %42
	fork %:loop
	zjmp %:loop
