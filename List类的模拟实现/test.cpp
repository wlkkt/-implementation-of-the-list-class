#include "list.h"

//list功能小实验
//int main()
//{
//	list<int> lt;
//	lt.push_back(1);
//	lt.push_back(2);
//	lt.push_back(3);
//	lt.push_back(4);
//	lt.push_back(5);
//	lt.push_back(2);
//	lt.push_back(3);
//	lt.push_back(4);
//	lt.push_back(2);
//	lt.push_back(5);
//
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	//逆置
//	lt.reverse();
//
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	///排序(升序)
//	lt.sort();
//
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	//仿函数（降序）
//	lt.sort(greater<int>());
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	//去重
//	lt.unique();
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	return 0;
//}

int main()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);


	//自己转移给自己
	lt.splice(lt.end(), lt, lt.begin());
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;


	list<int> lt1;
	lt1.push_back(10);
	lt1.push_back(20);
	lt1.push_back(30);
	lt1.push_back(40);
	//将另一个链表转移给自己（只要两个链表的结点类型一致）
	lt.splice(lt.begin(), lt1);//将lt1链表全部转移至lt链表的头部

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
	for (auto e : lt1)//转移后lt1没用可以指向的结点了
	{
		cout << e << " ";
	}
	return 0;
}