cmake_minimum_required(VERSION 3.26)
project(Wolfram)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(deps/glfw)

find_package(Vulkan REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include)

file(GLOB SOURCES 
"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/gl.c")

add_executable(Wolfram ${SOURCES})

target_link_libraries(Wolfram glfw ${GLFW_LIBRARIES})
