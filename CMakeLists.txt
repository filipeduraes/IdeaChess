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

file(
    GLOB_RECURSE PublicHeaders
    CONFIGURE_DEPENDS
    ${PublicDirectory}/*.h
)

set(SDL2_DISABLE_SDL2MAIN ON CACHE BOOL "" FORCE)
add_subdirectory(external/SDL)
add_subdirectory(external/SDL_image)

add_executable(
    ${PROJECT_NAME}
    ${PrivateSources}
    ${PublicHeaders}
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
    SDL2_image
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    SDL_MAIN_HANDLED
)


add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2_image>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
