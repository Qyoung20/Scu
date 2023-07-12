#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include "SCUMembers.h"



class Staff : public SCUMember {
public:
	//constructor inheriting scumember
	Staff(const string& name, const string& email, const string& addr, int level, std::string department);
	//assignes level if greater than origional
	void change_level(const int new_level);
	//change department
	void switch_dept(const std::string& new_dept);
	//uses scumemeber to_string then includes member varriables of staff to be printed
	std::string to_string()const;

private:
	int level_;
	std::string department_;
};