find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_SOURCES
        matrix.cpp
        test_recorder.cpp
        matrix.cpp
        soundbank.cpp
        test_timelinemark.cpp
        test_sound.cpp
)

set(CPP_SOURCES
        ../headers/utils.h
        ../headers/utils.cpp
        ../src/timelinemark.h
        ../src/timelinemark.cpp
        ../src/matrix.h
        ../src/matrix.cpp
        ../src/recorder.h
        ../src/recorder.cpp
        ../src/soundbank.h
        ../src/soundbank.cpp
        ../src/sound.h
        ../src/sound.cpp

        catch2_main.cpp
)

add_executable(tests ${TEST_SOURCES} ../lib/catch_amalgamated.cpp ${CPP_SOURCES})

# Premesti fajl u direktorijum gde se nalazi `tests` program da bi bio dostupan u testovima
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../src/resursi/zvukovi/A.wav ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)
