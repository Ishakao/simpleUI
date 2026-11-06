cmake_minimum_required(VERSION 3.18)
project(simpleUI_deps NONE)

include(ExternalProject)

set(COMMON_ARGS
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_INSTALL_PREFIX=${DEPS_PREFIX}
    -DCMAKE_PREFIX_PATH=${DEPS_PREFIX}
    -DCMAKE_C_COMPILER=${DEPS_C_COMPILER}
    -DCMAKE_CXX_COMPILER=${DEPS_CXX_COMPILER}
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5
    -DCMAKE_POLICY_DEFAULT_CMP0074=NEW
    -DCMAKE_POLICY_DEFAULT_CMP0144=NEW
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON
    -DBUILD_TESTING=OFF
    -DCMAKE_INSTALL_LIBDIR=lib
)

set(GLFW_EXTRA_ARGS "")

if(DEPS_COMPILER_ID STREQUAL "MSVC")
    list(APPEND COMMON_ARGS -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded)
    set(ZLIB_LIB_NAME zlibstatic.lib)
    set(PNG_LIB_NAME libpng16_static.lib)
else()
    if(DEPS_COMPILER_ID STREQUAL "GNU")
        list(APPEND COMMON_ARGS -DCMAKE_SHARED_LINKER_FLAGS=-static-libgcc)
    endif()
    set(ZLIB_LIB_NAME libz.a)
    set(PNG_LIB_NAME libpng16.a)
endif()

if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)

    set(MISSING_APT "")

    pkg_check_modules(SYS_X11 QUIET x11 xrandr xinerama xcursor xi)
    if(NOT SYS_X11_FOUND)
        list(APPEND MISSING_APT libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libxext-dev)
    endif()

    find_path(SYS_GL_HEADER GL/gl.h)
    if(NOT SYS_GL_HEADER)
        list(APPEND MISSING_APT libgl-dev libglu1-mesa-dev libegl-dev libopengl-dev)
    endif()

    if(MISSING_APT)
        list(REMOVE_DUPLICATES MISSING_APT)
        list(JOIN MISSING_APT " " MISSING_APT_STR)
        message(FATAL_ERROR "missing system packages, run: sudo apt install ${MISSING_APT_STR} pkg-config")
    endif()

    pkg_check_modules(SYS_WL QUIET wayland-client wayland-cursor wayland-egl wayland-protocols xkbcommon)
    find_program(SYS_WAYLAND_SCANNER wayland-scanner)

    if(SYS_WL_FOUND AND SYS_WAYLAND_SCANNER)
        list(APPEND GLFW_EXTRA_ARGS -DGLFW_BUILD_WAYLAND=ON -DGLFW_BUILD_X11=ON)
    else()
        message(STATUS "wayland deps not found, building glfw with x11 only (sudo apt install libwayland-dev libwayland-bin wayland-protocols libxkbcommon-dev)")
        list(APPEND GLFW_EXTRA_ARGS -DGLFW_BUILD_WAYLAND=OFF -DGLFW_BUILD_X11=ON)
    endif()
endif()

set(ZLIB_ARGS
    -DZLIB_LIBRARY=${DEPS_PREFIX}/lib/${ZLIB_LIB_NAME}
    -DZLIB_INCLUDE_DIR=${DEPS_PREFIX}/include
    -DZLIB_USE_STATIC_LIBS=ON
)

set(PNG_ARGS
    -DPNG_LIBRARY=${DEPS_PREFIX}/lib/${PNG_LIB_NAME}
    -DPNG_PNG_INCLUDE_DIR=${DEPS_PREFIX}/include
)

ExternalProject_Add(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG ${GLFW_TAG}
    GIT_SHALLOW ON
    CMAKE_ARGS ${COMMON_ARGS}
        ${GLFW_EXTRA_ARGS}
        -DBUILD_SHARED_LIBS=ON
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
)

ExternalProject_Add(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG ${RAYLIB_TAG}
    GIT_SHALLOW ON
    DEPENDS glfw
    CMAKE_ARGS ${COMMON_ARGS}
        -DBUILD_SHARED_LIBS=ON
        -DBUILD_EXAMPLES=OFF
        -DUSE_EXTERNAL_GLFW=ON
)

ExternalProject_Add(zlib
    GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG ${ZLIB_TAG}
    GIT_SHALLOW ON
    CMAKE_ARGS ${COMMON_ARGS}
        -DZLIB_BUILD_SHARED=OFF
        -DZLIB_BUILD_STATIC=ON
        -DZLIB_BUILD_TESTING=OFF
        -DZLIB_BUILD_EXAMPLES=OFF
)

ExternalProject_Add(libpng
    GIT_REPOSITORY https://github.com/pnggroup/libpng.git
    GIT_TAG ${PNG_TAG}
    GIT_SHALLOW ON
    DEPENDS zlib
    CMAKE_ARGS ${COMMON_ARGS}
        ${ZLIB_ARGS}
        -DBUILD_SHARED_LIBS=OFF
        -DPNG_SHARED=OFF
        -DPNG_TESTS=OFF
        -DPNG_TOOLS=OFF
        -DPNG_FRAMEWORK=OFF
)

ExternalProject_Add(freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG ${FT_TAG}
    GIT_SHALLOW ON
    DEPENDS libpng zlib
    CMAKE_ARGS ${COMMON_ARGS}
        ${ZLIB_ARGS}
        ${PNG_ARGS}
        -DBUILD_SHARED_LIBS=ON
        -DFT_REQUIRE_PNG=ON
        -DFT_REQUIRE_ZLIB=ON
        -DFT_DISABLE_BZIP2=ON
        -DFT_DISABLE_BROTLI=ON
        -DFT_DISABLE_HARFBUZZ=ON
)

ExternalProject_Add(harfbuzz
    GIT_REPOSITORY https://github.com/harfbuzz/harfbuzz.git
    GIT_TAG ${HB_TAG}
    GIT_SHALLOW ON
    DEPENDS freetype
    CMAKE_ARGS ${COMMON_ARGS}
        -DBUILD_SHARED_LIBS=OFF
        -DHB_HAVE_FREETYPE=ON
        -DHB_BUILD_SUBSET=ON
        -DHB_BUILD_UTILS=OFF
        -DHB_HAVE_GLIB=OFF
        -DHB_HAVE_ICU=OFF
        -DHB_HAVE_GRAPHITE2=OFF
)
