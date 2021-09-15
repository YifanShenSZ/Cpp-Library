for directory in utility file linalg; do
    echo
    echo "Entre "$directory
    cd $directory/build
    rm -f test.exe
    cmake --build .
    cd ..
    if [ -d input ]; then
        cd input
        ../build/test.exe
        cd ../..
    else
        ./build/test.exe
        cd ..
    fi
done