mkdir build
# cmake -G "Unix Makefiles" -B ./build -S ./
# 打开/关闭宏 TEST_OPTION=OFF
cmake -G "Unix Makefiles" -B ./ -S ../ -DTEST_OPTION=ON

cd build && make -j32

