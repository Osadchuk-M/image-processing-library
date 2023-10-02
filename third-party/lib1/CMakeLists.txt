# Define the library
add_library(lib1
    src/filters/blur.cpp
)

target_include_directories(lib1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
