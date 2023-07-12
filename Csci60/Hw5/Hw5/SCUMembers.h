#pragma once
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class SCUMember {
public:
	SCUMember(const string& name, const string& email, const string& addr);
	void change_address(const string& new_address);
	string to_string() const; // for printing 

private:
	string name_;
	string email_;
	string addr_;
};
