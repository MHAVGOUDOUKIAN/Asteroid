cmake_minimum_required(VERSION 3.0)

#Set a normal variable to a given value
set(PROJECT_NAME Asteroid)
project(${PROJECT_NAME})

# Very important, otherwise your executable will be considered as a shared library by your OS and no as an executable
set (CMAKE_CXX_FLAGS "-no-pie")

# Select the sources files to use in the current directory
set( SOURCES
    Engine.cpp
    main.cpp
    Munition.cpp
    Obstacle.cpp 
    Particule.cpp
    Player.cpp
)

# //   headers file //
set( HEADERS
    Engine.hpp
    Munition.hpp
    Obstacle.hpp 
    Particule.hpp
    ParticuleGenerator.hpp
    CONSTANTES.hpp
    Player.hpp
)

add_executable(${PROJECT_NAME} # Name of the executable
    ${SOURCES}
    ${HEADERS})
    
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system 
    sfml-audio
)