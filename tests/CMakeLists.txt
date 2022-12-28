find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_SOURCES
        )

set(CPP_SOURCES
        ../headers/utils.h
        ../headers/utils.cpp
        ../src/timelinemark.h
        ../src/timelinemark.cpp
)

add_executable(tests ${TEST_SOURCES} ../lib/catch_amalgamated.cpp ${CPP_SOURCES})

target_link_libraries(tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)
