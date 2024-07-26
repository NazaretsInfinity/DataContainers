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
	const int& getHead()const
	{
		return Head->Data;
	}
	ForwardList() // default constructor , creating an empty list
	{
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(int size)
	{
		Head = nullptr;
		if (size != 0)
		{
			Element* New = new Element(rand() % 100);
			Head = New;
			Element* Temp = Head;
			for (int i = 0; i < size-1; i++)
			{
				Element* New = new Element(rand() % 100);
				Temp->pNext = New;
				Temp = Temp->pNext;
			}
		}
		cout << "ListBySize-Constructor:\t" << this << endl;
	}
	~ForwardList()
	{
		Element* Temp = Head;
		while (Temp)
		{
			Element* buf = Temp;
			Temp = Temp->pNext;
			delete buf;
		}
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
		// since push back can't work with emptry list, we have to check if it's empty(then we call push_front instead, 'cause it's able to do it)
		if (!Head)return push_front(Data);
	
			Element* last = Head;
			while (last->pNext)last = last->pNext;
			last->pNext = New;
	}
	void pop_front()
	{
		Element* head = Head;
		Head = Head->pNext;
		delete head;
	}
	void pop_back()
	{
			Element* last = Head;
			if (!last->pNext)pop_front();
			else {
				while (last->pNext->pNext)last = last->pNext;
				delete last->pNext;
				last->pNext = nullptr;
			}
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
				if (!front->pNext) break;
					front = front->pNext;
			}
				New->pNext = front->pNext;
				front->pNext = New;
		}
	}
	void erase(int num)
	{
		if (!num)pop_front();
		else
		{
			Element* front = Head;
			for (int i = 0; i < num-1; i++)
			{
				if (!front->pNext->pNext)break;
				front = front->pNext;
			}
				Element* todel = front->pNext;
				front->pNext = todel->pNext;
				delete todel;
		}
	}
	// methods
	int size()const
	{
		Element* Temp = Head;
		int size = 0;
		while (Temp)
		{
			size++;
			Temp = Temp->pNext;
		}
		return size;
	}
	void print()const
	{
		Element* Temp = Head; // Temp - iterator. It's a pointer with one you can get access to element;
		cout << Head << delimeter;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << "\n\n";
			Temp = Temp->pNext; // move on next element 
		}
	}
	int& operator[](int num)
	{    
		Element* Temp = Head;
		for (int i = 0; i < num; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}
};
ForwardList operator+(ForwardList& A, ForwardList& B)
{
	ForwardList C;
	for (int i = 0; i < A.size()+B.size(); i++)
	{
		if (i >= A.size())C.push_back(B[i-A.size()]);
		else C.push_back(A[i]);
	}
	return C;
}
#define checking
void main()
{

#ifdef checking1
	int n;
	cout << "Enter the amount of elements: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	//list.pop_front();
	//list.pop_back(); cout << "\n\n";
	int s;
	cout << "Enter the number of el to add: "; cin >> s;
	list.insert(666, s); cout << "\n\n";
	list.print();
	cout << "Enter the number of el to delete: "; cin >> s;
	list.erase(s);
	list.print();
#endif 
#ifdef checking2
	int n;
	cout << "Enter the amount of elements: "; cin >> n;
	ForwardList list(n);
	for (int i = 0; i < list.size(); i++)
		cout << list[i] << tab;
	cout << endl;
	list.print();
#endif 
#ifdef checking3
	ForwardList list1(5);
	list1.print();
	ForwardList list2(3);
	list2.print();
	ForwardList list3 = list1 + list2;
	list3.print();
#endif 
}