set (CMAKE_CXX_STANDARD 20)
add_library(routehandler SHARED ModuleRouteHandler.cpp ModuleRouteHandler.hpp ../../badAPI.cpp ../../badAPI.hpp ../../requests/PHPRequest.cpp ../../requests/PHPRequest.hpp ../../requests/HTMLRequest.cpp ../../requests/HTMLRequest.hpp)
target_include_directories(routehandler PUBLIC ../../api ../../requests)
include_directories(${CMAKE_INCLUDE_PATH})
target_link_libraries(routehandler ${CONAN_LIBS})

if (UNIX)
	add_custom_command(
	TARGET routehandler POST_BUILD
	COMMAND cp ../../lib/libroutehandler.so ../../bin
	VERBATIM)
endif (UNIX)
