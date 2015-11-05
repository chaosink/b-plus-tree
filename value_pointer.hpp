#ifndef VALUE_POINTER_HPP
#define VALUE_POINTER_HPP

#include <iostream>
#include <cstring>

struct Value {
	int age;
	char name[256];
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
		return this->age < value.age || (this->age == value.age && strcmp(this->name, value.name) < 0);
	}
};

std::ostream &operator<<(std::ostream& os, const Value &value) {
	os << value.age << "-" << value.name << "-" << value.weight;
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
};

std::ostream &operator<<(std::ostream& os, const Pointer &pointer) {
	os << pointer.num;
	return os;
}

#endif // VALUE_POINTER_HPP
