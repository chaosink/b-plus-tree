#include "b_plus_tree.hpp"
#include "struct.h"

int main() {
	int pointer_num = 3;

	BPlusTree<Value> b_plus_tree = BPlusTree<Value>(pointer_num);

	Node<Value> *node;


	b_plus_tree.Insert(Value(4, 0.4), 4);
	b_plus_tree.Insert(Value(1, 0.1), 1);
	b_plus_tree.Insert(Value(5, 0.5), 5);
	b_plus_tree.Insert(Value(2, 0.2), 2);
	b_plus_tree.Insert(Value(3, 0.3), 3);



	node = b_plus_tree.GetNode(2);
	std::cout << node->num << " " << node->value_num << " " << (int)node->state << std::endl;
	for(int i = 0; i < pointer_num - 1; i++) std::cout << node->pointer[i] << " [" << node->value[i] << "] ";
	std::cout << node->pointer[pointer_num - 1] << std::endl;



	b_plus_tree.Delete(Value(1, 0.1));
	b_plus_tree.Delete(Value(2, 0.2));
	b_plus_tree.Delete(Value(3, 0.3));
	b_plus_tree.Delete(Value(4, 0.4));
	b_plus_tree.Delete(Value(5, 0.5));



	node = b_plus_tree.GetNode(2);
	std::cout << node->num << " " << node->value_num << " " << (int)node->state << std::endl;
	for(int i = 0; i < pointer_num - 1; i++) std::cout << node->pointer[i] << " [" << node->value[i] << "] ";
	std::cout << node->pointer[pointer_num - 1] << std::endl;

	node = b_plus_tree.GetNode(0);
	while(node->pointer[pointer_num - 1] != -1) {
		std::cout << node->num << " ";
		node = b_plus_tree.GetNode(node->pointer[pointer_num - 1]);
	}
	std::cout << node->num << std::endl;



	return 0;
}
