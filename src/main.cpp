#include <iostream>
using namespace std;

#include "value_pointer.hpp"
#include "b_plus_tree.hpp"

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

	pointer = b_plus_tree.Find(Value(512, "512", 1.f));
	cout << pointer.num << endl;

	p = b_plus_tree.FindFrom(Value(9995, "9995", 2.f), true);
	for(unsigned int i = 0; i < p.size(); i++)
		cout << p[i].num << " ";
	cout << endl;

	p = b_plus_tree.FindTo(Value(4, "4", 3.f), true);
	for(unsigned int i = 0; i < p.size(); i++)
		cout << p[i].num << " ";
	cout << endl;

	p = b_plus_tree.FindFromTo(Value(1, "1", 4.f), true, Value(505, "505", 5.f), true);
	for(unsigned int i = 0; i < p.size(); i++)
		cout << p[i].num << " ";
	cout << endl;

	for(int i = 0; i < N; i++) {
		char buffer[256];
		sprintf(buffer, "%d", i);
		b_plus_tree.Delete(Value(i, buffer, i));
	}

	pointer = b_plus_tree.Find(Value(499, "499", 0.f));
	cout << pointer.num << endl;

	return 0;
}
