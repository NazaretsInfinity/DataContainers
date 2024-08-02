#include<iostream>
using namespace std;
#define tab '\t'
class Element;
class List
{
	class Element
	{
		int Data; // value of element
		Element* pNext; // p - pointer
		Element* pPrev; // Prev-previous element
	public:
		Element(int Data, Element* Next = nullptr, Element* Prev = nullptr) : Data(Data), pNext(Next), pPrev(Prev)
		{
			cout << "EConstructor: " << this << endl;
		}
		~Element()
		{
			cout << "EDestructor: " << this << endl;
		}

		//size_t is a 'typedef' for 'unsigned int' 
		// typedef - directive , it creates a nickname for existing type of data(int ,etc)
		// typedef have this syntax:
		// typedef (type) nickname 
		friend class List;
		friend class Iterator;
	}*Head, * Tail;
	size_t size;
public:
	class Iterator
	{
		Element* it;
	public:
		Iterator(Element* it = nullptr) : it(it) {}
		~Iterator() {}
		bool operator==(const Iterator& other)
		{
			return this->it == other.it;
		}
		bool operator!=(const Iterator& other)
		{
			return this->it != other.it;
		}
		Iterator& operator++()
		{
			it = it->pNext;
			return *this;
		}
		Iterator& operator--()
		{
			it = it->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			it = it->pPrev;
			return old;
		}
		Iterator operator++(int)
		{
			Iterator old = it;
			it = it->pNext;
			return old;
		}
		const int& operator*()const
		{
			return it->Data;
		}
		int& operator*()
		{
			return it->Data;
		}
		friend class List;
	};
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) : Temp(Temp){}
		~ReverseIterator(){}
		// increment decrement
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = Temp;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp=Temp->pNext;
			return old;
		}
		// comprasion operators
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)
		{
			return this->Temp != other.Temp;
		}
		// Dereference operator
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}

	};
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	Iterator begin()const
	{
		return Head;
	}
	Iterator end()const
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const initializer_list<int>& il) : List()
	{
		for (const int* it = il.begin(); it != il.end(); ++it)push_back(*it);
		//for (auto it: il)push_back(it);
	}
	List(const List& other) : List()
	{
		*this = other;
		cout << "CopyConstructor: " << this << endl;
	}
	~List()
	{
		while (Head && Tail)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	// MOVE & COPY ASSIGNMENTS
	List& operator =(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment: " << this << endl;
		return *this;
	}
	 // ADDING ELEMENTS
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		if (!(Head && Tail))Head = Tail = New;
		else
		{
		    New->pNext = Head;
			Head->pPrev = New;
			Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		if (!(Head && Tail))Head = Tail = New;
		else
		{
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;
		}
		size++;
	}
	void pop_front()
	{
		if (!(Head && Tail))return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			//1) move head on next element
			Head = Head->pNext;
			//2) delete this fignya
			delete Head->pPrev;
			//3) give fignya nullptr
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (!(Head && Tail))return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
	void insert(int Data, int num)
	{
		if (num >= size)return push_back(Data);
		if (num == 0)return push_front(Data);
		Element* Temp = Head;
		if (num <= size/ 2)
			for (int i = 0; i < num; i++)
				Temp = Temp->pNext;
		else
		{
			Temp = Tail;
			for (int i = num; i < size-1; i++)
				Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		Temp->pPrev = Temp->pPrev->pNext;
		size++;
	}
	void erase(int num)
	{
		if (num >= size-1)return pop_back();
		if (num==0)return pop_front();
		Element* Temp = Head;
		if (num <= size / 2)
			for (int i = 0; i < num; i++)
				Temp = Temp->pNext;
		else
		{
			Temp = Tail;
			for (int i = num; i < size - 1; i++)
				Temp = Temp->pPrev;
		}
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete Temp;
		size--;
	}
	// METHODS 
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pNext << tab << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;

		}
			cout << "Amount of elements: " << size << endl;
	}
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp -> pNext << endl;
		}
			cout << "Amount of elements: " << size << endl;
	}
};
List operator+(const List& left, const List& right)
{
	List buffer = left;
	for (List::Iterator it = right.begin(); it != right.end(); it++)buffer.push_back(*it);
	return buffer;
}

#define checking
void main()
{
	setlocale(LC_ALL, "");
#ifdef checking1
	int s;
	List list;
	list.push_back(0);
	list.push_back(1);
	cout << "Enter number of the element to add: "; cin >> s;
	list.insert(666, s);
	list.print();
	cout << "Enter number of the element to delete: "; cin >> s;
	list.erase(s);
	list.print();
#endif 
#ifdef checking2
	List list = { 3,5,8,13,21 };
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}cout << "\n\n";
	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}cout << endl;
#endif 
	List list1 = { 3,5,8,13,21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	for (int i : list3)
	{
		cout << i << tab;
	}cout << endl;
}