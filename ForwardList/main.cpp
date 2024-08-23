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

// FORWARD LIST 

template<typename T>Iterator<T> ForwardList<T>::begin()const
{
	return Head;
}
template<typename T>Iterator<T> ForwardList<T>::end()const
{
	return nullptr;
}
template<typename T>int ForwardList<T>::getsize()const
{
	return size;
}
template<typename T>ForwardList<T>::ForwardList() 
{
	size = 0;
	Head = nullptr;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> ForwardList<T>::ForwardList(int size) : ForwardList()
{
	while (size--)push_front(0);
	cout << "ListBySize-Constructor:\t" << this << endl;
}
template<typename T>ForwardList<T>::ForwardList(const ForwardList<T>& other) : ForwardList()
{
	*this = other;
	cout << "CopyConstructor: " << this << endl;
}

template<typename T> ForwardList<T>::ForwardList(ForwardList<T>&& other) : ForwardList()
{
	*this = std::move(other);
	cout << "MoveConstructor: " << this << endl;
}

template<typename T> ForwardList<T>::ForwardList(const initializer_list<T>& il) : ForwardList()
{
	for (const T* it = il.begin(); it != il.end(); it++)push_back(*it);
}
template<typename T>ForwardList<T>::~ForwardList()
{
	while (Head)pop_back();
	cout << "LDestructor:\t" << this << endl;
}
// OPERARORS 

template<typename T>ForwardList<T>&  ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this == &other)return *this;
	this->~ForwardList();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "CopyAssignment: " << this << endl;
	return *this;
}
template<typename T>ForwardList<T>& ForwardList<T>::operator =(ForwardList<T>&& other)
{
	if (this == &other)return *this;
	this->~ForwardList();
	this->Head = other.Head;
	this->size = other.size;
	other.Head = nullptr;
	other.size = 0;
	return *this;
}

template<typename T>void ForwardList<T>::push_front(T Data)
{
	Head = new Element<T>(Data, Head);
	size++;
}
template<typename T>void ForwardList<T>::push_back(T Data)
{
	if (!Head)return push_front(Data);

	Element<T>* last = Head;
	while (last->pNext)last = last->pNext;
	last->pNext = new Element<T>(Data);
	size++;
}
template<typename T> void ForwardList<T>::pop_front()
{
	Element<T>* head = Head;
	Head = Head->pNext;
	delete head;
	size--;
}
template<typename T>void ForwardList<T>::pop_back()
{
	if (!Head->pNext)return pop_front();
	Element<T>* last = Head;

	while (last->pNext->pNext)last = last->pNext;
	delete last->pNext;
	last->pNext = nullptr;
	size--;
}

template<typename T>void ForwardList<T>::insert(T Data, int num)
{
	if (num > size)
	{
		cout << "index's out of range" << endl;
		return;
	}
	if (num == 0)return push_front(Data);
	Element* front = Head;
	for (int i = 0; i < num - 1; i++)
	{

		front = front->pNext;
	}
	front->pNext = new Element(Data, front->pNext);
	size++;
}
template<typename T>void ForwardList<T>::erase(int num)
{
	if (!num)pop_front();
	else
	{
		Element* front = Head;
		for (int i = 0; i < num - 1; i++)
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

template<typename T>void ForwardList<T>::print()const
{
	Element<T>* Temp = Head;
	cout << Head << delimeter;
	while (Temp)
	{
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << "\n\n";
		Temp = Temp->pNext;
	}
}
template<typename T>const T& ForwardList<T>::operator[](int num)const
{
	Element<T>* Temp = Head;
	for (int i = 0; i < num; i++)
	{
		Temp = Temp->pNext;
	}
	return Temp->Data;
}
template<typename T>T& ForwardList<T>::operator[](int num)
{
	Element* Temp = Head;
	for (int i = 0; i < num; i++)
	{
		Temp = Temp->pNext;
	}
	return Temp->Data;
}

template<typename T> ForwardList<T> operator+(const ForwardList<T>& A, const ForwardList<T>& B)
{
	ForwardList<T> C;
	for (int i = 0; i < A.getsize(); i++)C.push_back(A[i]);
	for (int i = 0; i < B.getsize(); i++)C.push_back(B[i]);
	return C;
}



 // ELEMENT 
template<typename T>Element<T>::operator int()
{
	return Data;
}
template<typename T>Element<T>::Element(T Data, Element<T>* pNext) : Data(Data), pNext(pNext)
{
	cout << "EConstructor:\t" << this << endl;
}
template<typename T>Element<T>::~Element()
{
	cout << "EDestructor:\t" << this << endl;
}

 // ITERATOR
template<typename T>::Iterator<T>::Iterator(Element<T>* p) : ptr(p) { cout << "Iconstructor: " << this << endl; }
template<typename T>::Iterator<T>::~Iterator() { cout << "Idestructor: " << this << endl; }
template<typename T>bool Iterator<T>::operator==(const Iterator<T>& other)const
{
	return (this->ptr == other.ptr);
}
template<typename T>bool Iterator<T>::operator!=(const Iterator<T>& other)const
{
	return this->ptr != other.ptr;
}
template<typename T>Iterator<T>& Iterator<T>::operator++()
{
	this->ptr = ptr->pNext;
	return *this;
}
template<typename T>Iterator<T> Iterator<T>::operator++(int)
{
	Iterator old = ptr;
	ptr = ptr->pNext;
	return old;
}
template<typename T>T& Iterator<T>::operator*()const
{
	return ptr->Data;
}
template<typename T>T Iterator<T>::operator*()
{
	return ptr->Data;
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
#ifdef checking
	ForwardList<std::string> list1 = { "bruh", "eh?" };
	list1.print();
	ForwardList<std::string> list2 = { "altough, " , "Yuppie!" };
	list2.print();
	ForwardList<std::string> list3 = list1 + list2;
	list3.print();
#endif 
#ifdef checking4
	int arr[] = { 3,5,8,13,21 };
	//Range-based for:
	for (int i : arr)
	{
		cout << i << tab;
	}
	// Range is a container
	//It means, containers sometimes are being called "range"
	// Therefore, 'Range-based for' is a loop 'for' for container
	ForwardList list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
#endif 
}