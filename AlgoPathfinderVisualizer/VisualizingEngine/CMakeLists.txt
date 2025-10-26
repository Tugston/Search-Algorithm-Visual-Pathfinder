# Add source to this project's executable.
add_executable (
	VisualizingEngine
	"src/Main.cpp"
 "src/GridSystem/Cell.h" "src/GridSystem/Cell.cpp" "src/GridSystem/Grid.h" "src/GridSystem/Grid.cpp" "src/Application.h" "src/Application.cpp" "src/Logger/Logger.h")

message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

if (CMAKE_VERSION VERSION_GREATER 3.20)
	set_property(
		TARGET VisualizingEngine
		PROPERTY CXX_STANDARD 23
		CXX_STANDARD_REQUIRED ON
	)
endif()

# TODO: Add tests and install targets if needed.
include(FetchContent)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 3.0.2
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_MakeAvailable(SFML)

target_link_libraries(VisualizingEngine PRIVATE SFML::Graphics)
target_link_libraries(VisualizingEngine PRIVATE Algorithms)