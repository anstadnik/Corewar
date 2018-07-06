cp ~/COREWAR/cmake-build-debug/asm_dev ~/COREWAR/vm_champs/
for file in `find ./champs -maxdepth 1 -type f -name "*.s"`
do
	echo "our asm: "
	./asm_dev $file
	echo "asm: "
	./asm $file
	echo "diff :"
	tmp=`echo $file | sed 's/\.s$//'`
#	echo $tmp
	diff $tmp.co $tmp.cor
	echo "\n"
done
