include_guard()

include("${CMAKE_CURRENT_LIST_DIR}/compiler/clang.cmake")

set(CMAKE_CXX_FLAGS_INIT  "${CMAKE_CXX_FLAGS_INIT} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -stdlib=libc++ -lc++abi")