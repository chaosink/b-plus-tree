cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(b-plus-tree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
if(MSVC)
	add_definitions(-DCONSTEXPR=const -DNOMINMAX -D_CRT_SECURE_NO_WARNINGS)
else()
	add_definitions(-DCONSTEXPR=constexpr)
	set(CXX_WARNINGS "-Wall -Wextra -Wpointer-arith -Wcast-align -fstrict-aliasing -Wno-unused-local-typedefs -Wno-misleading-indentation -Wno-maybe-uninitialized -Wno-int-in-bool-context -Wno-implicit-fallthrough")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_WARNINGS} -fvisibility-inlines-hidden -O3")
endif()

include_directories(
	include
)

add_executable(b_plus_tree_test
	src/b_plus_tree_test.cpp
)
