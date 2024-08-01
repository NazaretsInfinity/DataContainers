#include<iostream>
using namespace std;
#define tab '\t'
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

		//size_t is a 'typedef' on 'unsigned int' 
		// typedef - derective , it creates a nickname for existing type of data(int ,etc)
		// typedef have this syntax:
		// typedef (type) nickname 
		friend class List;
	}*Head, * Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
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
		Element* buffer = Head;
		Head->pPrev = nullptr;
		Head = Head->pNext;
		delete buffer;
		size--;
	}
	void pop_back()
	{
		Element* buffer = Tail;
		if (Tail->pPrev)
		{
			Tail->pPrev->pNext = nullptr;
			Tail = Tail->pPrev;
		}
		else Head = Tail = nullptr;
		delete buffer;
		size--;
	}

	// METHODS 
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp -> pNext << endl;
		}
			cout << "Amount of elements: " << size << endl;
	}
};
void main()
{
	setlocale(LC_ALL, "");
	List list; 
	list.push_back(0);
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.print();
	list.pop_back();
	list.pop_back();
	list.pop_back();
	list.pop_back();
	list.pop_back();
	list.print();
}