cmake_minimum_required (VERSION 3.0.0)

find_package(Threads)

add_executable(krylya
    main.cpp
    DeviceI2C.cpp
    NMEAUtil.cpp)

#target_compile_options(krylya PRIVATE -std=c++17)

target_link_libraries (krylya ${CMAKE_THREAD_LIBS_INIT})
