cmake_minimum_required(VERSION 3.21)
project(BowlingScoreboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

enable_testing()
include(CTest)
find_package(GTest REQUIRED)
include(GoogleTest)

find_program(CPPCHECK_EXECUTABLE cppcheck)
find_program(CPPCHECK_HTMLREPORT_EXECUTABLE cppcheck-htmlreport)
if(CPPCHECK_EXECUTABLE)
    add_custom_target(cppcheck
        COMMAND ${CPPCHECK_EXECUTABLE}
                --project=${CMAKE_BINARY_DIR}/compile_commands.json
                -i ${CMAKE_BINARY_DIR}
                --enable=warning,style,performance,portability,information,missingInclude
                --inconclusive
                --std=c++20
                --language=c++
                --template=gcc
                --suppress=missingIncludeSystem
                --force
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running cppcheck static analysis"
        VERBATIM
    )

    if(CPPCHECK_HTMLREPORT_EXECUTABLE)
        add_custom_target(cppcheck-html
            COMMAND ${CPPCHECK_EXECUTABLE}
                    --project=${CMAKE_BINARY_DIR}/compile_commands.json
                    -i ${CMAKE_BINARY_DIR}
                    --enable=warning,style,performance,portability,information,missingInclude
                    --inconclusive
                    --std=c++20
                    --language=c++
                    --xml
                    --output-file=${CMAKE_BINARY_DIR}/cppcheck-report.xml
                    --suppress=missingIncludeSystem
                    --force
            COMMAND ${CPPCHECK_HTMLREPORT_EXECUTABLE}
                    --file=${CMAKE_BINARY_DIR}/cppcheck-report.xml
                    --report-dir=${CMAKE_BINARY_DIR}/cppcheck-report
                    --source-dir=${CMAKE_SOURCE_DIR}
                    --title="BowlingScoreboard static analysis report"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running cppcheck and generating HTML report"
            VERBATIM
        )
    else()
        message(STATUS "cppcheck-htmlreport not found; target 'cppcheck-html' is unavailable.")
    endif()
else()
    message(STATUS "cppcheck not found; targets 'cppcheck' and 'cppcheck-html' are unavailable.")
endif()

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