#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include "SCUMembers.h"
using namespace std;

class Student : public SCUMember {
public:
	Student(const string& name, const string& email, const string& addr, const string& major);
	void change_major(const string& new_major);
	string to_string() const;

private:
	string major_;
};