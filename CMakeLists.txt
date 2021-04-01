project(Zia)
cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})
include_directories("api/http" "api" "./" "BoostServer" "requests")


add_executable(zia main.cpp badAPI.cpp zia.cpp BoostServer/Server.cpp BoostServer/Session.cpp)
target_link_libraries(zia ${CONAN_LIBS})

if (UNIX)
    target_link_libraries(zia dl)
endif (UNIX)

add_subdirectory(modules/connection)
add_subdirectory(modules/php)
add_subdirectory(modules/html)
add_subdirectory(modules/routehandler)
