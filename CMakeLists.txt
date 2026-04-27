cmake_minimum_required(VERSION 3.21)
project(BowlingScoreboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

enable_testing()
include(CTest)
find_package(GTest REQUIRED)
include(GoogleTest)

find_package(Qt6 REQUIRED COMPONENTS
    Core Gui Qml Quick QuickControls2)

add_subdirectory(src/core)
add_subdirectory(src/viewmodel)
add_subdirectory(src/network)

qt_add_executable(BowlingScoreboard
    src/main.cpp
)

qt_add_qml_module(BowlingScoreboard
    URI Bowling
    VERSION 1.0
    QML_FILES
        src/ui/Main.qml
        src/ui/FrameBox.qml
)

target_link_libraries(BowlingScoreboard
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    BowlingViewModel
    BowlingNetwork
)