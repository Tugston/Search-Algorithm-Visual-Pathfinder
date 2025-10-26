# Create static library
add_library(
	Algorithms STATIC
	"src/Algorithms.cpp"
	"src/Algorithms.h"
 "src/Utillity/Enums.h")

if (CMAKE_VERSION VERSION_GREATER 3.20)
	set_property(
		TARGET Algorithms
		PROPERTY CXX_STANDARD 23
		CXX_STANDARD_REQUIRED ON
	)
endif()

target_include_directories(Algorithms PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# TODO: Add tests and install targets if needed.
