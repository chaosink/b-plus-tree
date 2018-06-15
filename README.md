# b-plus-tree

A header-only and highly reusable implementation of B+-tree with which you can use your own definition of `Value` and `Pointer` and also the B+-tree can be saved in file blocks to be reused later.

## Define your own `Value` and `Pointer`

#### You can define your own `Value` like this:

```cpp
#include <cstring>

struct Value {
	int age = 0;
	char name[256] = "";
	float weight = 0;
	Value() {}
	Value(int age, const char *name, float weight) : age(age), weight(weight) {
		strcpy(this->name, name);
	}
	bool operator<(const Value &value) const { // ignore weight
		return this->age < value.age ||
			(this->age == value.age && strcmp(this->name, value.name) < 0);
	}
};
```

Necessary:
* A default constructor without arguments.
* Overload of comparison operator `<`.

#### You can define your own Pointer like this:

```cpp
struct Pointer {
	int num = -1;
	Pointer() {}
	Pointer(int num) : num(num) {}
	bool operator==(const Pointer &pointer) const {
		return num == pointer.num;
	}
};
```

Necessary:
* A member variable named `num` with type `int` to reccord the block numbers.
* A default constructor without arguments.
* Overload of comparison operator `==`.

## Build B+-tree with your own `Value` and `Pointer`

```cpp
#include "b_plus_tree.hpp"
#include "value_pointer.hpp"

int main() {
	BPlusTree<Value, Pointer> b_plus_tree("test");
	// "test" is the name of the B+-tree file

	b_plus_tree.Insert( <an instance of Value>, <an instance of Pointer> );
	Pointer pointer = b_plus_tree.Find( <an instance of Value> );
	b_plus_tree.Delete( <an instance of Value> );
}
```

The program will create two files:
* `test.idxinfo`: It records the root node number and the total node number in plain text.
* `test.idx`: It records the nodes of the B+-tree in binary blocks of which each size is 4K. You can change the size of blocks by hacking the code.

Acturally, the program will do operations on the **existing B+-tree** saved in the file with the specified name if it detects the file when starts running.
