set (CMAKE_CXX_STANDARD 20)
add_library(html SHARED ModuleHtml.cpp ModuleHtml.hpp ../../badAPI.cpp ../../badAPI.hpp ../../requests/HTMLRequest.cpp ../../requests/HTMLRequest.hpp)
target_include_directories(html PUBLIC ../../api ../../requests)
include_directories(${CMAKE_INCLUDE_PATH})
target_link_libraries(html ${CONAN_LIBS})

if (UNIX)
	add_custom_command(
	TARGET html POST_BUILD
	COMMAND cp ../../lib/libhtml.so ../../bin
	VERBATIM)
endif (UNIX)
