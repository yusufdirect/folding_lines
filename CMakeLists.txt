cmake_minimum_required(VERSION 3.16)

project(FoldingLines)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FoldingLines
    main.cpp
    Events.cpp
    Actions.cpp
    ControlMapping.cpp
    Opening.cpp
    MidiInput.cpp
    MidiActions.cpp
    UI.cpp
    FoldingLines.cpp
)

target_include_directories(FoldingLines PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(FoldingLines
    raylib
    opengl32
    gdi32
    winmm
)