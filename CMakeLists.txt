cmake_minimum_required(VERSION 3.10)

project(ImageProcessor VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)
find_package(SIPL REQUIRED)
find_library(UUID_LIBRARY NAMES uuid)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
    ${SIPL_INCLUDE_DIRS}
)

add_subdirectory(third-party/lib1)
add_subdirectory(third-party/lib2)
add_subdirectory(third-party/lib3)
add_subdirectory(third-party/lib4)
add_subdirectory(third-party/lib5)

add_library(image_processor_lib
    src/filter_factory.cpp
    src/internal/api.cpp
    src/internal/image_processor.cpp
    src/internal/utils.cpp
    src/internal/worker_pool.cpp
)

target_include_directories(image_processor_lib PRIVATE 
    ${CMAKE_SOURCE_DIR}/third-party/lib1/include
    ${CMAKE_SOURCE_DIR}/third-party/lib2/include
    ${CMAKE_SOURCE_DIR}/third-party/lib3/include
    ${CMAKE_SOURCE_DIR}/third-party/lib4/include
    ${CMAKE_SOURCE_DIR}/third-party/lib5/include
)

target_link_libraries(image_processor_lib 
    lib1 
    lib2 
    lib3 
    lib4 
    lib5 
    ${OpenCV_LIBS}
    ${UUID_LIBRARY}
    ${SIPL_LIBRARIES}
)
