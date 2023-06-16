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

# fmt
FetchContent_Declare(
    fmt
    GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
    GIT_TAG         10.0.0
    GIT_PROGRESS    TRUE
)

FetchContent_MakeAvailable(SDL SDL_TTF fmt)

add_executable(
    ${PROJECT_NAME}
    src/Pong.cpp
    src/Game.h
    src/Game.cpp
    src/SDLElements.h
    src/WindowSize.h
    src/UIElements/UIBaseElement.h
    src/UIElements/UIBaseElement.cpp
    src/UIElements/UIFunctions.h
    src/UIElements/UIFunctions.cpp
    src/UIElements/Player.h
    src/UIElements/Player.cpp
    src/UIElements/Ball.h
    src/UIElements/Ball.cpp
    src/UIElements/Points.h
    src/UIElements/Points.cpp
    src/UIElements/Field.h
    src/UIElements/Field.cpp
    src/UIElements/MiddleLine.h
    src/UIElements/MiddleLine.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(
    ${PROJECT_NAME}    
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    fmt::fmt
)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/)

