all: b_plus_tree

b_plus_tree: b_plus_tree.cpp main.cpp
	clang++ main.cpp b_plus_tree.cpp -o b_plus_tree
