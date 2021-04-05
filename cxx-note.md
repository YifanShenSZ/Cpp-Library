# My note during using c++
When there are abi issue, add a line in `CMakeLists.txt`:
```
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")
```