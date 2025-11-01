# Create static library
add_library(
	Algorithms STATIC
	"src/Algorithms.cpp"
	"src/Algorithms.h"
 "src/Utillity/Enums.h" "src/Searches/DFS.h" "src/Searches/DFS.cpp" "src/Searches/BaseSearch.h" "src/Searches/BaseSearch.cpp" "src/Searches/BFS.h" "src/Searches/BFS.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.20)
	set_property(
		TARGET Algorithms
		PROPERTY CXX_STANDARD 23
		CXX_STANDARD_REQUIRED ON
	)
endif()

target_include_directories(Algorithms PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# TODO: Add tests and install targets if needed.
