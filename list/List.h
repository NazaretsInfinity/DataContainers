#pragma once
#include<iostream>
using namespace std;
#define tab '\t'

template<typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* Next = nullptr, Element* Prev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* it;
	public:
		ConstBaseIterator(Element* it = nullptr) : it(it) {};
		~ConstBaseIterator() {};
		bool operator==(const ConstBaseIterator& other);
		bool operator!=(const ConstBaseIterator& other);
		const T& operator*()const;
		friend class List;
	};

public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* it = nullptr) : ConstBaseIterator(it) {}
		~ConstIterator() {}
		ConstIterator& operator++();
		ConstIterator& operator--();
		ConstIterator operator--(int);
		ConstIterator operator++(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* it = nullptr) :ConstIterator(it) {}
		~Iterator() {}
		T& operator*();
	};

	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* it = nullptr) :ConstReverseIterator(it) {}
		~ReverseIterator() {}
		T& operator*();
	};

	ConstReverseIterator rbegin()const;
	ReverseIterator rbegin();
	ConstReverseIterator rend()const;
	ReverseIterator rend();
	ConstIterator begin()const;
	Iterator begin();
	ConstIterator end()const;
	Iterator end();


	List();
	List(const initializer_list<T>& il);
	List(const List<T>& other);
	~List();
	List<T>& operator =(const List<T>& other);
	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(T Data, size_t num);
	void erase(int num);
	void reverse_print()const;
	void print()const;
};
// CLASS DECLARATION END