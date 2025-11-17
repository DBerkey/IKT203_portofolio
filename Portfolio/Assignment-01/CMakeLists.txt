cmake_minimum_required(VERSION 3.16)
project(Assignment01 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Eg bruker ikke Qt i denne oppgaven ,så derfor eg slå disse av.
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

# "ON" = Option 1, "OFF" = Option 2 (du bruker Option 2)
option(BUILD_ASSIGNMENT_01_OPTION_1 "Build Assignment Option 1 (Standard)" OFF)

# SharedLib (ligger en mappe opp)
# Dette gjør at målet "SharedLib" blir bygget, og at Eg kan linke mot det.
add_subdirectory(
        ${CMAKE_CURRENT_SOURCE_DIR}/../SharedLib
        ${CMAKE_CURRENT_BINARY_DIR}/SharedLib_build
)

#  main Arena sin
add_executable(Assignment-01
        main.cpp
)

# Hvor kompilatoren skal lete etter .h-filer
target_include_directories(Assignment-01 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include      # MusicApp.h, Player.h, Track.h, option2.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../SharedLib # SharedLib.h
)

# kildefilene basert på Option 1 / 2
if(BUILD_ASSIGNMENT_01_OPTION_1)
    # OPTION 1 (Eg skal ikke bruke denne, men vi lar det stå)
    target_sources(Assignment-01 PRIVATE
            src/option1.cpp
            include/option1.h
    )
    target_compile_definitions(Assignment-01 PRIVATE ASSIGNMENT_01_OPTION=1)
else()
    # OPTION 2 – Eg skal bruke denne
    target_sources(Assignment-01 PRIVATE
            src/option2.cpp      # "tom" bridge-fil
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

# Link mot SharedLib (ReadSongsFromFile, etc.)
target_link_libraries(Assignment-01 PRIVATE SharedLib)

add_custom_command(TARGET Assignment-01 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Assignment-01 post-build step"
)
