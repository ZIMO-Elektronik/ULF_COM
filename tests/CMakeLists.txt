include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ULF_COMTests ${SRC})

sanitize(address,undefined)

target_common_warnings(ULF_COMTests PRIVATE)
target_common_errors(ULF_COMTests INTERFACE -Werror)

cpmaddpackage(URI "gh:google/googletest#main" OPTIONS "INSTALL_GTEST OFF")

target_link_libraries(ULF_COMTests PRIVATE GTest::gtest_main GTest::gmock
                                           ULF::COM)

gtest_discover_tests(ULF_COMTests)
