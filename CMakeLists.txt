cmake_minimum_required(VERSION 3.26)
project(Wolfram)

set(CMAKE_CXX_STANDARD 23)

set(source "${CMAKE_SOURCE_DIR}/shaders")
set(destination "${CMAKE_CURRENT_BINARY_DIR}/shaders")

add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)

find_package(Vulkan REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/include)

file(GLOB SOURCES 
"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/extra/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/deps/glad/src/gl.c")

add_executable(Wolfram ${SOURCES})

target_link_libraries(Wolfram glfw ${GLFW_LIBRARIES})
target_link_libraries(Wolfram glm)

add_custom_command(TARGET ${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
    DEPENDS ${destination}
    COMMENT "symbolic link resource folder from ${source} => ${destination}"
)