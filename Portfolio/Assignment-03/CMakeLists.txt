cmake_minimum_required(VERSION 3.20)
project(Assignment-03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# "ON" = build Option 1, "OFF" = build Option 2.
option(BUILD_ASSIGNMENT_03_OPTION_1 "Build Assignment Option 1 (Standard)" OFF)

add_executable(Assignment-03
        src/main.cpp
        src/Node.cpp
        src/AVL.cpp
        src/Parser.cpp
        src/Interpreter.cpp
        src/RedBlackTree.cpp
        include/RedBlackTree.h
        include/RedBlackNode.h
)
target_include_directories(Assignment-03 PRIVATE include)

# Conditionally add the correct source file
if(BUILD_ASSIGNMENT_03_OPTION_1)
    # If ON, add option1.cpp and define 'ASSIGNMENT_OPTION=1' for C++
    target_sources(Assignment-03
      PRIVATE
            src/option1.cpp
            include/option1.h
    )
    target_compile_definitions(Assignment-03 PRIVATE "ASSIGNMENT_03_OPTION=1")
else()
    # If OFF, add option2.cpp and define 'ASSIGNMENT_OPTION=2' for C++
    target_sources(Assignment-03
      PRIVATE
            src/option2.cpp
            include/option2.h
    )
    target_compile_definitions(Assignment-03 PRIVATE "ASSIGNMENT_03_OPTION=2")
endif()
#target_link_libraries(Assignment-03
#    PRIVATE
#    SharedLib
#)


add_custom_command(TARGET Assignment-03 POST_BUILD
  # Add a custom command here if needed
  COMMAND ${CMAKE_COMMAND} -E echo "Assignment-03 post-build step"
)
