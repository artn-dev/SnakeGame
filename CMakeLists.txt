cmake_minimum_required(VERSION 3.16.3)
project(SnakeGame VERSION 1.0.0)

set(SOURCE_FILES 
        "${PROJECT_SOURCE_DIR}/src/main.cpp"
        "${PROJECT_SOURCE_DIR}/ext/glad/src/glad.c"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)


target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS}
)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/ext/glad/include"
)