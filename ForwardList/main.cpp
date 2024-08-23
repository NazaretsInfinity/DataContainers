#include "ForwardList.h"
#include"ForwardList.cpp"

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
	ForwardList<std::string> list1 = { "my", "little" };
	list1.print();
	ForwardList<std::string> list2 = { "pony " , "Yuppie!" };
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