#include <iostream>
#include <cstring>

struct Value {
	int age;
	char name[8];
	Value() {
		new (this) Value(0, "");
	}
	Value(int age, const char *name) {
		this->age = age;
		strcpy(this->name, name);
	}
	Value(const Value &value) {
		age = value.age;
		strcpy(name, value.name);
	} 
	bool operator==(const Value &value) {
		return this->age == value.age && strcmp(this->name, value.name) == 0;
	}
	bool operator!=(const Value &value) {
		return !(*this == value);
	}
	bool operator<(const Value &value) {
		return this->age < value.age || (this->age == value.age && strcmp(this->name, value.name) < 0);
	}
	bool operator>=(const Value &value) {
		return !(*this < value);
	}
	bool operator>(const Value &value) {
		return this->age > value.age || (this->age == value.age && strcmp(this->name, value.name) > 0);
	}
	bool operator<=(const Value &value) {
		return !(*this > value);
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
	static unsigned int Size() {
		return sizeof(int);
	}
	bool operator==(const Pointer &pointer) {
		return this->num == pointer.num;
	}
};

std::ostream &operator<<(std::ostream& os, const Pointer &pointer) {
	os << pointer.num;
	return os;
}
