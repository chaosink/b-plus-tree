#include <iostream>
#include "b_plus_tree.hpp"
using namespace std;

#define dd cout << "--------------------------------------------------";
#define d cout << "--------------------------------------------------here" << endl;

int main() {
	BPlusTree b_plus_tree = BPlusTree();
	Node *node;

	b_plus_tree.Insert(10, 10);
	b_plus_tree.Delete(10);
	b_plus_tree.Insert(10, 10);

	b_plus_tree.Insert(40, 40);
	b_plus_tree.Insert(30, 30);

	node = b_plus_tree.FindLeafNode(1);
dd	cout << node->num << " " << node->value_num << endl;
dd	for(int i = 0; i < node->value_num; i++) cout << node->pointer[i] << "," << node->value[i] << " "; cout << endl;



	b_plus_tree.Insert(50, 50);
	b_plus_tree.Insert(20, 20);
	b_plus_tree.Insert(80, 80);

	node = b_plus_tree.FindLeafNode(4);
dd	cout << node->num << " " << node->value_num << endl;
dd	for(int i = 0; i < node->value_num; i++) cout << node->pointer[i] << "," << node->value[i] << " "; cout << endl;



	b_plus_tree.Insert(100, 100);
	b_plus_tree.Insert(90, 90);

	node = b_plus_tree.FindLeafNode(10);
dd	cout << node->num << " " << node->value_num << endl;
dd	for(int i = 0; i < node->value_num; i++) cout << node->pointer[i] << "," << node->value[i] << " "; cout << endl;



	b_plus_tree.Insert(60, 60);
	b_plus_tree.Insert(70, 70);

	node = b_plus_tree.FindLeafNode(9);
dd	cout << node->num << " " << node->value_num << endl;
dd	for(int i = 0; i < node->value_num; i++) cout << node->pointer[i] << "," << node->value[i] << " "; cout << endl;



	b_plus_tree.Insert(110, 110);

	node = b_plus_tree.FindLeafNode(9);
dd	cout << node->num << " " << node->value_num << endl;
dd	for(int i = 0; i < node->value_num; i++) cout << node->pointer[i] << "," << node->value[i] << " "; cout << endl;



	b_plus_tree.Insert(54, 54);
	b_plus_tree.Insert(53, 53);
	b_plus_tree.Insert(51, 51);
	b_plus_tree.Insert(52, 52);
	b_plus_tree.Insert(71, 71);
	b_plus_tree.Insert(111, 111);
	b_plus_tree.Insert(112, 112);

	b_plus_tree.Delete(50);
	b_plus_tree.Delete(53);
	b_plus_tree.Delete(52);
	b_plus_tree.Delete(20);
	b_plus_tree.Delete(10);
	b_plus_tree.Delete(30);
	b_plus_tree.Delete(40);
	b_plus_tree.Delete(51);
	b_plus_tree.Delete(54);
	b_plus_tree.Delete(80);
	b_plus_tree.Delete(111);
	b_plus_tree.Delete(90);
	b_plus_tree.Delete(110);
	b_plus_tree.Delete(112);
	b_plus_tree.Delete(60);
	b_plus_tree.Delete(70);
	b_plus_tree.Delete(71);
	b_plus_tree.Delete(100);

//	b_plus_tree.Delete(110);
//	b_plus_tree.Delete(100);
//	b_plus_tree.Delete(90);
//	b_plus_tree.Delete(60);
//	b_plus_tree.Delete(70);
//	b_plus_tree.Delete(54);
//	b_plus_tree.Delete(53);

	b_plus_tree.Insert(1, 1);
	b_plus_tree.Insert(1, 2);

d
	node = b_plus_tree.GetNode(0);
dd	cout << node->num << " " << node->value_num << endl;
dd	for(int i = 0; i <= 3; i++) cout << node->pointer[i] << "," << node->value[i] << " "; cout << endl;
dd	cout << (int)node->state << endl;
	
/*	while(node->pointer[3] != -1) {
		cout << node->num << " ";
		node = b_plus_tree.GetNode(node->pointer[3]);
	}
	cout << node->num << " ";*/

	return 0;
}
