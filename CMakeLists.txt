cmake_minimum_required(VERSION 3.18)
project(simpleUI_test LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

set(HB_TAG "11.2.1" CACHE STRING "")
set(RAYLIB_TAG "5.5" CACHE STRING "")
set(GLFW_TAG "3.4" CACHE STRING "")
set(ZLIB_TAG "v1.3.1" CACHE STRING "")
set(PNG_TAG "v1.6.43" CACHE STRING "")
set(FT_TAG "VER-2-13-3" CACHE STRING "")

set(TOOLCHAIN "${CMAKE_CXX_COMPILER_ID}")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib/${TOOLCHAIN}")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin/${TOOLCHAIN}")
set(STAGE_DIR "${CMAKE_BINARY_DIR}/deps_stage")

if(MSVC)
    set(SUI_MSVC_LIKE 1)
else()
    set(SUI_MSVC_LIKE 0)
endif()

if(NOT EXISTS "${LIB_DIR}/.deps_ok")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/deps_build" "${STAGE_DIR}")

    execute_process(
        COMMAND ${CMAKE_COMMAND}
            -G "${CMAKE_GENERATOR}"
            -S "${CMAKE_SOURCE_DIR}/cmake/deps"
            -B "${CMAKE_BINARY_DIR}/deps_build"
            -DDEPS_PREFIX=${STAGE_DIR}
            -DDEPS_C_COMPILER=${CMAKE_C_COMPILER}
            -DDEPS_CXX_COMPILER=${CMAKE_CXX_COMPILER}
            -DDEPS_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}
            -DRAYLIB_TAG=${RAYLIB_TAG}
            -DGLFW_TAG=${GLFW_TAG}
            -DFT_TAG=${FT_TAG}
            -DHB_TAG=${HB_TAG}
            -DDEPS_MSVC_LIKE=${SUI_MSVC_LIKE}
            -DZLIB_TAG=${ZLIB_TAG}
            -DPNG_TAG=${PNG_TAG}
        RESULT_VARIABLE DEPS_RES
    )
    if(NOT DEPS_RES EQUAL 0)
        message(FATAL_ERROR "deps configure failed")
    endif()

    execute_process(
        COMMAND ${CMAKE_COMMAND} --build "${CMAKE_BINARY_DIR}/deps_build" --config Release
        RESULT_VARIABLE DEPS_RES
    )
    if(NOT DEPS_RES EQUAL 0)
        message(FATAL_ERROR "deps build failed")
    endif()

    file(MAKE_DIRECTORY "${LIB_DIR}" "${BIN_DIR}")
    file(COPY "${STAGE_DIR}/lib/" DESTINATION "${LIB_DIR}"
         PATTERN "cmake" EXCLUDE PATTERN "pkgconfig" EXCLUDE)
    if(EXISTS "${STAGE_DIR}/bin")
        file(GLOB STAGED_DLLS "${STAGE_DIR}/bin/*.dll")
        if(STAGED_DLLS)
            file(COPY ${STAGED_DLLS} DESTINATION "${BIN_DIR}")
        endif()
    endif()
    file(COPY "${STAGE_DIR}/include/" DESTINATION "${CMAKE_SOURCE_DIR}/include")
    file(WRITE "${LIB_DIR}/.deps_ok" "")
endif()

function(sui_find var)
    find_library(${var} NAMES ${ARGN} PATHS "${LIB_DIR}" NO_DEFAULT_PATH)
    if(NOT ${var})
        message(FATAL_ERROR "${ARGN} not found in ${LIB_DIR}, delete it and reconfigure")
    endif()
endfunction()

sui_find(SUI_RAYLIB raylib libraylib)
sui_find(SUI_GLFW glfw3dll glfw3 glfw)
sui_find(SUI_FREETYPE freetype libfreetype)
sui_find(SUI_HB harfbuzz)
sui_find(SUI_HB_SUBSET harfbuzz-subset)

set(SUI_HB_EXTRA "")
foreach(n harfbuzz-gpu harfbuzz-raster harfbuzz-vector)
    find_library(SUI_${n} NAMES ${n} PATHS "${LIB_DIR}" NO_DEFAULT_PATH)
    if(SUI_${n})
        list(APPEND SUI_HB_EXTRA ${SUI_${n}})
    endif()
endforeach()

add_executable(SIMPLEUI_TEST
    src/main.cpp
    include/SUIutils.cpp
)

target_include_directories(SIMPLEUI_TEST PRIVATE
    include
    include/freetype2
    include/harfbuzz
)

target_link_libraries(SIMPLEUI_TEST PRIVATE
    ${SUI_RAYLIB}
    ${SUI_GLFW}
    ${SUI_HB}
    ${SUI_HB_SUBSET}
    ${SUI_HB_EXTRA}
    ${SUI_FREETYPE}
)

if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    target_include_directories(SIMPLEUI_TEST PRIVATE ${GTK3_INCLUDE_DIRS})
    target_link_directories(SIMPLEUI_TEST PRIVATE ${GTK3_LIBRARY_DIRS})
    target_link_libraries(SIMPLEUI_TEST PRIVATE ${GTK3_LIBRARIES})
    target_compile_options(SIMPLEUI_TEST PRIVATE ${GTK3_CFLAGS_OTHER})
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(SIMPLEUI_TEST PRIVATE X11 GL m pthread dl)
    set_target_properties(SIMPLEUI_TEST PROPERTIES
        BUILD_WITH_INSTALL_RPATH ON
        INSTALL_RPATH "$ORIGIN"
    )
endif()

if(WIN32)
    target_link_libraries(SIMPLEUI_TEST PRIVATE winmm gdi32)
endif()

target_compile_definitions(SIMPLEUI_TEST PRIVATE API_LIB_EXPORT=)

if(MSVC)
    target_compile_options(SIMPLEUI_TEST PRIVATE /W0)
else()
    target_compile_options(SIMPLEUI_TEST PRIVATE -w)
    if(WIN32)
        target_link_options(SIMPLEUI_TEST PRIVATE -static)
    endif()
endif()

file(GLOB RUNTIME_DLLS "${BIN_DIR}/*.dll")
if(RUNTIME_DLLS)
    add_custom_command(TARGET SIMPLEUI_TEST POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${RUNTIME_DLLS} $<TARGET_FILE_DIR:SIMPLEUI_TEST>
    )
endif()

if(UNIX AND NOT APPLE)
    add_custom_command(TARGET SIMPLEUI_TEST POST_BUILD
        COMMAND sh -c "cp -a '${LIB_DIR}'/*.so* '$<TARGET_FILE_DIR:SIMPLEUI_TEST>/'"
    )
endif()

add_custom_command(TARGET SIMPLEUI_TEST POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Fonts $<TARGET_FILE_DIR:SIMPLEUI_TEST>/Fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/simpleUI Shaders"
        "$<TARGET_FILE_DIR:SIMPLEUI_TEST>/simpleUI Shaders"
)
