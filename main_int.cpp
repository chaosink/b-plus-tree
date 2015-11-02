#include <iostream>
#include "b_plus_tree.hpp"
using namespace std;

int main() {
	int pointer_num = 5;

	BPlusTree<int> b_plus_tree = BPlusTree<int>(pointer_num);

	Node<int> *node;



	b_plus_tree.Insert(30, 30);
	b_plus_tree.Insert(10, 10);
	b_plus_tree.Insert(40, 40);
	b_plus_tree.Insert(55, 55);
	b_plus_tree.Insert(45, 45);
	b_plus_tree.Insert(70, 70);
	b_plus_tree.Insert(80, 80);
	b_plus_tree.Insert(20, 20);
	b_plus_tree.Insert(43, 43);
	b_plus_tree.Insert(60, 60);
	b_plus_tree.Insert(99, 99);
	b_plus_tree.Insert(95, 95);
	b_plus_tree.Insert(91, 91);	
	b_plus_tree.Insert(63, 63);	
	b_plus_tree.Insert(67, 67);
	b_plus_tree.Insert(65, 65);
	b_plus_tree.Insert(1, 1);
	b_plus_tree.Insert(5, 5);
	b_plus_tree.Insert(7, 7);
	b_plus_tree.Insert(9, 9);
	b_plus_tree.Insert(31, 31);
	b_plus_tree.Insert(37, 37);
	b_plus_tree.Insert(35, 35);
	b_plus_tree.Insert(33, 33);
	b_plus_tree.Insert(69, 69);
	b_plus_tree.Insert(36, 36);
	b_plus_tree.Insert(38, 38);
	b_plus_tree.Insert(39, 39);
	b_plus_tree.Insert(41, 41);
	b_plus_tree.Insert(42, 42);
	b_plus_tree.Insert(44, 44);



	b_plus_tree.Delete(9);
	b_plus_tree.Delete(10);
	b_plus_tree.Delete(35);
	b_plus_tree.Delete(37);
	b_plus_tree.Delete(33);
	b_plus_tree.Delete(43);
	b_plus_tree.Delete(38);
	b_plus_tree.Delete(36);
	b_plus_tree.Delete(42);
	b_plus_tree.Delete(40);
	b_plus_tree.Delete(39);
	b_plus_tree.Delete(60);
	b_plus_tree.Delete(55);
	b_plus_tree.Delete(44);
	b_plus_tree.Delete(41);
	b_plus_tree.Delete(95);
	b_plus_tree.Delete(63);
	b_plus_tree.Delete(67);
	b_plus_tree.Delete(65);
	b_plus_tree.Delete(70);
	b_plus_tree.Delete(7);
	b_plus_tree.Delete(1);
	b_plus_tree.Delete(5);
	b_plus_tree.Delete(20);
	b_plus_tree.Delete(30);
	b_plus_tree.Delete(91);
	b_plus_tree.Delete(69);
	b_plus_tree.Delete(99);
	b_plus_tree.Delete(31);
	b_plus_tree.Delete(45);
	b_plus_tree.Delete(80);
	b_plus_tree.Delete(70);



	node = b_plus_tree.GetNode(0);
	cout << node->num << " " << node->value_num << " " << (int)node->state << endl;
	for(int i = 0; i < pointer_num - 1; i++) cout << node->pointer[i] << " [" << node->value[i] << "] ";
	cout << node->pointer[pointer_num - 1] << endl;

	node = b_plus_tree.GetNode(0);
	while(node->pointer[pointer_num - 1] != -1) {
		cout << node->num << " ";
		node = b_plus_tree.GetNode(node->pointer[pointer_num - 1]);
	}
	cout << node->num << endl;



	return 0;
}
