cmake_minimum_required(VERSION 3.20)
project(AP_Talebi LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENGINE_SOURCES
        src/main.cpp
)

set(ENGINE_HEADERS
        src/config.h
)

# ---------------------------------------------------------------------------
# 2. ISOLATE THIRD-PARTY (GLAD)
# ---------------------------------------------------------------------------
# We treat GLAD as its own little internal library so it doesn't rot your src
add_library(glad_lib STATIC deps/glad/src/glad.c)
target_include_directories(glad_lib PUBLIC deps/glad/include)

# ---------------------------------------------------------------------------
# 3. MAIN TARGET
# ---------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# 4. INCLUDE PATHS
# Use PRIVATE for apps. This keeps your include paths from leaking.
target_include_directories(${PROJECT_NAME} PRIVATE
        src
        src/vendors
        include
)

# 5. DEPENDENCIES & LINKING
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Link your app to glad_lib and the system libs
target_link_libraries(${PROJECT_NAME} PRIVATE
        glad_lib
        glfw
        OpenGL::GL
)