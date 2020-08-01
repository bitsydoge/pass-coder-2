cmake_minimum_required(VERSION 3.7)
project(PassCoder2 C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(PASSCODER_SOURCE_DIRECTORY ${CMAKE_BINARY_DIR}/Sources)
set(PASSCODER_EXTERNAL_DIRECTORY ${CMAKE_BINARY_DIR}/External)

file(GLOB_RECURSE SOURCES
        ${PASSCODER_SOURCE_DIRECTORY}/*.h
        ${PASSCODER_SOURCE_DIRECTORY}/*.c)

file(GLOB_RECURSE EXTERNAL
        ${PASSCODER_EXTERNAL_DIRECTORY}/*.h
        ${PASSCODER_EXTERNAL_DIRECTORY}/*.c)

string(REGEX REPLACE "CMakeFiles/[^;]+;?" "" SOURCES "${SOURCES}")
string(REGEX REPLACE "CMakeFiles/[^;]+;?" "" EXTERNAL "${EXTERNAL}")
include_directories(${CMAKE_BINARY_DIR}/External/argon2)
include_directories(${CMAKE_BINARY_DIR}/External/argtable3)
include_directories(${CMAKE_BINARY_DIR}/External/rlutil)

add_executable(PassCoder2 ${SOURCES} ${EXTERNAL})
set_target_properties(PassCoder2 PROPERTIES C_STANDARD 99)

IF (NOT WIN32)
	target_link_libraries(PassCoder2 pthread m)
ENDIF()