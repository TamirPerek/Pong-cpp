cmake_minimum_required(VERSION 3.21.0)
project(Pong VERSION 0.1.0 LANGUAGES CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

# sdl2
FetchContent_Declare(
    SDL
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL
    GIT_TAG         release-2.26.3
    GIT_PROGRESS    TRUE
)

set(SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2_DISABLE_INSTALL OFF CACHE BOOL "" FORCE)

# sdl_ttf
FetchContent_Declare(
    SDL_TTF
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_ttf
    GIT_TAG         release-2.20.2
    GIT_PROGRESS    TRUE
)

FetchContent_MakeAvailable(SDL SDL_TTF)

# set(SDL_LIBRARIES ${SDL_LIBRARIES} SDL2main SDL2-static SDL2_ttf)
# target_include_directories("${PROJECT_NAME}" PRIVATE include)

# target_link_libraries("${PROJECT_NAME}" PRIVATE ${SDL_LIBRARIES})

# find_package(SDL2 REQUIRED)
# include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
    ${PROJECT_NAME}
    pong.cpp
)

target_link_libraries(
    ${PROJECT_NAME}    
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/img/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/img/)

