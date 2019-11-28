
test:	clean
	clang -g -O0 -Wno-int-conversion -Wno-implicit-function-declaration -Wno-pointer-integer-compare -I. -I./support -I./vendor/secp256k1 -lpthread -lm -ldl -lbsd -o $@ bitcoin/*.c bcash/*.c ethereum/event/*.c support/*.c vendor/sqlite3/sqlite3.c
	#clang -g -O0 -Wno-implicit-function-declaration -I. -I./support -I./vendor/secp256k1 -o $@ bitcoin/*.c bcash/*.c ethereum/event/*.c support/*.c vendor/sqlite3/sqlite3.c

clean:
	rm -f *.o */*.o test

run:	test
	./test
