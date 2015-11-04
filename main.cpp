#include "b_plus_tree.hpp"
#include "struct.h"

int main() {
	remove("test.info");
	remove("test.index");

	BPlusTree<Value, Pointer> b_plus_tree = BPlusTree<Value, Pointer>("test");

	b_plus_tree.Insert(Value(4, "0.4", 0.4), 4);
	b_plus_tree.Insert(Value(1, "0.1", 0.1), 1);
	b_plus_tree.Insert(Value(5, "0.5", 0.5), 5);
	b_plus_tree.Insert(Value(2, "0.2", 0.2), 2);
	b_plus_tree.Insert(Value(3, "0.3", 0.3), 3);
	b_plus_tree.Insert(Value(9, "0.9", 0.9), 9);
	b_plus_tree.Insert(Value(6, "0.6", 0.6), 6);
	b_plus_tree.Insert(Value(0, "0.0", 0.0), 0);
	b_plus_tree.Insert(Value(8, "0.8", 0.8), 8);
	b_plus_tree.Insert(Value(7, "0.7", 0.7), 7);

	Pointer pointer = b_plus_tree.Find(Value(4, "0.4", 0.4));
	std::cout << pointer.num << std::endl;
	pointer = b_plus_tree.Find(Value(9, "0.9", 0.9));
	std::cout << pointer.num << std::endl;
	pointer = b_plus_tree.Find(Value(1, "0.2", 0.3));
	std::cout << pointer.num << std::endl;

	b_plus_tree.Delete(Value(1, "0.1", 0.1));
	b_plus_tree.Delete(Value(2, "0.2", 0.2));
	b_plus_tree.Delete(Value(3, "0.3", 0.3));
	b_plus_tree.Delete(Value(4, "0.4", 0.4));
	b_plus_tree.Delete(Value(5, "0.5", 0.5));

	return 0;
}
