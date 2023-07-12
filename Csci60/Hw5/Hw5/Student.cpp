#include <iostream>
#include <string>
#include <cassert>
#include "Student.h"

using namespace std;

Student::Student(const string& name, const string& email,
	const string& addr, const string& major) : SCUMember(name, email, addr), major_(major) { }


void Student::change_major(const string& new_major) {
	major_ = new_major;
}

string Student::to_string() const {
	return SCUMember::to_string() + " Student's major: " + major_;
}