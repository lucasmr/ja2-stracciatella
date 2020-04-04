# \file dependencies/lib-gtest/CMakeLists.txt

message(STATUS "<gtest>")

# create getter
set(SRC_DIR "${CMAKE_BINARY_DIR}/lib-gtest/src")
set(BUILD_DIR "${CMAKE_BINARY_DIR}/lib-gtest/build")
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/getter/CMakeLists.txt.in"
    "${CMAKE_CURRENT_BINARY_DIR}/getter/CMakeLists.txt"
    @ONLY
)

# execute getter
execute_process(COMMAND ${CMAKE_COMMAND} . "-G${CMAKE_GENERATOR}" WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/getter")
execute_process(COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}/getter")

# library
set(BUILD_GMOCK OFF CACHE BOOL "no gmock" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "no install, gtest is integrated" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "always use shared (DLL) run-time lib" FORCE)
set(gtest_disable_pthreads ON CACHE BOOL "no pthreads in gtest" FORCE)
mark_as_advanced(BUILD_GMOCK INSTALL_GTEST gtest_force_shared_crt gtest_disable_pthreads)
add_subdirectory("${SRC_DIR}" "${BUILD_DIR}")
set(GTEST_LIBRARIES gtest PARENT_SCOPE)

message(STATUS "</gtest>")
