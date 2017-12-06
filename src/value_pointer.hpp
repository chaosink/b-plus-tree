#pragma once

#include <iostream>
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

std::ostream &operator<<(std::ostream& os, const Value &value) {
	os << value.age << "-" << value.name << "-" << value.weight;
	return os;
}

struct Pointer {
	int num = -1;
	Pointer() {}
	Pointer(int num) : num(num) {}
	bool operator==(const Pointer &pointer) const {
		return num == pointer.num;
	}
};

std::ostream &operator<<(std::ostream& os, const Pointer &pointer) {
	os << pointer.num;
	return os;
}
