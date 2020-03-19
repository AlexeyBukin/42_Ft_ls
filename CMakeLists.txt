cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD  90)
set(CMAKE_C_STANDARD_REQUIRED True)

# set the project name
project(ft_ls)

#file(GLOB SOURCES "src/*.c")

#TODO change makefile, laggyy when make

# find src -type f -name '*.c' | sed "s/^/        /"
set(SOURCES
        src/main.c
        src/ls_flags.c
        src/ls_entry.c
        src/ls_errors.c
        src/ls_orders.c
        src/ls_sort.c
        src/ls_free.c
        src/ls_print.c
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/libft/include
        )

add_subdirectory(libft)
target_link_libraries(${PROJECT_NAME} ft)

