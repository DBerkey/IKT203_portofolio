cmake_minimum_required(VERSION 3.16)
project(Assignment01 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt is not used in this assignment
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

# "ON" = Option 1, "OFF" = Option 2 (you are using Option 2)
option(BUILD_ASSIGNMENT_01_OPTION_1 "Build Assignment Option 1 (Standard)" OFF)


# Main entry point. Option-specific sources are added below.
add_executable(Assignment-01
        main.cpp
)

# Include directories
target_include_directories(Assignment-01 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../SharedLib
)

# Add source files depending on option
if(BUILD_ASSIGNMENT_01_OPTION_1)

    target_sources(Assignment-01 PRIVATE
            src/option1.cpp
            include/option1.h
    )
    target_compile_definitions(Assignment-01 PRIVATE ASSIGNMENT_01_OPTION=1)

else()

    target_sources(Assignment-01 PRIVATE
            src/option2.cpp
            include/option2.h

            src/MusicApp.cpp
            include/MusicApp.h

            src/Player.cpp
            include/Player.h

            src/Track.cpp
            include/Track.h
    )
    target_compile_definitions(Assignment-01 PRIVATE ASSIGNMENT_01_OPTION=2)

endif()

# Link SharedLib
target_link_libraries(Assignment-01 PRIVATE SharedLib)

add_custom_command(TARGET Assignment-01 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Assignment-01 post-build step"
)
