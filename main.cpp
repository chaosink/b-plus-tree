#include <iostream>
#include "b_plus_tree.hpp"
using namespace std;

struct Value {
	int age;
	float weight;

	Value() {
		new (this) Value(0, 0);
	}
	Value(int age, float weight) {
		this->age = age;
		this->weight = weight;
	}
	bool operator==(const Value &value) {
		return this->age == value.age && this->weight == value.weight;
	}
	bool operator!=(const Value &value) {
		return !(*this == value);
	}
	bool operator<(const Value &value) {
		return this->age < value.age || (this->age == value.age && this->weight < value.weight);
	}
	bool operator>=(const Value &value) {
		return !(*this < value);
	}
	bool operator>(const Value &value) {
		return this->age > value.age || (this->age == value.age && this->weight > value.weight);
	}
	bool operator<=(const Value &value) {
		return !(*this > value);
	}
};

ostream &operator<<(ostream& os, const Value &value) {
	os << value.age << "-" << value.weight;
	return os;
}

int main() {
	int pointer_num = 4;

	BPlusTree<Value> b_plus_tree = BPlusTree<Value>(pointer_num);

	Node<Value> *node;


	b_plus_tree.Insert(Value(4, 0.4), 4);
	b_plus_tree.Insert(Value(1, 0.1), 1);
	b_plus_tree.Insert(Value(5, 0.5), 5);
	b_plus_tree.Insert(Value(2, 0.2), 2);
	b_plus_tree.Insert(Value(3, 0.3), 3);



	b_plus_tree.Delete(Value(1, 0.1));
	b_plus_tree.Delete(Value(2, 0.2));
	b_plus_tree.Delete(Value(3, 0.3));
	b_plus_tree.Delete(Value(4, 0.4));
	b_plus_tree.Delete(Value(5, 0.5));



	node = b_plus_tree.GetNode(2);
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
