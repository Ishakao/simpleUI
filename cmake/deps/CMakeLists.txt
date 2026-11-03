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
    -DBUILD_TESTING=OFF
)

if(DEPS_COMPILER_ID STREQUAL "MSVC")
    list(APPEND COMMON_ARGS -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded)
elseif(DEPS_COMPILER_ID STREQUAL "GNU")
    list(APPEND COMMON_ARGS -DCMAKE_SHARED_LINKER_FLAGS=-static-libgcc)
endif()

ExternalProject_Add(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG ${GLFW_TAG}
    GIT_SHALLOW ON
    CMAKE_ARGS ${COMMON_ARGS}
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

ExternalProject_Add(freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG ${FT_TAG}
    GIT_SHALLOW ON
    CMAKE_ARGS ${COMMON_ARGS}
        -DBUILD_SHARED_LIBS=ON
        -DFT_DISABLE_ZLIB=ON
        -DFT_DISABLE_BZIP2=ON
        -DFT_DISABLE_PNG=ON
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