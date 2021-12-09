mkdir build && mkdir bin
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .
cd ../bin
./json_test
