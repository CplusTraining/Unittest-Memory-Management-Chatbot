cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

project(Membot)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

file(GLOB project_SRCS src/*.cpp)

add_executable(membot ${project_SRCS})
target_link_libraries(membot ${wxWidgets_LIBRARIES})
target_include_directories(membot PRIVATE ${wxWidgets_INCLUDE_DIRS})

# Add the GoogleTest library subdirectories
add_subdirectory(thirdparty/googletest)

# Add unit test
file (GLOB project_UT src/*.cpp test/*.cpp)
add_executable(membot_test ${project_UT})

target_link_libraries(membot_test gtest_main gmock_main ${wxWidgets_LIBRARIES})
target_include_directories(membot_test PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_compile_definitions(membot_test PRIVATE UT=1)
