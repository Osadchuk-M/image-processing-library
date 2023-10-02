# Define the library
add_library(lib5
    src/filters/crop.cpp
)

target_include_directories(lib5 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
