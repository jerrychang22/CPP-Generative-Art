export CC=/usr/bin/clang-9
export CXX=/usr/bin/clang++-9

cd $HOME/Code/CPP-Generative-Art/proj/cmake/
cmake .
#make VERBOSE=1
cmake --build .
