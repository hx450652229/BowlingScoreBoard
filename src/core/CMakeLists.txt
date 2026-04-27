project(BowlingCore LANGUAGES CXX)

add_library(BowlingCore STATIC
    inc/BowlingGame.hpp
    src/BowlingGame.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_compile_features(BowlingCore PUBLIC cxx_std_20)

if (BUILD_TESTING)
    add_executable(BowlingCoreTests
        test/BowlingGameTest.cpp
    )
    target_link_libraries(BowlingCoreTests
        PRIVATE
            BowlingCore
            GTest::gtest_main
    )
    target_compile_features(BowlingCoreTests PUBLIC cxx_std_20)
    gtest_discover_tests(BowlingCoreTests)
endif()

target_include_directories(BowlingCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)