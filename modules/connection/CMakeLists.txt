set (CMAKE_CXX_STANDARD 20)
add_library(connection SHARED ModuleConnection.cpp ModuleConnection.hpp ../../badAPI.cpp ../../badAPI.hpp)
target_include_directories(connection PUBLIC ../../api)
include_directories(${CMAKE_INCLUDE_PATH})
target_link_libraries(connection ${CONAN_LIBS})

if (UNIX)
	add_custom_command(
	TARGET connection POST_BUILD
	COMMAND cp ../../lib/libconnection.so ../../bin
	VERBATIM)
endif (UNIX)
