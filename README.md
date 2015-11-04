# b-plus-tree

A highly reusable implementation of B+-tree with which you can use your own definition of `Value` and `Pointer` and also you can save the B+-tree in file blocks to reuse it later.

## Define your own Pointer and Value

#### You can define your own Value like this:

```cpp
#include <iostream>
#include <cstring>

struct Value {
	int age;
	char name[8];
	float weight;
	Value() {
		new (this) Value(0, "", 0);
	}
	Value(int age, const char *name, float weight) {
		this->age = age;
		strcpy(this->name, name);
		this->weight = weight;
	}
	bool operator==(const Value &value) {
		return this->age == value.age && strcmp(this->name, value.name) == 0;
	}
	bool operator<(const Value &value) {
		return this->age < value.age ||
			(this->age == value.age && strcmp(this->name, value.name) < 0);
	}
};

std::ostream &operator<<(std::ostream& os, const Value &value) {
	os << value.age << "-" << value.name << "-" << value.weight;
	return os;
}
```

Necessary:
* Member variables which occupy memory space.
* A default constructor without arguments.
* Comparison operator overload, `==` `<`.

Optional:
* Output stream operator overload, `<<`, if you need to output `Value`.

#### You can define your own Pointer like this:

```cpp
#include <iostream>

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
};

std::ostream &operator<<(std::ostream& os, const Pointer &pointer) {
	os << pointer.num;
	return os;
}
```

Necessary:
* Member variables which occupy memory space. A member variable named `num` with type `int` must be defined to specify a block number.
* A default constructor without arguments.
* Comparison operator overload, `==`.

Optional:
* Output stream operator overload, `<<`, if you need to output `Pointer`.

## Build B+-tree with your own Value and Pointer

```cpp
#include "b_plus_tree.hpp"
#include "value_pointer.hpp"

int main() {
	BPlusTree<Value, Pointer> b_plus_tree = BPlusTree<Value, Pointer>("test");
	// "test" is the name of the B+-tree file

	b_plus_tree.Insert( <an instance of Value>, <an instance of Pointer> );
	Pointer pointer = b_plus_tree.Find( <an instance of Value> );
	b_plus_tree.Delete( <an instance of Value> );
}
```

When the program terminates, two files are created.
* `test.info`: It records the root node number and the total node number in text format.
* `test.index`: It records the nodes of the B+-tree in binary blocks of which each size is 4K. You can change the size of blocks by hacking the code.

Acturally, the program will do operations on the existing B+-tree saved in the file of the specified name if it detects the file when starts running.
