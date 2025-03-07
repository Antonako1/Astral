cmake_minimum_required(VERSION 3.0...3.5)

set(PROJECT_NAME "Astral")

project(${PROJECT_NAME} LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(ASTRAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/INCLUDE)


# Platform-specific sources
if(WIN32)
    set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/WINDOWS/ASTRAL_WIN_MEM.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/WINDOWS/ASTRAL_WIN_CON.c
    )
elseif(UNIX)
    set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/LINUX/ASTRAL_LINUX.c)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Shared sources
list(APPEND SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/SHARED/ASTRAL_SHARED_CON.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/SHARED/ASTRAL_SHARED_MEM.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SOURCE/SHARED/ASTRAL_SHARED_STR.c
)

# Define shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${ASTRAL_INCLUDE_DIR})

# Output build information
message(STATUS "Building ${PROJECT_NAME} as a shared library")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Include Directory: ${ASTRAL_INCLUDE_DIR}")
message(STATUS "Source Files: ${SOURCES}")
