#include<iostream>
using namespace std;
#define tab '\t'
class Element;
template<typename T> class List
{
	class Element
	{
		T Data; // value of element
		Element* pNext; // p - pointer
		Element* pPrev; // Prev-previous element
	public:
		Element(T Data, Element* Next = nullptr, Element* Prev = nullptr) : Data(Data), pNext(Next), pPrev(Prev)
		{
			cout << "EConstructor: " << this << endl;
		}
		~Element()
		{
			cout << "EDestructor: " << this << endl;
		}
		friend class List;
	}*Head, * Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* it;
	public: 
		ConstBaseIterator(Element* it = nullptr) : it(it) {};
		~ConstBaseIterator() {};
		bool operator==(const ConstBaseIterator& other)
		{
			return this->it == other.it;
		}
		bool operator!=(const ConstBaseIterator& other)
		{
			return this->it != other.it;
		}
		const T& operator*()const
		{
			return it->Data;
		}
		friend class List;
	};

public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* it = nullptr) : ConstBaseIterator(it) {}
		~ConstIterator() {}
		ConstIterator& operator++()
		{
			ConstBaseIterator::it = ConstBaseIterator::it->pNext;
			return *this;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::it = ConstBaseIterator::it->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::it = ConstBaseIterator::it->pPrev;
			return old;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = ConstBaseIterator::it;
			ConstBaseIterator::it = ConstBaseIterator::it->pNext;
			return old;
		}
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp){}
		~ConstReverseIterator(){}
		// increment decrement
		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::it = ConstBaseIterator::it->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = ConstBaseIterator::it;
			ConstBaseIterator::it = ConstBaseIterator::it->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::it = ConstBaseIterator::it->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::it= ConstBaseIterator::it->pNext;
			return old;
		}
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* it = nullptr):ConstIterator(it){}
		~Iterator(){}
		T& operator*()
		{
			return ConstBaseIterator::it->Data;
		}
	};

	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* it = nullptr) :ConstReverseIterator(it) {}
		~ReverseIterator() {}
		T& operator*()
		{
			return ConstBaseIterator::it->Data;
		}
	};

	// END & BEGIN
	ConstReverseIterator rbegin()const;
	ReverseIterator rbegin();
	ConstReverseIterator rend()const;
	ReverseIterator rend();
	ConstIterator begin()const;
	Iterator begin();
	ConstIterator end()const;
	Iterator end();


	List();
	List(const initializer_list<T>& il);
	List(const List<T>& other);
	~List();
	List<T>& operator =(const List<T>& other);
	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(T Data, size_t num);
	void erase(int num);
	// METHODS 
	void reverse_print()const;
	void print()const;
};


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
		//1) move head on next element
		Head = Head->pNext;
		//2) delete this fignya
		delete Head->pPrev;
		//3) give fignya nullptr
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
//  LIST METHODS END
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
	//list.print();
	//cout << "Enter number of the element to delete: "; cin >> s;
	//list.erase(s);
	list.print();
#endif 
#ifdef checking2
	List<double> list = { 3,5,8,13,21 };
	for (List<double>::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}cout << "\n\n";
	for (List<double>::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}cout << endl;
#endif 
#ifdef checking
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (int i : list3)
	{
		cout << i << tab;
	}cout << endl;
#endif 
}