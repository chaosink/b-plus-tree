#include <iostream>
#include <string>
#include "b_plus_tree.hpp"
using namespace std;

struct Value {
	int age;
	string name;

	Value() {
		new (this) Value(0, "");
	}
	Value(int age, string name) {
		this->age = age;
		this->name = name;
	}
	bool operator==(const Value &value) {
		return this->age == value.age && this->name == value.name;
	}
	bool operator!=(const Value &value) {
		return !(*this == value);
	}
	bool operator<(const Value &value) {
		return this->age < value.age || (this->age == value.age && this->name < value.name);
	}
	bool operator>=(const Value &value) {
		return !(*this < value);
	}
	bool operator>(const Value &value) {
		return this->age > value.age || (this->age == value.age && this->name > value.name);
	}
	bool operator<=(const Value &value) {
		return !(*this > value);
	}
	friend ostream &operator<<(ostream& os, const Value &value);
};

ostream &operator<<(ostream& os, const Value &value) {
	os << value.age << "-" << value.name;
	return os;
}

struct Pointer {
	int num;
	Pointer() {
		new (this) Pointer(-1);
	}
	Pointer(int num) {
		this->num = num;
	}
	bool operator==(const Pointer &pointer) {
		return this->num == pointer.num;
	}
	friend ostream &operator<<(ostream& os, const Pointer &pointer);
};

ostream &operator<<(ostream& os, const Pointer &pointer) {
	os << pointer.num;
	return os;
}

int main() {
	int pointer_num = 4;

	BPlusTree<Value, Pointer> b_plus_tree = BPlusTree<Value, Pointer>(pointer_num);

	Node<Value, Pointer> *node;



	b_plus_tree.Insert(Value(4, "0.4"), 4);
	b_plus_tree.Insert(Value(1, "0.1"), 1);
	b_plus_tree.Insert(Value(5, "0.5"), 5);
	b_plus_tree.Insert(Value(2, "0.2"), 2);
	b_plus_tree.Insert(Value(3, "0.3"), 3);



	node = b_plus_tree.GetNode(0);
	cout << node->num << " " << node->value_num << " " << (int)node->state << endl;
	for(int i = 0; i < pointer_num - 1; i++) cout << node->pointer[i] << " [" << node->value[i] << "] ";
	cout << node->pointer[pointer_num - 1] << endl;



	b_plus_tree.Delete(Value(1, "0.1"));
	b_plus_tree.Delete(Value(2, "0.2"));
	b_plus_tree.Delete(Value(3, "0.3"));
	b_plus_tree.Delete(Value(4, "0.4"));
	b_plus_tree.Delete(Value(5, "0.5"));



	node = b_plus_tree.GetNode(0);
	cout << node->num << " " << node->value_num << " " << (int)node->state << endl;
	for(int i = 0; i < pointer_num - 1; i++) cout << node->pointer[i] << " [" << node->value[i] << "] ";
	cout << node->pointer[pointer_num - 1] << endl;

	node = b_plus_tree.GetNode(0);
	while(node->pointer[pointer_num - 1].num != -1) {
		cout << node->num << " ";
		node = b_plus_tree.GetNode(node->pointer[pointer_num - 1].num);
	}
	cout << node->num << endl;



	return 0;
}
