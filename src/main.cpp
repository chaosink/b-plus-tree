#include <iostream>
using namespace std;

#include "b_plus_tree.hpp"
#include "value_pointer.hpp"

const int N = 10000;

int main() {
	remove("test.idxinfo");
	remove("test.idx");

	bpt::BPlusTree<Value, Pointer> b_plus_tree("test");
	Pointer pointer;
	vector<Pointer> p;

	for(int i = 0; i < N; i++) {
		char buffer[256];
		sprintf(buffer, "%d", i);
		b_plus_tree.Insert(Value(i, buffer, i / 10.f), i);
	}

	// find an existing Value, the corresponding Pointer returned
	pointer = b_plus_tree.Find(Value(32, "32", 0.f));
	cout << pointer.num << endl;

	// find a non-existing Value, an empty Pointer returned
	pointer = b_plus_tree.Find(Value(16, "17", 0.f));
	cout << pointer.num << endl;

	// find from an existing Value, the Pointers with Value satisfying > or >= returned
	p = b_plus_tree.FindFrom(Value(9995, "9995", 0.f), true);
	for(unsigned int i = 0; i < p.size(); i++)
		cout << p[i] << " ";
	cout << endl;

	// find from a non-existing Value, the Pointers with Value satisfying > or >= returned
	p = b_plus_tree.FindFrom(Value(9995, "9996", 0.f), true);
	for(unsigned int i = 0; i < p.size(); i++)
		cout << p[i] << " ";
	cout << endl;

	// find to an existing Value, the Pointers with Value satisfying < or <= returned
	p = b_plus_tree.FindTo(Value(4, "4", 0.f), true);
	for(unsigned int i = 0; i < p.size(); i++)
		cout << p[i] << " ";
	cout << endl;

	// find to a non-existing Value, the Pointers with Value satisfying < or <= returned
	p = b_plus_tree.FindTo(Value(4, "3", 0.f), true);
	for(unsigned int i = 0; i < p.size(); i++)
		cout << p[i] << " ";
	cout << endl;

	// find from and to existing Values
	p = b_plus_tree.FindFromTo(Value(16, "16", 0.f), true, Value(32, "32", 0.f), true);
	for(unsigned int i = 0; i < p.size(); i++)
		cout << p[i] << " ";
	cout << endl;

	// find from and to non-existing Values
	p = b_plus_tree.FindFromTo(Value(16, "17", 0.f), true, Value(32, "31", 0.f), true);
	for(unsigned int i = 0; i < p.size(); i++)
		cout << p[i] << " ";
	cout << endl;

	// delete a non-existing Value, nothing happens
	b_plus_tree.Delete(Value(16, "17", 0.f));

	// delete all existing Values
	for(int i = 0; i < N; i++) {
		char buffer[256];
		sprintf(buffer, "%d", i);
		b_plus_tree.Delete(Value(i, buffer, i));
	}

	// find an existed but deleted Value, an empty Pointer returned
	pointer = b_plus_tree.Find(Value(32, "32", 0.f));
	cout << pointer.num << endl;

	return 0;
}
