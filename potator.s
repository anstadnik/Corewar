.name "Potator"
.comment "The beater"

	sti	r1, %:live, %1 # Load player's number to live
:load
	# Change those loop labels to something normal
	ld :loop, r1
	ld :loop + 1, r2
	ld :loop + 2, r3
	ld :loop + 3, r4
	ld :loop + 4, r5
	ld :loop + 5, r6
	ld :loop + 6, r7
	ld :loop + 7, r8
	ld :loop + 8, r9
	ld :loop + 9, r10
	ld :loop + 10, r11
	ld :loop + 11, r12
	ld %1, r13
	ld %0, r15
	ld %12, r16

:loop
	add r15, r13, r15 # Increment counter
	add r16, r13, r16 # Increment counter
	sti r15, %:quine, %1 # Write parameters
	sti r16, %:quine, %2 # Write parameters
:quine
	st r42, 42 # Write code from register to map
	xor r16, %12, r14 # Check if u copied all the code
	zjmp %:next_iteration
	zjmp %:loop
:next_iteration
	ld %0 r15
	ld %12 r16
:live
	live %42
	fork %13
	zjmp %:loop
