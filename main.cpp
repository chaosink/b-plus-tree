#include "b_plus_tree.hpp"
#include "value_pointer.hpp"
#include <cstdio>

#define N 500

int main() {
	remove("test.info");
	remove("test.index");

	BPlusTree<Value, Pointer> b_plus_tree = BPlusTree<Value, Pointer>("test");
	Pointer pointer;

	for(int i = 0; i < N; i++) {
		char buffer[256];
		sprintf(buffer, "%d", i);
		b_plus_tree.Insert(Value(i, buffer,i), i);
	}

/*	pointer = b_plus_tree.Find(Value(496, "496", 49.6));
	std::cout << pointer.num << std::endl;

	std::vector<Pointer> p = b_plus_tree.FindFrom(Value(1, "1", 0.1), true);
	for(unsigned int i = 0; i < p.size(); i++)
	        std::cout << p[i].num << " ";
	std::cout << std::endl;

	p = b_plus_tree.FindTo(Value(100, "100", 10), true);
	for(unsigned int i = 0; i < p.size(); i++)
	        std::cout << p[i].num << " ";
	std::cout << std::endl;

	p = b_plus_tree.FindFromTo(Value(10, "10", 1), true, Value(100, "100", 10), true);
	for(unsigned int i = 0; i < p.size(); i++)
	        std::cout << p[i].num << " ";
	std::cout << std::endl;*/

	std::cout << "here" << std::endl;
	for(int i = 0; i < N; i++) {
		char buffer[256];
		sprintf(buffer, "%d", i);
		b_plus_tree.Delete(Value(i, buffer,i));
	}
	std::cout << "here" << std::endl;

	pointer = b_plus_tree.Find(Value(499, "499", 49.9));
	std::cout << pointer.num << std::endl;

	return 0;
}
