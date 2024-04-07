#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

namespace bit
{
	/*   Node��iterator��list����һ����
	
	Node�ฺ���ʾ�ĵ������Ľṹ�����ṩ��صķ����������������

	list�ฺ��������н���Ĺ�ϵ���ṩ����ӿ������û�������������

	iterator�ฺ��ʵ�ַ�װԭ��ָ���ʵ�ֵ�������Ҫ�ķ���   */

	template <class T>
	struct ListNode
	{
		ListNode<T>* _next;//���ĺ��ָ��
		ListNode<T>* _prev;//����ǰ��ָ��
		T _data;//����д�ŵ�����

		ListNode(const T& x = T())//����Node�����͵Ķ���һ��������
			:_next(nullptr)//δ����ָ�����ݣ�x�ͻ���ڸ���������
			, _prev(nullptr)//����ָ�����ݣ�x������Ǹ�ָ�������ݣ�T()��������
			, _data(x)
		{}
	};


	template<class T, class Ref, class Ptr>
	struct ListIterator
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T, Ref, Ptr> iterator;

		Node* _node;

		ListIterator(Node* node)
			:_node(node)
		{}

		// *it
		//T& operator*()
		Ref operator*()
		{
			return _node->_data;
		}

		// it->
		//T* operator->()
		Ptr operator->()
		{
			return &_node->_data;
		}

		// ++it
		iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp(*this);
			_node = _node->_next;

