all: b_plus_tree

b_plus_tree: b_plus_tree.cpp main.cpp
	clang++ main.cpp -o b_plus_tree
	./b_plus_tree
