cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME App)
project(${PROJECT_NAME})

message("Starting cmake process..")

# Add a subdirectory to the build
# Check if a "CMakeLists.txt" file exists in the subdirectory
add_subdirectory(src)

set(PERMISSIONS OWNER_READ 
    OWNER_WRITE 
    OWNER_EXECUTE 
    GROUP_READ 
    GROUP_WRITE 
    GROUP_EXECUTE 
    WORLD_READ 
    WORLD_WRITE 
    WORLD_EXECUTE
)

install(FILES src/Asteroid DESTINATION ${PROJECT_SOURCE_DIR} PERMISSIONS ${PERMISSIONS} )