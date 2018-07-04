for file in `find ./champs/examples -type f -name "*.s"`
do
	echo "our asm: "
	./asm_dev $file
	echo "\n"
	echo "asm: "
	./asm $file
done
