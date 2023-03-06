cmake_minimum_required(VERSION 3.24)
project(RGInterp)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)

message(STATUS "Getting Eigen3")
include(FetchContent)
FetchContent_Declare(
        Eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
#        FIND_PACKAGE_ARGS NAMES Eigen
#        PREFIX ${RoutingLIB_DEPENDENCY_DIR}
        SYSTEM ON
)
FETCHCONTENT_MAKEAVAILABLE(Eigen)

add_library(RGInterp RGInterp/Axis.h RGInterp/Grid.h RGInterp/InterpolationStrategy.h RGInterp/Interpolator.h)

set_target_properties(RGInterp PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(RGInterp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/RGInterp)
target_link_libraries(RGInterp PUBLIC Eigen3::Eigen)

if (RGInterp_TESTING)
    message(STATUS "Configuring RGInterp UnitTests")
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        v1.13.0
            FIND_PACKAGE_ARGS NAMES GTest
            SYSTEM ON
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(tests)
endif()

message(STATUS "Configuring RGInterp Python Bindings")
FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG        v2.10.0
        FIND_PACKAGE_ARGS NAMES pybind11
        SYSTEM ON
)
FetchContent_MakeAvailable(pybind11)

project(${SKBUILD_PROJECT_NAME} VERSION ${SKBUILD_PROJECT_VERSION})

find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(_core MODULE python/rgi_interp_python/main.cpp python/rgi_interp_python/py_interp_3d.cpp python/rgi_interp_python/py_axis.cpp python/rgi_interp_python/py_grid.cpp)
target_link_libraries(_core PUBLIC RGInterp)
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
install (TARGETS _core DESTINATION .)