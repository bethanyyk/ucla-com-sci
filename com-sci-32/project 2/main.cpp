#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Sequence s;
	assert(s.insert(0, "lavash") == 0);
	assert(s.insert(0, "tortilla") == 0);
	assert(s.size() == 2);
	ItemType x = "injera";
	assert(s.get(0, x) && x == "tortilla");
	assert(s.get(1, x) && x == "lavash");
}
void test2()
{
	Sequence s;
	assert(s.insert(0, "10") == 0);
	assert(s.insert(0, "20") == 0);
	assert(s.size() == 2);
	ItemType i = "999";
	s.get(0, i);
	assert(i == "20");
	s.get(1, i);
	assert(i == "10");
}

int main()
{
	Sequence ss;
	ss.insert(0, "aaa");
	ss.insert(1, "ccc");
	ss.insert(2, "bbb");
	ItemType i = "xxx";
	assert(!ss.get(3, i) && i == "xxx");
	assert(ss.get(1, i) && i == "ccc");

	test();

	Sequence s;
	assert(s.remove("10") == 0);
	s.insert(0, "10");
	//s.dump();
	assert(s.find("10") == 0);
	assert(s.find("30") == -1);
	s.insert(1, "30");
	//s.dump();
	s.insert(1, "20");
	//s.dump();
	s.insert(0, "0");
	//s.dump();
	assert(s.find("30") == 3);
	ItemType j = "7";
	s.get(2, j);
	assert(j == "20");
	s.insert(4, "39");
	//s.dump();
	s.set(4, "40");
	//s.dump();
	assert(s.find("40") == 4);
	s.insert("25");
	assert(s.find("25") == 3);
	assert(s.insert("25") == 3);
	//s.dump();
	assert(s.insert("50") == 7);
	s.insert(1, "50");
	assert(s.insert("49") == 1);
	//s.dump();
	s.erase(1);
	assert(s.find("49") == -1);
	assert(s.find("50") == 1);
	//s.dump();
	assert(s.remove("25") == 2);
	//s.dump();
	assert(s.size() == 7);

	Sequence t;
	t.insert(0, "1");
	t.insert(1, "2");
	t.insert(2, "3");
	t.insert(3, "4");
	//t.dump();
	assert(t.size() == 4);

	s.swap(t);
	//s.dump();
	//t.dump();
	assert(s.size() == 4);
	assert(t.size() == 7);

	Sequence u;
	u = s;
	//u.dump();
	assert(u.size() == s.size());

	t = u;
	//t.dump();
	//u.dump();

	Sequence v;
	v.insert("0");
	v.insert("1");
	v.insert("2");
	v.insert("3");
	v.insert("4");
	v.insert("5");
	Sequence w;
	w.insert("2");
	w.insert("3");
	w.insert("4");
	assert(subsequence(v, w) == 2);
	w.erase(1);
	assert(subsequence(v, w) == -1);

	Sequence x;
	x.insert(0, "3");
	x.insert(1, "2");
	x.insert(2, "1");
	//x.dump();
	Sequence y;
	y.insert(0, "6");
	y.insert(1, "5");
	y.insert(2, "4");
	//y.dump();
	Sequence z;
	concatReverse(x, y, z);
	//z.dump();

	//v.dump();
	concatReverse(x, y, v);
	//v.dump();

	Sequence a;
	a.insert(0, "3");
	a.insert(1, "2");
	a.insert(2, "1");
	Sequence b;
	b.insert(0, "6");
	b.insert(1, "5");
	b.insert(2, "4");
	concatReverse(a, b, a);
	//a.dump();
	Sequence c;
	c.insert(0, "3");
	c.insert(1, "2");
	c.insert(2, "1");
	Sequence d;
	d.insert(0, "6");
	d.insert(1, "5");
	d.insert(2, "4");
	concatReverse(c, d, d);
	//d.dump();

	test2();

	Sequence s1;
	s1.insert(0, "p");
	s1.insert(1, "a");
	s1.insert(2, "r");
	Sequence s2;
	s2.insert(0, "r");
	s2.insert(1, "o");
	s2.insert(2, "t");
	Sequence s3;
	concatReverse(s1, s2, s3);
	//s3.dump();

	cerr << "All test cases passed" << endl;
}