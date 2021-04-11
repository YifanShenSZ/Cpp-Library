for directory in utility file linalg; do
    echo
    echo "Entre "$directory
    cd $directory/build
    rm -f test.exe
    cmake --build .
    ./test.exe
    cd ../..
done