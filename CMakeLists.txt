cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY https://github.com/ZIMO-Elektronik/CMakeModules
  GIT_TAG v0.3.0
  SOURCE_DIR ${CMAKE_BINARY_DIR}/CMakeModules)
FetchContent_MakeAvailable(CMakeModules)

version_from_git()
project(
  ULFCom
  VERSION ${VERSION_FROM_GIT}
  LANGUAGES CXX)

set(ULFCOM_MAX_DEVICE_NAME_LEN
    32uz
    CACHE STRING "Maximum length of device name string")
set(ULFCOM_MAX_VERSION_LEN
    32uz
    CACHE STRING "Maximum length of version string")

add_library(ULFCom INTERFACE ${SRC})
add_library(ULF::Com ALIAS ULFCom)

target_compile_features(ULFCom INTERFACE cxx_std_23)

target_compile_definitions(
  ULFCom INTERFACE ULFCOM_MAX_DEVICE_NAME_LEN=${ULFCOM_MAX_DEVICE_NAME_LEN}
                   ULFCOM_MAX_VERSION_LEN=${ULFCOM_MAX_VERSION_LEN})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  target_include_directories(ULFCom INTERFACE include)
else()
  target_include_directories(ULFCom SYSTEM INTERFACE include)
endif()

target_common_warnings(ULFCom INTERFACE)

if(NOT TARGET ZTL::ZTL)
  cpmaddpackage("gh:ZIMO-Elektronik/ZTL@0.19.0")
endif()

target_link_libraries(ULFCom INTERFACE ZTL::ZTL)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  file(
    DOWNLOAD
    https://raw.githubusercontent.com/ZIMO-Elektronik/.clang-format/master/.clang-format
    ${CMAKE_CURRENT_LIST_DIR}/.clang-format)
  file(GLOB_RECURSE SRC include/*.*pp tests/*.*pp)
  add_clang_format_target(ULFComFormat OPTIONS -i FILES ${SRC})
endif()

if(BUILD_TESTING
   AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME
   AND CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
  add_subdirectory(examples)
  add_subdirectory(tests)
endif()
