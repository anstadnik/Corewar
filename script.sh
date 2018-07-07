# make; ./corewar -b 
if [ "$#" -gt 4 ] || [ "$#" -eq 0 ]; then
	echo "U r a stupid budda"
	return 1
else
	echo "Make"
	make;
	echo "Our corewar"
	./corewar -v 31 "$@" > ours.log
	echo "Original corewar"
	./executables/corewar -v 31 "$@" > orig.log
	echo "Compare"
	nvim -d ours.log orig.log
	# rm -i ours.log orig.log
	rm -f ours.log orig.log
fi
