# breadwallet-core
SPV bitcoin C library with added BitCoinSV 

steps for compilation
I am compiling using clang 9 but I am sure that a more ancient version of the C compiler will work too

 - git clone git@github.com:edwardbr/breadwallet-core.git
 - git checkout bsv
 - git submodule init
 - git submodule update
 - make
 For btc
 - ./test
 For bch
 - ./test bch
 For bsv
 - ./test bsv
