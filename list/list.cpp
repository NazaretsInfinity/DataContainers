#include"List.h"
// ELEMENT 
template<typename T> List<T>::Element::Element(T Data, Element* Next, Element* Prev) : Data(Data), pNext(Next), pPrev(Prev)
{
	cout << "EConstructor: " << this << endl;
}
template<typename T> List<T>::Element::~Element()
{
	cout << "EDestructor: " << this << endl;
}
// CONST BASE OPERATOR

template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)
{
	return this->it == other.it;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)
{
	return this->it != other.it;
}
template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return it->Data;
}

//CONSTREVERSEITERATOR
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::it = ConstBaseIterator::it->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = ConstBaseIterator::it;
	ConstBaseIterator::it = ConstBaseIterator::it->pPrev;
	return old;
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::it = ConstBaseIterator::it->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::it = ConstBaseIterator::it->pNext;
	return old;
}

//CONSTITERATOR
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::it = ConstBaseIterator::it->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::it = ConstBaseIterator::it->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::it = ConstBaseIterator::it->pPrev;
	return old;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = ConstBaseIterator::it;
	ConstBaseIterator::it = ConstBaseIterator::it->pNext;
	return old;
}

// ITERATOR
template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::it->Data;
}

// REVERSEITERATOR
template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::it->Data;
}


// LIST METHODS
template<typename T> typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template<typename T> typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T> typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const initializer_list<T>& il) : List()
{
	for (const T* it = il.begin(); it != il.end(); ++it)push_back(*it);
}
template<typename T>List<T>::List(const List<T>& other) : List()
{
	*this = other;
	cout << "CopyConstructor: " << this << endl;
}
template<typename T>List<T>::~List()
{
	while (Head && Tail)pop_front();
	cout << "LDestructor:\t" << this << endl;
}

template<typename T>List<T>& List<T>::operator =(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "CopyAssignment: " << this << endl;
	return *this;
}


template<typename T>void List<T>::push_front(T Data)
{
	if (!(Head && Tail))Head = Tail = new Element(Data);
	else
	{
		Head = Head->pPrev = new Element(Data, Head);
	}
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (!(Head && Tail))Head = Tail = new Element(Data);
	else
	{
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;
}
template<typename T>void List<T>::pop_front()
{
	if (!(Head && Tail))return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	size--;
}
template<typename T>void List<T>::pop_back()
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
template<typename T>void List<T>::insert(T Data, size_t num)
{
	if (num >= size)return push_back(Data);
	if (num == 0)return push_front(Data);
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
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}
template<typename T>void List<T>::erase(int num)
{
	if (num >= size - 1)return pop_back();
	if (num == 0)return pop_front();
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



template<typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pNext << tab << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;

	}
	cout << "Amount of elements: " << size << endl;
}
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Amount of elements: " << size << endl;
}

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
	}
	return buffer;
}