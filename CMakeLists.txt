cmake_minimum_required(VERSION 3.21.0)
project(Pong VERSION 0.1.0 LANGUAGES CXX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
include(CheckIncludeFileCXX)

## Compile feature checks
CHECK_INCLUDE_FILE_CXX("format" SUPPORT_STD_FORMAT_LIB)
message(STATUS "CXX_FORMAT_SUPPORT: ${CXX_FORMAT_SUPPORT}")

# sdl2
FetchContent_Declare(
    SDL
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL
    GIT_TAG         release-2.30.10
    GIT_PROGRESS    TRUE
)

set(SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2_DISABLE_INSTALL OFF CACHE BOOL "" FORCE)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
# sdl_ttf
FetchContent_Declare(
    SDL_TTF
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_ttf
    GIT_TAG         release-2.22.0
    GIT_PROGRESS    TRUE
)

# fmt
if(NOT SUPPORT_STD_FORMAT_LIB)
    message("Fetch fmt lib")
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
        GIT_TAG         10.0.0
        GIT_PROGRESS    TRUE
    )
    FetchContent_MakeAvailable(fmt)
endif()

FetchContent_MakeAvailable(SDL SDL_TTF)

add_definitions( -DSUPPORT_STD_FORMAT_LIB=${SUPPORT_STD_FORMAT_LIB} )

configure_file( src/Configure.h.in Configure.h )

if(APPLE)
    set(CUR_TARGET ${PROJECT_NAME})        
    # NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
    # the property added to Info.plist
    set(MACOSX_BUNDLE_ICON_FILE Pong.icns)

    # And this part tells CMake where to find and install the file itself
    set(myApp_ICON ${CMAKE_SOURCE_DIR}/assets/Pong.icns)
    set_source_files_properties(
        ${myApp_ICON} 
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources/
    )

    # Copy DB File
    # set(DB_FILE ${CMAKE_SOURCE_DIR}/db/worktimer.db)
    # set_source_files_properties(
    # ${DB_FILE}
    # PROPERTIES
    #     MACOSX_PACKAGE_LOCATION Resources/db
    # )
    
    file(GLOB_RECURSE Images "${CMAKE_SOURCE_DIR}/assets/*.ttf")
    set_source_files_properties(
        ${Images}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources/assets/
    )

    # add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${myApp_ICON} ${TARGET_SRC} ${Images})  

     add_executable(
        ${PROJECT_NAME}
        MACOSX_BUNDLE
        src/Pong.cpp
        src/Game.h
        src/Game.cpp
        src/SDLElements.h
        src/WindowSize.h
        src/Utils.h
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
        ${Images}
        ${myApp_ICON}
    )
    
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUNDLE True
        MACOSX_BUNDLE_GUI_IDENTIFIER my.domain.style.identifier.${PROJECT_NAME}
        MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
        MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}"
        MACOSX_PACKAGE_LOCATION MacOSX
    )
    #set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
    #target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
    
    target_link_libraries(
        ${PROJECT_NAME}    
        SDL2::SDL2-static
        SDL2::SDL2main
        SDL2_ttf::SDL2_ttf-static
    )
    
    if(NOT SUPPORT_STD_FORMAT_LIB)
        target_link_libraries(
            ${PROJECT_NAME}    
            fmt::fmt
        )
    endif()
else()

    add_executable(
        ${PROJECT_NAME}
        src/Pong.cpp
        src/Game.h
        src/Game.cpp
        src/SDLElements.h
        src/WindowSize.h
        src/Utils.h
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

    #set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
    #target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

    target_link_libraries(
        ${PROJECT_NAME}    
        SDL2::SDL2-static
        SDL2::SDL2main
        SDL2_ttf::SDL2_ttf-static
    )

    if(NOT SUPPORT_STD_FORMAT_LIB)
        target_link_libraries(
            ${PROJECT_NAME}    
            fmt::fmt
        )
    endif()

    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/)
endif()


target_include_directories(${PROJECT_NAME} 
PUBLIC
"${CMAKE_CURRENT_BINARY_DIR}")

# standard compiler warnings
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)
