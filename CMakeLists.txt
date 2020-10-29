cmake_minimum_required(VERSION 3.0)

project(Physics)
add_subdirectory(deps)
add_executable(Physics src/main.cpp src/Shader.cpp src/Mat.cpp src/Vec.cpp src/VertexBuffer.cpp src/VertexArray.cpp deps/glad/src/glad.c)

target_link_libraries(Physics PUBLIC glfw)
target_include_directories(Physics PUBLIC "${GLFW_SOURCE_DIR}/include")
target_include_directories(Physics PUBLIC "deps/glad/include")
set_target_properties(Physics PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)

add_custom_command(TARGET Physics POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:Physics>/shaders)