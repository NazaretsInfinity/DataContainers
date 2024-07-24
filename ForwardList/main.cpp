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
			Element* last = Head;
			while (last->pNext)last = last->pNext;
			last->pNext = New;
		}
	}
	void pop_front()
	{
		Head->~Element();
		Head = Head->pNext;
	}
	void pop_back()
	{
			Element* last = Head;
			while (last->pNext->pNext)last = last->pNext;
			delete last->pNext;
			last->pNext = nullptr;
	}

	void insert(int Data, int num)
	{
		if (num==0)push_front(Data);
		else
		{
			Element* New = new Element(Data);
			Element* front = Head;
			for (int i = 0; i < num - 1; i++)
			{
				front = front->pNext;
			}
			New->pNext = front->pNext;
			front->pNext = New;
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
		list.push_back(rand() % 100);
	}
	list.print();
	list.insert(666,0); cout << "\n\n";
	list.pop_front();
	list.insert(666,7); cout << "\n\n";
	list.pop_back(); cout << "\n\n";
	list.print();
}