			return tmp;
		}

		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		iterator operator--(int)
		{
			iterator tmp(*this);
			_node = _node->_prev;

			return tmp;
		}

		bool operator!=(const iterator& it)
		{
			return _node != it._node;
		}

		bool operator==(const iterator& it)
		{
			return _node == it._node;
		}
	};



	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		//typedef ListIterator<T> iterator;
		//typedef ListConstIterator<T> const_iterator;

		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;

		//��ʼ��һ���ڱ�λ
		void empty_init()
		{
			_head = new Node();//_headָ��һ���ڶ��Ϲ����Node�����͵����������󣨿ս�㣩
			//����new�Ļ�����Ľ��ռ���ջ�Ͽ��٣������Ƕ���

			//����������β
			_head->_next = _head;//_head���ʽ������е�_nextָ�룬�������д�ŵĵ�ַ�Ǳ�Ϊ_head
			_head->_prev = _head;//_head���ʽ������е�_prevָ�룬�������д�ŵĵ�ַ�Ǳ�Ϊ_head

			//����Ԫ�ظ���Ϊ0
			_size = 0;
		}

		list()//���캯��
		{
			empty_init();//����empty_init��������
		}

		//��ָ��λ��ǰ�����½��
		void insert(iterator pos, const T& val)//pos�ǵ��������͵Ķ������ĳ�Ա_node���ָ��λ�õĵ�ַ
		{
			Node* newnode = new Node(val);//newһ���½�����

			Node* cur = pos._node;//��ȡָ��λ�õĵ�ַ

			Node* prev = cur->_prev;//prev���浱ǰ����ǰһ�������Ϣ

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			_size++;
		}

		//ɾ��ָ��λ�õĽ��
		iterator erase(iterator pos)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;

			delete cur;
			_size--;
			return iterator(next);//ɾ��ָ��λ�õĽ���Ҫ���µ������д�ŵĵ�ַ��Ϣ�����������ʧЧ
		}

		iterator begin()//���ص��������͵Ķ���
		{
			//return iterator(_head->_next);
			//ԭ��ָ��_head����ֱ�ӵ���������ʹ�ã�_head++�ò�����һ��������ĵ�ַ
			//��_head->_next����һ�������������͵Ķ��󣬲���ʼ���ö����е�_node��Ա����
			//_head->_next={xxx}��_node={xxx}����ʼʱ�����д�ŵ�����һ��

			//����õĵ����������͵Ķ���ᱻ���ظ�iterator�����͵ı���it

			//it++����õ����������Ͷ����е�++���غ�����_node = _node->_next;	return *this��
			//������return _headȻ��it++�ͻ�õ���һ������ĵ�ַ

			return _head->_next;//�������͵ĵ����������͵Ķ���_head->_next����ø���Ĺ��캯������һ����������������˵��������캯���ᷢ����ʽ����ת����Node* -> iterator��
		}

		iterator end()
		{
			return _head;//ͬ��
		}

		const_iterator begin()const
		{
			return _head->_next;
		}

		const_iterator end()const
		{
			return _head;
		}

		////��ʼβ�庯��
		//void push_back(const T& x)
		//{
		//	//Node* newnode = new Node(x);//newnodeָ��һ���ڶ��Ϲ��챻x��ʼ����Node�����͵����������󣬹�newnode��������Node*

		//	//Node* tail = _head->_prev;//tailָ���ڱ�λ��ǰ����㣨β��㣩�������ˣ�����Ϳ����ӣ�
		//	//_prev��ŵ���ǰ��������ĵ�ַ�����������Node����tail��Node*

		//	//����ָ��
		//	//tail->_next = newnode;
		//	//newnode->_prev = tail;
		//	//newnode->_next = _head;
		//	//_head->_prev = newnode;
		//}

		//���ýӿں��β�庯��
		void push_back(const T& x)//����end()������end�������������β��������
		{
			insert(end(), x);
		}

		//ͷ�庯��
		void push_front(const T& x)
		{
			insert(begin(), x); // ��������ͷ��������
		}

		//βɾ����
		void pop_back()
		{
			erase(--end());//������--������--���غ���
		}

		//ͷɾ����
		void pop_front()
		{
			erase(begin());
		}

		//�����������Ч���ݵĽ�㣬��Ϊ�������������_head->_next������_head
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);//��ֹ������ʧЧ���⣬erase�᷵�ص����������´�ŵĵ�ַ��Ϣ������it
			}
		}

		//��������
		~list()
		{
			clear();
			delete _head;//ɾ��_headָ��Ŀռ䣨�ڱ�λ������Ϊ֮ǰnew��һ���ڱ�λ�ռ�
			_head = nullptr;//��_head�ÿ�
		}

		//a(b)
		//�������캯��
		list(const list<T>& lt)//const����lt��const list<T>& this,const list<T>& lt��
		{
			empty_init();//�����ڱ�λ
			for (auto& e : lt)//��Ȼ������&���Զ�lt�еĽ���������޸ģ�������Ŀ�Ļ���Ϊ�˷�ֹ����
			{
				push_back(e);//push_back(this,e)��e��ʱ����һ�������������
			}
		}

		//�Զ��彻������
		void swap(list<T>& lt)//�����ô���ֱ����ԭ����������޸ģ���list<T>& this,list<T>& lt��
		{
			std::swap(_head, lt, _head);//�����㷨���ṩ��swap����
			std::swap(_size, lt._size);
		}

		//lt1 =  lt3
		//��ֵ�����������
		list<T>& operator=(list<T> lt)//�Ҳ������󿽱�����һ����ʱ���󣬴����÷��ط��ص��ǽ�����Ķ���
		{
			swap(lt);//��this��lt��
			return *this;//���ؽ�����õ��Ķ���
		}

		//���С
		size_t size()const
		{
			return _size;
		}

		//�п�
		bool empty()
		{
			return _size == 0;
		}

	private:
		Node* _head;//_head����ָ��������ڱ�λ��㣬�����ʵ�������Ľ������������Node*����                
		size_t _size;//_headҲ��Node*��
	};

	//ͷβ�塢ͷβɾ��ָ��λ��ǰ�塢ɾ��ָ��λ�ò����µ��������������Ļ���ʵ��
	void test_list1()
	{
		list<int> lt; 
		lt.push_back(1);
		lt.push_back(2);

		list<int>::iterator it = lt.begin();//it�ǵ��������͵ı���
		//cout << typeid(it).name() << endl;//it��������struct bit::ListIterator<int>

		while (it != lt.end())
		{
			cout << *it << " "; //*it == it.operator*()
			++it;               //++it == it.operator++(int)
		}

		cout << endl;

		lt.push_front(3);
		lt.push_front(4);

		for (auto& e : lt)//������д�ú��÷�Χfor���������Զ����õ�����
		{
			cout << e << " ";
		}

		cout << endl;
	}

	struct A
	{
		int _a1;
		int _a2;

		A(int a1 = 0, int a2 = 0)
			:_a1(a1)
			, _a2(a2)
		{}
	};

	//�������Ľ�������벹��ʵ��
	void test_list2()
	{
		list<A> lt;
		A aa1(1, 1);
		A aa2 = { 1,1 };//C++11�ṩ�Ķ�����Ĺ��캯������ʽ����ת����initializer_list���ͱ�ΪA����
		lt.push_back(aa1);//ʹ����������β��
		lt.push_back(aa2);
		lt.push_back(A(2, 2));//�乹��������β��
		lt.push_back({ 3,3 });//������Ĺ��캯������ʽ����ת��
		lt.push_back({ 4,4 });

		list<A>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//cout << *it << endl;////*it�õ�it�д�ŵ�A�����Ͷ����Զ����������ݲ�֧��������

			//��ȡA�����Ͷ����д�ŵĳ�Ա������ֵ
			//����һ��*.
			//cout << (*it)._a1 << ":" << (*it)._a2 << endl;
			//++it;//ָ�������д�ŵ���һ��A�����͵Ķ���

			//��������->
			cout << it->_a1 << ":" << it->_a2 << endl;
			++it;


			//�ȼ��ڣ�cout << it->->_a1 << ":" << it->->_a2 << endl;//������Ϊ�˿ɶ���ʡ����һ��->
			//�ȼ��ڣ�cout << it.operator->()->_a1 << ":" << it.operator->()->_a2 << endl;	
			//it.operator->()->_a1 : ��A* "����"ָ�룩 -> _a1
		}
		cout << endl;
	}


	//��ӡ����
	void PrintList(const list<int>& clt)//������Ǳ�const���ε�clt��ֻ����
	{
		//list<int>::iterator it = clt.begin();//������ͨ���������������ķ��ʻ����Ȩ�޷Ŵ�
		list<int>::const_iterator it = clt.begin();//const���ε�����ͬ����Ҫ��const���εĵ�����
		while (it != clt.end())
		{
			cout << *it << " ";
			++it;
		}

		cout << endl;
	}

	///������������ʵ��
	void test_list3()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);

		PrintList(lt);

		list<int> lt1(lt);

		PrintList(lt1);
	}
}

