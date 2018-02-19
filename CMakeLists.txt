cmake_minimum_required (VERSION 3.0)


project (symmat CXX)

set(SOURCE_NAME   "symmat_source")
set(TEST_NAME     "symmat_test")
set(PATH_BUILD    "${PROJECT_SOURCE_DIR}/build")
set(PATH_INCLUDE  "${PROJECT_SOURCE_DIR}/include")
set(PATH_SOURCE   "${PROJECT_SOURCE_DIR}/src")
set(PATH_TEST     "${PROJECT_SOURCE_DIR}/test")

file(GLOB SOURCES_LIB "${PATH_SOURCE}/*.cpp")
file(GLOB SOURCES_TEST "${PATH_TEST}/*.cpp")
file(GLOB HEADER_FILES "${PATH_INCLUDE}/*.h")

find_package(Eigen3 REQUIRED)

include_directories(${PATH_INCLUDE})

add_library(${SOURCE_NAME} "${SOURCES_LIB}")
target_link_libraries(${SOURCE_NAME} Eigen3::Eigen)

enable_testing()

set(tests
  eigen_test
  )

list(LENGTH tests temp_len)
math(EXPR test_len "${temp_len} - 1")

foreach(index RANGE ${test_len})
  list(GET tests ${index} test)
  add_executable(${test} ${PATH_TEST}/${test}.cpp)
  target_link_libraries(${test} ${SOURCE_NAME})
  add_test(${test} ${test})
endforeach()


add_executable(${PROJECT_NAME} ${PATH_SOURCE}/Main.cpp)
target_link_libraries(${PROJECT_NAME} ${SOURCE_NAME} Eigen3::Eigen)
