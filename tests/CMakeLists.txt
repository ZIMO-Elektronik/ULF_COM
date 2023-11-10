include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ULFComTests ${SRC})

sanitize("address,undefined")

target_common_warnings(ULFComTests PRIVATE)

cpmaddpackage("gh:google/googletest#main")

target_link_libraries(ULFComTests PRIVATE GTest::gtest_main GTest::gmock
                                          ULF::Com)

gtest_discover_tests(ULFComTests)
