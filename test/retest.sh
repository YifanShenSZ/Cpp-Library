for directory in utility_file utility_matrix utility_heap utility_UnionFind utility_LRUCache utility_LFUCache \
linalg; do
    echo
    echo "Entre "$directory
    # rebuild
    cd $directory/build
    rm test.exe
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
