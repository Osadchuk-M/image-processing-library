# Define the library
add_library(lib4
    src/filters/resize.cpp
)

target_include_directories(lib4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
