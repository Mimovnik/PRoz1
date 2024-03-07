cmake_minimum_required(VERSION 3.0.0)
project(projectName VERSION 0.1.0)

add_library(
    SOURCE_FILES

    src/List.h
    src/List.c
    src/HashMap.h
    src/HashMap.c
)


add_executable(projectName src/main.c)
target_link_libraries(${PROJECT_NAME} SOURCE_FILES)