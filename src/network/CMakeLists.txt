project(BowlingNetwork LANGUAGES CXX)

add_library(BowlingNetwork STATIC
    inc/UdpReceiver.hpp
    src/UdpReceiver.cpp
)

target_compile_features(BowlingNetwork PUBLIC cxx_std_20)
target_include_directories(BowlingNetwork PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

find_package(Qt6 REQUIRED COMPONENTS Network)
target_link_libraries(BowlingNetwork 
    PUBLIC 
        Qt6::Network
        Qt6::Core
)