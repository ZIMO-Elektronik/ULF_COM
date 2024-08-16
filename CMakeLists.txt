cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY "https://github.com/ZIMO-Elektronik/CMakeModules"
  GIT_TAG v0.9.2
  SOURCE_DIR ${CMAKE_BINARY_DIR}/CMakeModules)
FetchContent_MakeAvailable(CMakeModules)

version_from_git()
project(
  ULF_COM
  VERSION ${VERSION_FROM_GIT}
  LANGUAGES CXX)

set(ULF_COM_MAX_DEVICE_NAME_LEN
    32uz
    CACHE STRING "Maximum length of device name string")
set(ULF_COM_MAX_VERSION_LEN
    32uz
    CACHE STRING "Maximum length of version string")

add_library(ULF_COM INTERFACE ${SRC})
add_library(ULF::COM ALIAS ULF_COM)

target_compile_features(ULF_COM INTERFACE cxx_std_23)

target_compile_definitions(
  ULF_COM INTERFACE ULF_COM_MAX_DEVICE_NAME_LEN=${ULF_COM_MAX_DEVICE_NAME_LEN}
                    ULF_COM_MAX_VERSION_LEN=${ULF_COM_MAX_VERSION_LEN})

if(PROJECT_IS_TOP_LEVEL)
  target_include_directories(ULF_COM INTERFACE include)
else()
  target_include_directories(ULF_COM SYSTEM INTERFACE include)
endif()

target_common_warnings(ULF_COM INTERFACE)

if(NOT TARGET ZTL::ZTL)
  cpmaddpackage("gh:ZIMO-Elektronik/ZTL@0.19.0")
endif()

target_link_libraries(ULF_COM INTERFACE ZTL::ZTL)

if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
  add_subdirectory(examples)
  file(
    DOWNLOAD
    "https://github.com/ZIMO-Elektronik/.github/raw/master/data/.clang-format"
    ${CMAKE_CURRENT_LIST_DIR}/.clang-format)
  file(GLOB_RECURSE SRC include/*.*pp tests/*.*pp)
  add_clang_format_target(ULF_COMFormat OPTIONS -i FILES ${SRC})
endif()

if(BUILD_TESTING AND CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
  add_subdirectory(tests)
endif()
