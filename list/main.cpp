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


	class Iterator
	{
		Element* it;
	public:
		Iterator(Element* el = nullptr) : it(el) {}
		~Iterator() {}
		bool operator!=(const Iterator& other)
		{
			return this->it != other.it;
		}
		Iterator& operator++()
		{
			it = it->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = it;
			it = it->pNext;
			return old;
		}
		int& operator*()const
		{
			return it->Data;
		}
		int operator*()
		{
			return it->Data;
		}
		friend class List;
	};

public:
	Iterator begin()
	{
		return Iterator(Head);
	}
	Iterator end()
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
		for (auto it: il)push_back(it);
	}
	~List()
	{
		while (Head && Tail)pop_front();
		cout << "LDestructor:\t" << this << endl;
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
	List list = {3,5,8,13,21};
	list.print();
	for (int i: list)
	{
		cout << i << tab;
	}cout << endl;
}