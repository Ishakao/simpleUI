cmake_minimum_required(VERSION 3.16)
project(simpleUI_test LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SIMPLEUI_TEST
    src/test5.cpp
    include/SUIutils.cpp
)

target_include_directories(SIMPLEUI_TEST PRIVATE include)

target_link_libraries(SIMPLEUI_TEST PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libraylib.dll.a
    ${CMAKE_SOURCE_DIR}/lib/glfw3dll.lib

    ${CMAKE_SOURCE_DIR}/lib/libharfbuzz.a
    ${CMAKE_SOURCE_DIR}/lib/libharfbuzz-subset.a
    ${CMAKE_SOURCE_DIR}/lib/libharfbuzz-gpu.a
    ${CMAKE_SOURCE_DIR}/lib/libharfbuzz-raster.a
    ${CMAKE_SOURCE_DIR}/lib/libharfbuzz-vector.a

    ${CMAKE_SOURCE_DIR}/lib/libfreetype.dll.a
    winmm
    gdi32
)

set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_compile_definitions(SIMPLEUI_TEST PRIVATE API_LIB_EXPORT=)
target_compile_options(SIMPLEUI_TEST PRIVATE -w)
target_compile_options(SIMPLEUI_TEST PRIVATE -Wno-unused-parameter -Wno-unused-variable)

# automatic files copying (dll files nearby to executable and fonts/shaders dirs which used by simpleUI) | you can copy it manually
add_custom_command(TARGET SIMPLEUI_TEST POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/bin/libraylib.dll
        ${CMAKE_SOURCE_DIR}/bin/glfw3.dll
        ${CMAKE_SOURCE_DIR}/bin/libgcc_s_seh-1.dll
        ${CMAKE_SOURCE_DIR}/bin/libstdc++-6.dll
        ${CMAKE_SOURCE_DIR}/bin/libwinpthread-1.dll
        $<TARGET_FILE_DIR:SIMPLEUI_TEST>
    COMMAND ${CMAKE_COMMAND} -E copy_directory   # copy fonts dir
        ${CMAKE_SOURCE_DIR}/Fonts
        $<TARGET_FILE_DIR:SIMPLEUI_TEST>/Fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory   # copy texture dir
        ${CMAKE_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:SIMPLEUI_TEST>/textures
    COMMAND ${CMAKE_COMMAND} -E copy_directory   # copy shaders dir
        "${CMAKE_SOURCE_DIR}/simpleUI Shaders"
        "$<TARGET_FILE_DIR:SIMPLEUI_TEST>/simpleUI Shaders"
)