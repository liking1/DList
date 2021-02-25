#include <iostream>
#include <list>
#include <vector>
#include "Header1.h"
#include "Header.h"

using namespace std;
int main()
{
	DList<int> d;
	DList<int> l;

	d.pushBack(2);
	d.pushBack(1);
	l.pushBack(3);
	l.pushBack(5);
	l.pushBack(6);
	l.pushBack(1);

	d.printL();
	d.reverse();
	d.printL();
	DList<int> test;
	test = l * d;
	test.printL();
	cout << "Size: " << test.getSize() << endl;
}