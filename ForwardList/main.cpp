#include<iostream>
using namespace std;
#define tab "\t"
#define delimeter "\n====================================\n"
class Element
{
	int Data;
	Element* pNext; // p - pointer. Next - next element
public:
	Element(int Data, Element* pNExt = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
class ForwardList
{
	Element* Head; // head of list, pointing at first element 
public:
	ForwardList() // default constructor , creating an empty list
	{
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	 //               Adding elements
	void push_front(int Data)
	{
		//1) created new element; 
		Element* New = new Element(Data);
		//2) Dock new element to the start of list
		New->pNext = Head;	
		Head = New;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		if (Head == nullptr)Head = New;
		else
		{
			Element* last=Head;
			while (last->pNext)last=last->pNext;
			last->pNext = New;
		}
	}

	// methods
	void print()const
	{
		Element* Temp = Head; // Temp - iterator. It's a pointe with one you can get access to element;
		cout << Head << delimeter;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << "\n\n";
			Temp = Temp->pNext; // move on next element 
		}
	}
};
void main()
{
	int n;
	cout << "Enter the amount of elements: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
}