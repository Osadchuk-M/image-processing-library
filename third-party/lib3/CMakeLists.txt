# Define the library
add_library(lib3
    src/filters/cartoonize.cpp
)

target_include_directories(lib3 PRIVATE ${SIPL_INCLUDE_DIRS}../)
target_include_directories(lib3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)