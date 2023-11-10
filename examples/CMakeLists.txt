file(GLOB_RECURSE SRC *.cpp)
add_executable(ULFComExamples ${SRC})

target_common_warnings(ULFComExamples PRIVATE)

target_link_libraries(ULFComExamples PRIVATE ULF::Com)
