# CMake 최소 버전 명시
cmake_minimum_required(VERSION 3.26.4)

# 프로젝트 이름 및 버전 명시
set(PROJECT_NAME scop)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 환경 변수 세팅
set(WINDOW_NAME "scop")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 640)

# Mac에서 돌릴때 필요한 추가적인 Flag들
if (APPLE)
    set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit -framework OpenGL")
endif()

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE) # close DEPRECATION WARNING...


# 프로젝트 이름 설정
project(${PROJECT_NAME})
# 실행파일의 이름 설정
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/common.h
    src/shader.cpp src/shader.h
    src/program.cpp src/program.h
    src/context.cpp src/context.h
    src/buffer.cpp src/buffer.h
    src/vertex_layout.cpp src/vertex_layout.h
    src/image.cpp src/image.h
    src/texture.cpp src/texture.h
    src/parse.cpp src/parse.h

    src/mathlib/Common.cpp src/mathlib/Common.h
    src/mathlib/Mat2x2.cpp src/mathlib/Mat2x2.h
    src/mathlib/Mat3x3.cpp src/mathlib/Mat3x3.h
    src/mathlib/Mat4x4.cpp src/mathlib/Mat4x4.h
    src/mathlib/Value_ptr.cpp src/mathlib/Value_ptr.h
    src/mathlib/Vector2.cpp src/mathlib/Vector2.h
    src/mathlib/Vector3.cpp src/mathlib/Vector3.h
    src/mathlib/Vector4.cpp src/mathlib/Vector4.h
)

# ExternalProject 관련 명령어 셋 추가
include(Dependency.cmake)

# 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})

# define 매크로로 지정한 값을 실제 컴파일 과정에서 지정
target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
)