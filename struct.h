#include <iostream>

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

std::ostream &operator<<(std::ostream& os, const Value &value) {
	os << value.age << "-" << value.weight;
	return os;
}
