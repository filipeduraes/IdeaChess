cmake_minimum_required(VERSION 3.20)

project(IdeaChess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SourceRoot ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PublicDirectory ${SourceRoot}/public)
set(PrivateDirectory ${SourceRoot}/private)

file(
    GLOB_RECURSE PrivateSources
    CONFIGURE_DEPENDS
    ${PrivateDirectory}/*.cpp
)

add_subdirectory(external/SDL)

add_executable(
    ${PROJECT_NAME}
    ${PrivateSources}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${PublicDirectory}
    PRIVATE
    ${PrivateDirectory}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    SDL2
    SDL2main
)
