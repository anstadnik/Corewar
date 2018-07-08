.name "Potator"
.comment "The beater"

beg:
	sti  r1,      %:live,   %1
	sti  r1,      %:hehehe, %2
	ld   :hehehe, r2
	ld   :fill,   r7
	ld   %0,      r6           # Change carry to 1

live:
	live %42
	fork %:prep_f
	fork %:prep_b
	fork %:fill
	zjmp %:live


prep_b:
	ld   %-8,     r4

attak_b:
	st   r2,      r4           # Write smth to a field
	sub  r4,      r5,       r4 # Decrement a counter
	xor  r3,      %-256,    r6
	zjmp %:prep_b
	ld   %0,      r6           # Change carry to 1
	zjmp %:attak_b


prep_f:
	ld   %1,      r3

attak_f:
	st   r2,      r3           # Write smth to a field
	add  r3,      r5,       r3 # Increment a counter
	xor  r3,      %256,     r6
	zjmp %:prep_f
	ld   %0,      r6           # Change carry to 1
	zjmp %:attak_f

                               # We will spam this
hehehe:
	ld   %43,     r1

fill:
	st   r7,      1
