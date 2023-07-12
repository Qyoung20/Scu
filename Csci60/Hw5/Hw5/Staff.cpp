#include <iostream>
#include <string>
#include <cassert>
#include "Staff.h"

Staff::Staff(const string& name, const string& email, const string& addr, int level, std::string department)
	: SCUMember(name, email, addr), level_(level), department_(department){ }
void Staff::change_level(const int new_level) {
	if (new_level > level_) {
		level_ = new_level;
	}
	else {
		return;
	}
}
void Staff::switch_dept(const std::string& new_dept) {
	department_ = new_dept;
}
std::string Staff::to_string() const {
	return SCUMember::to_string() + "\n"+ " Staff level: " + std::to_string(level_) + ", Staff Department: " + department_;
}