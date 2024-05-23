cmake_minimum_required(VERSION 3.15)

project(VulkanTest)

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(vulkan_test
    source/main.cpp
    source/Application.cpp
    source/FileUtils.cpp
)

add_subdirectory(thirdparty/glfw-3.3.9)


target_include_directories(vulkan_test 
    PRIVATE 
    ${Vulkan_INCLUDE_DIRS}
    thirdparty/glfw-3.3.9/include
    thirdparty/stb
    thirdparty/tinyobjloader
)
add_dependencies(vulkan_test glfw)
target_link_libraries(vulkan_test PRIVATE glfw)
target_link_libraries(vulkan_test PRIVATE $ENV{VULKAN_SDK}/Lib/vulkan-1.lib)

# find_program(GLSLC_PROGRAM glslc REQUIRED)
# execute_process(COMMAND ${GLSLC_PROGRAM} ${CMAKE_SOURCE_DIR}/shaders/main.vert -o ${CMAKE_SOURCE_DIR}/shaders/outputs/vert.spv)
# execute_process(COMMAND ${GLSLC_PROGRAM} ${CMAKE_SOURCE_DIR}/shaders/main.frag -o ${CMAKE_SOURCE_DIR}/shaders/outputs/frag.spv)