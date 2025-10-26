# Add source to this project's executable.
add_library(
	TestCases STATIC
	"src/EntryPoint.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.20)
	set_property(
		TARGET Algorithms
		PROPERTY CXX_STANDARD 23
		CXX_STANDARD_REQUIRED ON
	)
endif()

# TODO: Add tests and install targets if needed.