//
// Created by Shandy Mephesto on 11/1/21.
//

#include <iostream>
#include <string>
#include <deque>

#if 0 //CREATE A REAL STL EXAMPLE

#include <map>
#include <stack>
#include <vector>

namespace ft = std;
#else

#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"

#endif

#include <stdlib.h>

template<typename T>
void printSize(ft::vector<T>
const& vct,
		bool print_content = true
)
{
	const size_t size = vct.size();
	const size_t capacity = vct.capacity();
	const std::string isCapacityOk = (capacity>=size) ? "OK" : "KO";
// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size <<
			  std::endl;
	std::cout << "capacity: " << isCapacityOk <<
			  std::endl;
	if ((capacity<size)) {
		std::cout << "capacity " << capacity <<
				  std::endl;
		std::cout << "size     " << size <<
				  std::endl;
	}
	std::cout << "max_size: " << vct.
			max_size()
			  <<
			  std::endl;
	if (print_content) {
		typename ft::vector<T>::const_iterator it = vct.begin();
		typename ft::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" <<
				  std::endl;
		for (; it!=
				ite;
			   ++it)
			std::cout << "- " << *it <<
					  std::endl;
	}
	std::cout << "###############################################" <<
			  std::endl;
}

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft

//int main(void)
//{
//	TESTED_NAMESPACE::vector<int> v, vector;
//	TESTED_NAMESPACE::vector<int> tmp, tmp2;
//	vector.assign(3, 3);
//	tmp.assign(40000000, 1);
//	tmp2.assign(4000, 1);
//	vector.assign(tmp.begin(), tmp.end());
//	v.push_back(vector[1]);
//	v.push_back(vector.size());
//	v.push_back(vector.capacity());
//	vector.assign(tmp2.begin(), tmp2.end());
//	v.push_back(vector[444]);
//	v.push_back(vector.size());
//	v.push_back(vector.capacity());
//	printSize(v, true);
//	return (0);
//}
//
////#include "common.hpp"

class B {
public:
	char* l;
	int i;
	B()
			:l(nullptr), i(1) { };
	B(const int& ex)
	{
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B()
	{
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A()
			:B() { };
	A(const B* ex)
	{
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i==-1) throw "n";
	}
	~A()
	{
		delete this->l;
		this->l = nullptr;
	};
};

int main(void)
{
	TESTED_NAMESPACE::vector<int> v;
	TESTED_NAMESPACE::vector<int> vector;
	vector.assign(26000000, 1);
	v.push_back(*(vector.insert(vector.end()-8000000, 44)));
	v.push_back(vector.size());
	v.push_back(vector.capacity());
	std::unique_ptr<B> k2(new B(3));
	std::unique_ptr<B> k3(new B(4));
	std::unique_ptr<B> k4(new B(-1));
	TESTED_NAMESPACE::vector<A> vv;
	TESTED_NAMESPACE::vector<B*> v1;

	v1.push_back(&(*k2));
	v1.push_back(&(*k3));
	v1.push_back(&(*k4));
	try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
	catch (...) {
		v.push_back(vv.size());
		v.push_back(vv.capacity());
	}
	printSize(v);

	return (0);
}

//int main(void)
//{
//	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);
//	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
//
//	for (unsigned long int i = 0; i<vct.size(); ++i)
//		vct[i] = (vct.size()-i)*3;
//	printSize(vct);
//
//	vct2.insert(vct2.end(), 42);
//	vct2.insert(vct2.begin(), 2, 21);
//	printSize(vct2);
//
//	vct2.insert(vct2.end()-2, 42);
//	printSize(vct2);
//
//	vct2.insert(vct2.end(), 2, 84);
//	printSize(vct2);
//
//	vct2.resize(4);
//	printSize(vct2);
//
//	vct2.insert(vct2.begin()+2, vct.begin(), vct.end());
//	vct.clear();
//	printSize(vct2);
//
//	printSize(vct);
//	return (0);
//}
// TODO:: speed up

//int main()
//{
//	TESTED_NAMESPACE::vector<TESTED_TYPE> vector;
//	TESTED_NAMESPACE::vector<TESTED_TYPE> v;
//	vector.assign(99000000, 1);
//	vector.resize(50000000);
//	vector.reserve(50000000);
//	v.push_back(vector.size());
//	v.push_back(vector.capacity());
//	vector.resize(70000000);
//	v.push_back(vector.size());
//	v.push_back(vector.capacity());
//	vector.resize(153000000, int());
//	v.push_back(vector.size());
//	v.push_back(vector.capacity());
//	v.push_back(vector[65]);
//	printSize(v, true);
//	return 1;
//}

/*
int main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;

	for (unsigned long int i = 0; i<vct.size(); ++i)
		vct[i] = (vct.size()-i)*3;
	printSize(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	printSize(vct2);

	vct2.insert(vct2.end()-2, 42);
	printSize(vct2);

	vct2.insert(vct2.end(), 2, 84);
	printSize(vct2);

	vct2.resize(4);
	printSize(vct2);

	vct2.insert(vct2.begin()+2, vct.begin(), vct.end());
	vct.clear();
	printSize(vct2);

	printSize(vct);
	return (0);
}
*/
/*
#define int int
#include <list>
#define TESTED_TYPE int
int main(void)
{
	std::list<TESTED_TYPE> lst;
	std::list<TESTED_TYPE>::iterator lst_it;
	for (int i = 1; i<5; ++i)
		lst.push_back(i*3);

	ft::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
	printSize(vct);

	lst_it = lst.begin();
	for (int i = 1; lst_it!=lst.end(); ++i)
		*lst_it++ = i*5;
	vct.assign(lst.begin(), lst.end());
	printSize(vct);

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	printSize(vct);
	return (0);
}
*/

//#define TESTED_TYPE int
//#define TESTED_NAMESPACE ft
//
//int main(void)
//{
//	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(5);
//	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
//	const int cut = 3;
//
//	for (unsigned long int i = 0; i<vct.size(); ++i)
//		vct[i] = (vct.size()-i)*7;
//	printSize(vct);
//
//	vct2.insert(vct2.begin(), vct.begin(), vct.begin()+cut);
//	printSize(vct2);
//	vct2.insert(vct2.begin(), vct.begin()+cut, vct.end());
//	printSize(vct2);
//	vct2.insert(vct2.end(), vct.begin(), vct.begin()+cut);
//	printSize(vct2);
//
//	std::cout << "insert return:" << std::endl;
//
//	std::cout << *vct2.insert(vct2.end(), 42) << std::endl;
//	std::cout << *vct2.insert(vct2.begin()+5, 84) << std::endl;
//	std::cout << "----------------------------------------" << std::endl;
//
//	printSize(vct2);
//	return (0);
//}