#ifndef VALUE_POINTER_HPP
#define VALUE_POINTER_HPP

#include <iostream>
#include <string>

struct Value {
	int age;
	std::string name;
	Value() {
		new (this) Value(0, "");
	}
	Value(int age, std::string name) {
		this->age = age;
		this->name = name;
	}
	bool operator==(const Value &value) {
		return this->age == value.age && this->name == value.name;
	}
	bool operator<(const Value &value) {
		return this->age < value.age || (this->age == value.age && this->name < value.name);
	}
};

std::ostream &operator<<(std::ostream& os, const Value &value) {
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
};

std::ostream &operator<<(std::ostream& os, const Pointer &pointer) {
	os << pointer.num;
	return os;
}

#endif // VALUE_POINTER_HPP
