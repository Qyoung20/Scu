#pragma once
#include <ostream>
#include <iostream>
class IntBag {
	const static int CAPACITY = 128;

	const static int MULT = 2;
public:
	//0 argument constructor
	//pre:none
	//post:creates empty intbag
	IntBag();
	//pre:none
	//post:creates new bag which is a coppy of the other
	IntBag(const IntBag& a);
	//pre:none
	//post:disolves dynamic memory associ
	~IntBag();
	//pre:none
	//post:
	void operator = (const IntBag& rhs);
	//pre:none
	//post:
	int operator[](int index)const { return array_[index]; }
	//pre:none
	//post:
	void add(const int item);
	//pre:none
	//post:
	int getUsed()const { return used_; }
	//pre:none
	//post:
	void setUsed(int newused);
	//pre:none
	//post:
	void clear();
	//pre:none
	//post:
	bool remove(int pos);
	//pre:none
	//post:
	void fill(int c);
private:
	int* array_;
	int size_;
	int used_;
};
std::ostream& operator<<(std::ostream& out, const IntBag& a);