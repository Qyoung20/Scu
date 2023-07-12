#include "intbag.h"
//empty bag
IntBag::IntBag() {
	array_ = nullptr;
	used_ = 0;
	size_ = 0;
}
//deep copy of a
IntBag::IntBag(const IntBag& a) {
	if (a.size_ > 0) {
		array_ = new int[a.size_];
		for (size_t i = 0; i < a.used_; i++) {
			array_[i] = a.array_[i];
		}
	}
	else {
		array_ = nullptr;
	}
	size_ = a.size_;
	used_ = a.used_;
}
//removes before out of scope
IntBag::~IntBag() {
	delete[] array_;
	array_ = nullptr;
}
void IntBag::operator = (const IntBag& rhs) {
	used_ = rhs.used_;
	if (size_ != rhs.size_) {
		size_ = rhs.size_;
		delete[] array_;
		array_ = new int[size_];
	}
	for (size_t i = 0; i < used_; i++) {
		array_[i] = rhs.array_[i];
	}
}
//-----------------------------------------------------
void IntBag::add(const int item) {
	if (size_ == 0) {
		size_= 1;
		array_ = new int[size_];
	}
	else if (used_==size_){
		if (used_ == CAPACITY) {
			return;
		}
		size_ *=2;
		int* temp = new int[size_];
		for (size_t i = 0; i < used_; i++) {
			temp[i] = array_[i];
		}
		delete[] array_;
		 array_= temp;
	}
	array_[used_] = item;
	used_++;
}
void IntBag::setUsed(int newsize) {
	size_ = newsize;
}
void IntBag::clear() {
	size_t count = 0;
	while (remove(count))count++;
	std::cout << "Cleared" << std::endl;
}
bool IntBag::remove(int pos) {
	size_t i = 0;
	while (i < used_ && i != pos)i++;
	if (i == used_)return false;
	//shift everything back one and decrease used_ after by 1
	for (i++; i < used_; i++) {
		array_[i - 1] = array_[i];
	}
	used_--;
	return true;
}
void IntBag::fill(int c) {
	while (used_ != CAPACITY)add(c);
}
std::ostream& operator<<(std::ostream& out, const IntBag& a) {
	for (size_t i = 0; i < a.getUsed(); i++) {
		out << a[i] << " ";
	}
	return out;
}