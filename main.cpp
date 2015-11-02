#include <iostream>
#include "b_plus_tree.hpp"
using namespace std;

int main() {
	int pointer_num = 4;

	BPlusTree<string> b_plus_tree = BPlusTree<string>(pointer_num);

	Node<string> *node;



	b_plus_tree.Insert("Brandt", 1);
	b_plus_tree.Insert("Califieri", 2);
	b_plus_tree.Insert("Einstein", 3);
	b_plus_tree.Insert("El Said", 4);
	b_plus_tree.Insert("Crick", 5);
	b_plus_tree.Insert("Gold", 6);
	b_plus_tree.Insert("Katz", 7);
	b_plus_tree.Insert("Mozart", 9);
	b_plus_tree.Insert("Singh", 10);
	b_plus_tree.Insert("Kim", 8);
	b_plus_tree.Insert("Srinivasan", 11);
	b_plus_tree.Insert("Wu", 12);
	b_plus_tree.Insert("Adams", 13);



	b_plus_tree.Delete("Srinivasan");
	b_plus_tree.Delete("Singh");
	b_plus_tree.Delete("Wu");
	b_plus_tree.Delete("Gold");
	b_plus_tree.Delete("Adams");
	b_plus_tree.Delete("Brandt");
	b_plus_tree.Delete("Califieri");
	b_plus_tree.Delete("Crick");
	b_plus_tree.Delete("Einstein");
	b_plus_tree.Delete("El Said");
	b_plus_tree.Delete("Katz");
	b_plus_tree.Delete("Kim");
	b_plus_tree.Delete("Mozart");
	b_plus_tree.Delete("Crick");



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
