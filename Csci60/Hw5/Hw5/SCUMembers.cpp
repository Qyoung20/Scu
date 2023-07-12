#include <iostream>
#include <string>
#include <cassert>
#include "SCUMembers.h"

using namespace std;

SCUMember::SCUMember(const string& name, const string& email,
	const string& addr) : name_(name), email_(email), addr_(addr) { }

void SCUMember::change_address(const string& new_address) {
	addr_ = new_address;
}

string SCUMember::to_string() const {
	return "SCU Member: " + name_ + " , " + email_ + " , " + addr_;
}
