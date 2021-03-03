for directory in utility linalg; do
    cd $directory/build
    rm -f test.exe
    cmake --build .
    ./test.exe
    cd ../..
done