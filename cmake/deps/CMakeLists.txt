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
    -DCMAKE_BUILD_RPATH_USE_ORIGIN=ON
    -DCMAKE_INSTALL_RPATH=$ORIGIN
    -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON
)

set(GLFW_EXTRA_ARGS "")

if(DEPS_MSVC_LIKE)
    list(APPEND COMMON_ARGS -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDLL)
    set(ZLIB_CANON zlibstatic.lib)
    set(ZLIB_CANDIDATES "zlibstatic.lib|zs.lib|zlib.lib")
    set(PNG_CANON libpng16_static.lib)
    set(PNG_CANDIDATES "libpng16_static.lib|png16_static.lib|libpng16.lib|png16.lib")
else()
    if(DEPS_COMPILER_ID STREQUAL "GNU")
        list(APPEND COMMON_ARGS -DCMAKE_SHARED_LINKER_FLAGS=-static-libgcc)
    endif()
    set(ZLIB_CANON libz.a)
    set(ZLIB_CANDIDATES "libz.a|libzlibstatic.a|libzs.a")
    set(PNG_CANON libpng16.a)
    set(PNG_CANDIDATES "libpng16.a|libpng.a|libpng16_static.a")
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
    -DZLIB_LIBRARY=${DEPS_PREFIX}/lib/${ZLIB_CANON}
    -DZLIB_INCLUDE_DIR=${DEPS_PREFIX}/include
    -DZLIB_USE_STATIC_LIBS=ON
)

set(PNG_ARGS
    -DPNG_LIBRARY=${DEPS_PREFIX}/lib/${PNG_CANON}
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

ExternalProject_Add_Step(zlib normalize
    DEPENDEES install
    COMMAND ${CMAKE_COMMAND}
        -DLIBDIR=${DEPS_PREFIX}/lib
        -DCANON=${ZLIB_CANON}
        "-DCANDIDATES=${ZLIB_CANDIDATES}"
        -P ${CMAKE_CURRENT_LIST_DIR}/normalize_lib.cmake
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

ExternalProject_Add_Step(libpng normalize
    DEPENDEES install
    COMMAND ${CMAKE_COMMAND}
        -DLIBDIR=${DEPS_PREFIX}/lib
        -DCANON=${PNG_CANON}
        "-DCANDIDATES=${PNG_CANDIDATES}"
        -P ${CMAKE_CURRENT_LIST_DIR}/normalize_lib.cmake
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
