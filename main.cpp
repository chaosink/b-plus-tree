#include "b_plus_tree.hpp"
#include "value_pointer.hpp"

#define N 100000

int main() {
	remove("test.info");
	remove("test.index");

	BPlusTree<Value, Pointer> b_plus_tree = BPlusTree<Value, Pointer>("test");
	Node<Value, Pointer> node;
	int pointer_num = (BLOCK_SIZE - sizeof(int) - sizeof(char) - sizeof(int) - sizeof(Pointer)) / (sizeof(Pointer) + sizeof(Value)) + 1;
	cout << pointer_num << endl;
	cout << sizeof(Value) << endl;

	for(int i = 0; i < N; i++) {
		char buffer[256];
		sprintf(buffer, "%d", i);
		b_plus_tree.Insert(Value(i, buffer,i), i);
	}

	node = b_plus_tree.GetNode(6);
	std::cout << *(node.num) << " " << *(node.value_num) << " " << (int)*(node.state) << std::endl;
	for(int i = 0; i < pointer_num - 1; i++) std::cout << node.pointer[i] << " [" << node.value[i] << "] ";
	std::cout << node.pointer[pointer_num - 1] << std::endl;

	for(int i = 0; i < N; i++) {
		char buffer[256];
		sprintf(buffer, "%d", i);
		b_plus_tree.Delete(Value(i, buffer,i));
	}

/*	node = b_plus_tree.GetNode(0);
	while(node.pointer[pointer_num - 1].num != -1) {
		std::cout << *node.num << " ";
		node = b_plus_tree.GetNode(node.pointer[pointer_num - 1].num);
	}
	std::cout << *node.num << std::endl;*/

/*	std::vector<Pointer> p = b_plus_tree.FindFrom(Value(1, "1", 0.1), true);
	for(unsigned int i = 0; i < p.size(); i++)
		std::cout << p[i].num << " ";
	std::cout << std::endl;

	p = b_plus_tree.FindTo(Value(100, "100", 10), true);
	for(unsigned int i = 0; i < p.size(); i++)
		std::cout << p[i].num << " ";
	std::cout << std::endl;

	p = b_plus_tree.FindFromTo(Value(1, "1", 0.1), true, Value(1, "1", 0.1), true);
	for(unsigned int i = 0; i < p.size(); i++)
		std::cout << p[i].num << " ";
	std::cout << std::endl;*/

	return 0;
}
