# breadwallet-core
SPV bitcoin C library with added BitCoinSV 

steps for compilation
I am compiling using clang 9 but I am sure that a more ancient version of the C compiler will work to

 - git clone https://github.com/edwardbr/breadwallet-core
 - git checkout bsv
 - git submodule init
 - git submodule update
 - make
 - ./test
