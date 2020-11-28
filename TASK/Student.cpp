#include "Module.h"
#include "Student.h"

// see comment in Student.h
Student::Student() {}

Student::Student(const string& uid) {
	// IMPLEMENT ME
}

// Even though they say "IMPLEMENT ME", some of these functions may
// need to be implemented in some subclasses in addition to / instead of here

bool Student::addModule(string moduleCode, float mark) {
	// IMPLEMENT ME
	return true;
}

bool Student::updateMark(string moduleCode, float mark) {
	// IMPLEMENT ME
	return true;
}

float Student::cwa() const {
	// IMPLEMENT ME
	return 0.0;
}

string Student::calcDegClass() const {
	// IMPLEMENT ME
	return "DUMMY STRING";
}

istream& operator>>(istream& is, Student& student) {
	// IMPLEMENT ME
	return is;
}

ostream& operator<<(ostream& os, const Student& student) {
	// IMPLEMENT ME
	return os;
}