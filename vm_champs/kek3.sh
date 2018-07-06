for file in `find ./champs/championships -type f -name "*.s"`
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
