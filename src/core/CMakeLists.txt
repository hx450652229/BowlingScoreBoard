project(BowlingCore LANGUAGES CXX)

add_library(BowlingCore STATIC
    inc/BowlingGame.hpp
    src/BowlingGame.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_compile_features(BowlingCore PUBLIC cxx_std_20)

target_include_directories(BowlingCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)