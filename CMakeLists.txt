cmake_minimum_required(VERSION 2.8)

project(cyberway.event-engine-reader)
SET(BOOST_ROOT "~/opt/boost")
FIND_PACKAGE(Boost 1.67 REQUIRED COMPONENTS
    system
    iostreams)
if(APPLE)
  include_directories(/usr/local/include)
  link_directories(/usr/local/lib)
endif(APPLE)
# Uncomment to have the build process verbose
#set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_definitions(-std=c++17)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)

set(outname "cyberway.event-engine-reader")

# Build the executable
add_executable(${outname} ${PROJECT_SOURCE_DIR}/reader.cpp)
target_link_libraries(${outname} Threads::Threads)

