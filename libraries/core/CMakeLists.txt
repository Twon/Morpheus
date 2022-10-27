include(cmake/morpheus_add_library.cmake)
include(cmake/morpheus_add_testing_library.cmake)
include(cmake/morpheus_add_tests.cmake)

add_subdirectory(src)
add_subdirectory(testing)
add_subdirectory(tests)