# Define the library
add_library(lib2
    src/filters/watercolor.cpp
)

target_include_directories(lib2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
