mkdir build
cmake -G "Unix Makefiles" -B ./build -S ./
# cmake -G "Unix Makefiles" -B ./ -S ../ -DUSE_STATIC_LIB=ON

cd build && make -j32