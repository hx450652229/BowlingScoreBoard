project(BowlingViewModel LANGUAGES CXX)

add_library(BowlingViewModel STATIC
    inc/ScoreboardViewModel.hpp
    src/ScoreboardViewModel.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_compile_features(BowlingViewModel PUBLIC cxx_std_20)

target_include_directories(BowlingViewModel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(BowlingViewModel 
    PUBLIC 
        Qt6::Core
        BowlingCore
)