PROJECT(thread-pool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

if (CMAKE_VERSION VERSION_LESS "3.1" OR "${CONAN_CMAKE_CXX_STANDARD}" STREQUAL "20"
        OR "${CONAN_CMAKE_CXX_STANDARD}" STREQUAL "gnu20")
    if(CONAN_STD_CXX_FLAG)
        message(STATUS "Conan setting CXX_FLAGS flags: ${CONAN_STD_CXX_FLAG}")
        set(CMAKE_CXX_FLAGS "-std=${CONAN_STD_CXX_FLAG} ${CMAKE_CXX_FLAGS}")
    endif()
endif()

SET(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -fconcepts-ts")

add_executable(queue queue.cpp)