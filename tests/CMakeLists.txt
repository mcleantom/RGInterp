message(STATUS "Configuring RGInterp Tests")
include(GoogleTest)
# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

enable_testing()

file(GLOB RGInterp_SRC CONFIGURE_DEPENDS "*.cpp")

add_executable(
        RGInterp_unittests
        ${RGInterp_SRC}
        test_interpolator.cpp)

add_dependencies(RGInterp_unittests RGInterp)

target_link_libraries(
        RGInterp_unittests
        PUBLIC
        gtest
        gtest_main
        RGInterp
)

#target_compile_options(RGInterp_unittests PRIVATE -fprofile-arcs -ftest-coverage -O3)

gtest_discover_tests(RGInterp_unittests)

message(STATUS "Configured unittests")
# set_target_properties(routinglib_unittests PROPERTIES PROPERTY VERSION ${BUILD_VERSION})
# set_target_properties(routinglib_unittests PROPERTIES gtest_shuffle ON)