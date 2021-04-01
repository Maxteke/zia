set (CMAKE_CXX_STANDARD 20)
add_library(php SHARED ModulePhp.cpp ModulePhp.hpp ../../badAPI.cpp ../../badAPI.hpp ../../requests/PHPRequest.cpp ../../requests/PHPRequest.hpp)
target_include_directories(php PUBLIC ../../api ../../requests)
include_directories(${CMAKE_INCLUDE_PATH})
target_link_libraries(php ${CONAN_LIBS})

if (UNIX)
	add_custom_command(
	TARGET php POST_BUILD
	COMMAND cp ../../lib/libphp.so ../../bin
	VERBATIM)
endif (UNIX)
