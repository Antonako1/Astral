cmake_minimum_required(VERSION 3.10)

project(TEST LANGUAGES C)  # Explicitly define project and language

# Path to the Astral library (parent directory)
set(ASTRAL_DIR "${CMAKE_SOURCE_DIR}/../..")

# Add the Astral library
add_subdirectory(${ASTRAL_DIR} ${CMAKE_BINARY_DIR}/AstralBuild)

# Define sources
set(TEST_SOURCES ${CMAKE_SOURCE_DIR}/ASTRAL_UI_1.c)

# Create the test executable
add_executable(TEST ${TEST_SOURCES})

# Link with Astral library
target_link_libraries(TEST PRIVATE Astral)

if(WIN32)
    add_custom_target(copy_astral ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Astral>
        $<TARGET_FILE_DIR:TEST>
        DEPENDS Astral TEST
    )
endif()


# Include the Astral headers
target_include_directories(TEST PRIVATE ${ASTRAL_DIR}/INCLUDE)

# Output debug info
message(STATUS "Building TEST project with ASTRAL dependency")
message(STATUS "ASTRAL Library Path: ${ASTRAL_DIR}")
message(STATUS "Source Files: ${TEST_SOURCES}")
