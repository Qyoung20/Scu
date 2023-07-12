#include <iostream>
using namespace std;
#include "intbag.h"

int main() {
	IntBag a;
	a.add(1);
	cout << a << endl;
	IntBag b(a);
	cout << b << endl;
	b.add(12);
	cout << b << endl;
	b = a;
	cout << b << endl;
	b.remove(1);
	cout << b << endl;
	b.clear();
	cout << b << endl;
	b.fill(2);
	cout << b << endl;

	return 0;
}
