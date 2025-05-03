mkdir build
cmake -G "Unix Makefiles" -B ./build -S ./
# cmake -G "Unix Makefiles" -B ./ -S ../
cd build && make -j32