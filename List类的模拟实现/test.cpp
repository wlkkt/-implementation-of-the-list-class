#include "list.h"

//list����Сʵ��
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
//	//����
//	lt.reverse();
//
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	///����(����)
//	lt.sort();
//
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	//�º���������
//	lt.sort(greater<int>());
//	for (auto e : lt)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	//ȥ��
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


	//�Լ�ת�Ƹ��Լ�
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
	//����һ������ת�Ƹ��Լ���ֻҪ��������Ľ������һ�£�
	lt.splice(lt.begin(), lt1);//��lt1����ȫ��ת����lt�����ͷ��

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
	for (auto e : lt1)//ת�ƺ�lt1û�ÿ���ָ��Ľ����
	{
		cout << e << " ";
	}
	return 0;
}