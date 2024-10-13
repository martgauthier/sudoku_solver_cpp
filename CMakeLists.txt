cmake_minimum_required(VERSION 3.30)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/**.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include    
)