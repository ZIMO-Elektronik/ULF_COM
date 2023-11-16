file(GLOB_RECURSE SRC *.cpp)
add_executable(ULF_COMExamples ${SRC})

target_common_warnings(ULF_COMExamples PRIVATE)

target_link_libraries(ULF_COMExamples PRIVATE ULF::COM)
