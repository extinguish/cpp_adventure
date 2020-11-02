cmake_minimum_required(VERSION 2.8)
project(boost_lab)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
find_package(Boost REQUIRED COMPONENTS
        filesystem   # 我的工程中只使用了 boost 的 filesystem 功能,因此这里只有一个组件
        )
if (NOT Boost_FOUND)
    message("Not found Boost")
endif ()

include_directories(${Boost_INCLUDE_DIRS})
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")

add_executable(boost_test BoostTest.cpp)
target_link_libraries(boost_lab ${Boost_LIBRARIES})


