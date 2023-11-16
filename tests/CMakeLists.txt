include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ULF_COMTests ${SRC})

sanitize("address,undefined")

target_common_warnings(ULF_COMTests PRIVATE)

cpmaddpackage("gh:google/googletest#main")

target_link_libraries(ULF_COMTests PRIVATE GTest::gtest_main GTest::gmock
                                           ULF::COM)

gtest_discover_tests(ULF_COMTests)
