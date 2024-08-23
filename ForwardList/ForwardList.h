#pragma once
#include<iostream>
using namespace std;
#define tab "\t"
#define delimeter "\n====================================\n"

template<typename T>
class Element
{
	T Data;
	Element<T>* pNext; // p - pointer. Next - next element
public:
	operator int();
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();
	template<typename T>friend class ForwardList;
	template<typename T>friend class Iterator;
};

template<typename T>class Iterator
{
	Element<T>* ptr;
public:
	Iterator(Element<T>* p = nullptr);
	~Iterator();
	bool operator==(const Iterator<T>& other)const;
	bool operator!=(const Iterator<T>& other)const;
	Iterator<T>& operator++();
	Iterator<T> operator++(int);

	T& operator*()const;
	T operator*();
	template<typename T>friend class ForwardList;
};

template<typename T>
class ForwardList
{
	int size;
	Element<T>* Head; // head of list, pointing at first element 
public:
	Iterator<T> begin()const;
	Iterator<T> end()const;
	int getsize()const;
	ForwardList();
	explicit ForwardList(int size);

	ForwardList(const ForwardList<T>& other);

	ForwardList(ForwardList<T>&& other);

	ForwardList(const initializer_list<T>& il);
	~ForwardList();

	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator =(ForwardList<T>&& other);

	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();

	void insert(T Data, int num);
	void erase(int num);

	void print()const;
	const T& operator[](int num)const;
	T& operator[](int num);
};

template<typename T> ForwardList<T> operator+(const ForwardList<T>& A, const ForwardList<T>& B);