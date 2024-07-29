#include<iostream>
using namespace std;
#define tab "\t"
#define delimeter "\n====================================\n"
class Element
{
	int Data;
	Element* pNext; // p - pointer. Next - next element
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	int getDATA()const
	{
		return Data;
	}
	Element* getNELEMENT()
	{
		return pNext;
	}
	friend class ForwardList;
};
class ForwardList
{
	int size;
	Element* Head; // head of list, pointing at first element 
public:
	const int& getHead()const
	{
		return Head->Data;
	}
	int getsize()const
	{
		return size;
	}
	ForwardList() // default constructor , creating an empty list
	{
		size = 0;
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(int size) : ForwardList() 
	{
		this->size = size;
		while (size--)push_front(0);
		cout << "ListBySize-Constructor:\t" << this << endl;
	}
	// COPY 
	ForwardList(const ForwardList& other) : ForwardList()
	{
		*this = other;
		cout << "CopyConstructor: " << this << endl;
	}
	 // MOVE
	ForwardList(ForwardList&& other) : ForwardList()
	{
		*this = std::move(other);
		cout << "MoveConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	// OPERARORS 

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment: " << this << endl;
		return *this;
	}
	ForwardList& operator =(ForwardList&& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		return *this;
	}
	 // Adding elements
	void push_front(int Data)
	{
	    /*Element* New = new Element(Data);
		New->pNext = Head;	
		Head = New;*/
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		// since push back can't work with emptry list, we have to check if it's empty(then we call push_front instead, 'cause it's able to do it)
		if (!Head)return push_front(Data);
	
			Element* last = Head;
			while (last->pNext)last = last->pNext;
			last->pNext = new Element(Data);
			size++;
	}
	void pop_front()
	{
		Element* head = Head;
		Head = Head->pNext;
		delete head;
		size--;
	}
	void pop_back()
	{
			if (!Head->pNext)return pop_front();
			Element* last = Head;
			
				while (last->pNext->pNext)last = last->pNext;
				delete last->pNext;
				last->pNext = nullptr;
			
			size--;
	}

	void insert(int Data, int num)
	{
		if (num > size)
		{
			cout << "index's out of range" << endl;
			return;
		}
		if (num==0)return push_front(Data);


			//Element* New = new Element(Data);
			Element* front = Head;
			for (int i = 0; i < num - 1; i++)
			{
				//if (!front->pNext) break;
					front = front->pNext;
			}
			front->pNext = new Element(Data, front->pNext);
		size++;
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
		size--;
	}
	// methods
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
	const int& operator[](int num)const
	{    
		Element* Temp = Head;
		for (int i = 0; i < num; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
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
ForwardList operator+(ForwardList A, ForwardList B)
{
	ForwardList C;
	for (int i = 0; i < A.getsize(); i++)C.push_back(A[i]);
	for (int i = 0; i < B.getsize(); i++)C.push_back(B[i]);
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
	ForwardList list(5);
	for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << tab << endl;
	}
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
	ForwardList list(0);
	list.push_front(1);
	list.push_front(1);
	list.push_front(1);
	list.print();
}