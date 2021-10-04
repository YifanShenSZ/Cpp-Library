for directory in utility_file utility_matrix utility_heap utility_UnionFind utility_LRUCache utility_LFUCache \
linalg; do
    echo
    echo "Entre "$directory
    cd $directory
    # build
    if [ -d build ]; then rm -r build; fi
    mkdir build
    cd build
    cmake -DCMAKE_C_COMPILER=icc -DCMAKE_CXX_COMPILER=icpc ..
    cmake --build .
    cd ..
    # run
    if [ -d input ]; then
        cd input
        ../build/test.exe
        cd ../..
    else
        ./build/test.exe
        cd ..
    fi
done
