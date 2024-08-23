#include"List.h"
#include"list.cpp"
using namespace std;
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