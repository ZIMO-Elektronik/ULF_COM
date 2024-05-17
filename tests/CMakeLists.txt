include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ULF_COMTests ${SRC})

sanitize(address,undefined)

target_common_warnings(ULF_COMTests PRIVATE)

cpmaddpackage(
  NAME
  googletest
  GITHUB_REPOSITORY
  "google/googletest"
  GIT_TAG
  main
  SYSTEM
  YES
  OPTIONS
  "INSTALL_GTEST OFF")

target_link_libraries(ULF_COMTests PRIVATE GTest::gtest_main GTest::gmock
                                           ULF::COM)

gtest_discover_tests(ULF_COMTests)
