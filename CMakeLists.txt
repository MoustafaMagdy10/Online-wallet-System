

cmake_minimum_required(VERSION 3.0)
project(Online-wallet-System)


file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "src/*.cpp")

set(CMAKE_CXX_STANDARD 11)

add_executable(main ${SOURCES} ${HEADERS})

target_link_libraries(main raylib GL m pthread dl rt X11 )
