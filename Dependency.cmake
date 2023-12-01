include(ExternalProject)

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# spdlog: fast logger library
# spdlog를 다운받아서 가져옴. 로그를 보는데 용이.
ExternalProject_Add(
    dep_spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x" #태그(특정 버전 지정)이름, 브랜치 정보
    GIT_SHALLOW 1 #shallow : 활성화(1)되면 가장 최신의 것만 다운로드
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} #cmake configure 할때 넣는 인자, -D: definition
    TEST_COMMAND ""
)

# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep_spdlog)

# OS 별 생성 파일이 .lib 와 .a 파일로 달라지므로, Mac 기준에 맞춰서 해당 디렉토리에 있는 링크를 제대로 맞춰줌.
if (APPLE)
    set(DEP_LIBS ${DEP_LIBS} libspdlog.a)
endif()
if (WIN32)
    set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)
endif()

# glfw 설치
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.8"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    TEST_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
)

set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)

# glad
ExternalProject_Add(
    dep_glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
    GIT_TAG "v0.1.34"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLAD_INSTALL=ON
    TEST_COMMAND ""
    )
set(DEP_LIST ${DEP_LIST} dep_glad)
set(DEP_LIBS ${DEP_LIBS} glad)

# stb 설치
ExternalProject_Add(
    dep_stb
    GIT_REPOSITORY "https://github.com/nothings/stb"
    GIT_TAG "master"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    # 헤더파일만 가져오기에 build 와 configure를 막아둔다.
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    TEST_COMMAND ""
    # 대신 install command를 따로 지정한다.
    # ${CMAKE_COMMAND} -E copy 로 stb_image.h를 복사하기에, cmake 명령어를 통해 사용해서 os간 차이가 없게끔 한다.
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_BINARY_DIR}/dep_stb-prefix/src/dep_stb/stb_image.h
        ${DEP_INSTALL_DIR}/include/stb/stb_image.h
)
set(DEP_LIST ${DEP_LIST} dep_stb)

# glm
ExternalProject_Add(
    dep_glm
    GIT_REPOSITORY "https://github.com/g-truc/glm"
    GIT_TAG "0.9.9.8"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    TEST_COMMAND ""
    # 위의 stb library를 추가한 방식과 동일하게 가져오나, copy_directory를 통해 디렉토리 자체를 복사해온다.
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_BINARY_DIR}/dep_glm-prefix/src/dep_glm/glm
        ${DEP_INSTALL_DIR}/include/glm
)

set(DEP_LIST ${DEP_LIST} dep_glm)

include(FetchContent)
FetchContent_Declare(
        dep_imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        GIT_TAG "master"
)
FetchContent_MakeAvailable(dep_imgui)

set(imgui_dir ${PROJECT_BINARY_DIR}/_deps/dep_imgui-src)

file(COPY ${imgui_dir}/imconfig.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)
file(COPY ${imgui_dir}/imgui.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)
file(COPY ${imgui_dir}/imgui_internal.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)
file(COPY ${imgui_dir}/imstb_rectpack.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)
file(COPY ${imgui_dir}/imstb_textedit.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)
file(COPY ${imgui_dir}/imstb_truetype.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)
file(COPY ${imgui_dir}/misc/cpp/imgui_stdlib.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)
file(COPY ${imgui_dir}/backends/imgui_impl_glfw.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)
file(COPY ${imgui_dir}/backends/imgui_impl_opengl3.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)
file(COPY ${imgui_dir}/backends/imgui_impl_opengl3_loader.h DESTINATION ${DEP_INCLUDE_DIR}/imgui)

# add all source code
set(IMGUI_CODE
    ${imgui_dir}/imgui.cpp
    ${imgui_dir}/imgui_draw.cpp
    ${imgui_dir}/imgui_tables.cpp
    ${imgui_dir}/imgui_widgets.cpp
    ${imgui_dir}/misc/cpp/imgui_stdlib.cpp
    ${imgui_dir}/backends/imgui_impl_glfw.cpp
    ${imgui_dir}/backends/imgui_impl_opengl3.cpp
)
# make library
add_library(imgui ${IMGUI_CODE})
# change library path to DEP_LIB_DIR
set_target_properties(imgui PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${DEP_LIB_DIR})
# set library path
set(IMGUI_INCLUDE_DIR ${DEP_INCLUDE_DIR}/imgui)
# set include header for imgui library
target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE_DIR})
target_include_directories(imgui PUBLIC ${DEP_INCLUDE_DIR})
# others for imgui
add_dependencies(imgui ${DEP_LIST})
# for main target
set(DEP_LIST ${DEP_LIST} imgui)
set(DEP_LIBS ${DEP_LIBS} imgui)

# assimp
ExternalProject_Add(
  dep_assimp
  GIT_REPOSITORY "https://github.com/assimp/assimp"
  GIT_TAG "v5.0.1"
  GIT_SHALLOW 1
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
      -DBUILD_SHARED_LIBS=OFF
      -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
      -DASSIMP_BUILD_TESTS=OFF
      -DASSIMP_INJECT_DEBUG_POSTFIX=OFF
      -DASSIMP_BUILD_ZLIB=ON
  TEST_COMMAND ""
  )
set(DEP_LIST ${DEP_LIST} dep_assimp)
set(DEP_LIBS ${DEP_LIBS}
    assimp
    zlibstatic
    IrrXML
  )