cmake_minimum_required(VERSION 3.5)
project(sparky)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "-Wall -Wextra" CACHE STRING "" FORCE)
set (CMAKE_C_FLAGS "-Wall -Wextra" CACHE STRING "" FORCE)

file (GLOB SOURCES *.c *.cpp *.h)

find_package (GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package (OpenGL REQUIRED)
include_directories (${OPENGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)
find_package (GLFW3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIRS})
link_libraries(${GLFW3_LIBRARIES})

add_executable (${PROJECT_NAME} ${SOURCES} Window.cpp Window.h Shader.cpp Shader.h FileUtils.cpp FileUtils.h Buffer.cpp Buffer.h IndexBuffer.cpp IndexBuffer.h VertexArray.cpp VertexArray.h Renderable2D.h SimpleRenderer2D.cpp SimpleRenderer2D.h Renderer2D.h BatchRenderer2D.cpp BatchRenderer2D.h Sprite.cpp Sprite.h StaticSprite.cpp StaticSprite.h)

target_link_libraries (${PROJECT_NAME}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLFW3_LIBRARIES}
)
