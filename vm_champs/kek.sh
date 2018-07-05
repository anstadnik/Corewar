for file in `find ./champs/examples -type f -name "*.s"`
do
	echo ""
	echo $file
	echo "our asm: "
	./asm_dev $file
	echo "\n"
	echo "asm: "
	./asm $file
	echo "diff :"
	tmp=`echo $file | sed 's/\.s$//'`
	echo $tmp
	diff $tmp.co $tmp.cor
done
