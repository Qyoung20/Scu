//Quinton Young, HW5,CSCI60

#include <iostream>
#include <string>
#include <cassert>
#include "Student.h"
#include "SCUMembers.h"
#include "Staff.h"
using namespace std;

int main() {
	//SCUMEMBER TEST
	SCUMember sm("sukanya", "smanna@scu.edu", "OCB");
	cout << sm.to_string() << endl;
	sm.change_address("Lucas");
	cout << sm.to_string() << endl;
	
	//STUDENT TEST
	Student student("sukanya", "smanna@scu.edu", "OCB", "CS");
	cout << student.to_string() << endl;

	//STAFF TEST
	Staff a("dumbledore", "dumbledore@scu.edu", "Mould-on-the-Wold", 99, "teacher");
	cout << a.to_string() << endl;
	a.change_level(100);
	a.switch_dept("head master");
	a.change_address("Hogwarts");
	cout << a.to_string() << endl;

	return 0;
}