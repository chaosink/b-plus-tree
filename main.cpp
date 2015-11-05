#include "b_plus_tree.hpp"
#include "value_pointer.hpp"

int main() {
	remove("test.info");
	remove("test.index");

	BPlusTree<Value, Pointer> b_plus_tree = BPlusTree<Value, Pointer>("test");

	b_plus_tree.Insert(Value(4, "4444444", 0.4), 4);
	b_plus_tree.Insert(Value(1, "1111111", 0.1), 1);
	b_plus_tree.Insert(Value(5, "5555555", 0.5), 5);
	b_plus_tree.Insert(Value(2, "2222222", 0.2), 2);
	b_plus_tree.Insert(Value(3, "3333333", 0.3), 3);
	b_plus_tree.Insert(Value(9, "9999999", 0.9), 9);
	b_plus_tree.Insert(Value(6, "6666666", 0.6), 6);
	b_plus_tree.Insert(Value(0, "0000000", 0.0), 0);
	b_plus_tree.Insert(Value(8, "8888888", 0.8), 8);
	b_plus_tree.Insert(Value(7, "7777777", 0.7), 7);

	Pointer pointer = b_plus_tree.Find(Value(4, "4444444", 0.4));
	std::cout << pointer.num << std::endl;
	pointer = b_plus_tree.Find(Value(9, "9999999", 0.9));
	std::cout << pointer.num << std::endl;
	pointer = b_plus_tree.Find(Value(1, "1111111", 0.1));
	std::cout << pointer.num << std::endl;

	b_plus_tree.Delete(Value(1, "1111111", 0.1));
	b_plus_tree.Delete(Value(2, "2222222", 0.2));
	b_plus_tree.Delete(Value(3, "3333333", 0.3));
	b_plus_tree.Delete(Value(4, "4444444", 0.4));
	b_plus_tree.Delete(Value(5, "5555555", 0.5));

	b_plus_tree.Insert(Value(4, "4444444", 0.4), 4);
	b_plus_tree.Insert(Value(1, "1111111", 0.1), 1);
	b_plus_tree.Insert(Value(5, "5555555", 0.5), 5);
	b_plus_tree.Insert(Value(2, "2222222", 0.2), 2);
	b_plus_tree.Insert(Value(3, "3333333", 0.3), 3);

	return 0;
}
