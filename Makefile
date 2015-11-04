all: b_plus_tree

b_plus_tree: b_plus_tree.cpp b_plus_tree.hpp buffer_manager.cpp buffer_manager.hpp main.cpp struct.h
	clang++ buffer_manager.cpp main.cpp -o b_plus_tree -g
