cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(demo1 demo1.c)
add_test(test-demo1 demo1)

add_executable(demo16 demo16.cc)
add_test(test-demo16 demo16)

add_executable(mycurl mycurl.cc)
add_test(test-mycurl mycurl)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
