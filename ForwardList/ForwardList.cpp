#include"ForwardList.h"

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

template<typename T>ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
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