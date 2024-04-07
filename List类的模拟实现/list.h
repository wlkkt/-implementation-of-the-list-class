#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

namespace bit
{
	/*   Node、iterator、list都是一个类
	
	Node类负责表示的单个结点的结构，并提供相关的方法来操作单个结点

	list类负责管理所有结点间的关系及提供对外接口来让用户操作整个链表

	iterator类负责实现封装原生指针和实现迭代器需要的方法   */

	template <class T>
	struct ListNode
	{
		ListNode<T>* _next;//结点的后继指针
		ListNode<T>* _prev;//结点的前驱指针
		T _data;//结点中存放的数据

		ListNode(const T& x = T())//构造Node类类型的对象（一个结点对象）
			:_next(nullptr)//未传入指定数据，x就会等于该匿名对象
			, _prev(nullptr)//传入指定数据，x会等于那个指定的数据，T()不起作用
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

		//初始化一个哨兵位
		void empty_init()
		{
			_head = new Node();//_head指向一个在堆上构造的Node类类型的匿名结点对象（空结点）
			//不加new的话链表的结点空间在栈上开辟，而不是堆上

			//连接链表首尾
			_head->_next = _head;//_head访问结点对象中的_next指针，并将其中存放的地址是变为_head
			_head->_prev = _head;//_head访问结点对象中的_prev指针，并将其中存放的地址是变为_head

			//链表元素个数为0
			_size = 0;
		}

		list()//构造函数
		{
			empty_init();//调用empty_init函数即可
		}

		//在指定位置前插入新结点
		void insert(iterator pos, const T& val)//pos是迭代器类型的对象，它的成员_node存放指定位置的地址
		{
			Node* newnode = new Node(val);//new一个新结点对象

			Node* cur = pos._node;//获取指定位置的地址

			Node* prev = cur->_prev;//prev保存当前结点的前一个结点信息

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			_size++;
		}

		//删除指定位置的结点
		iterator erase(iterator pos)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;

			delete cur;
			_size--;
			return iterator(next);//删除指定位置的结点后要更新迭代器中存放的地址信息，否则迭代器失效
		}

		iterator begin()//返回迭代器类型的对象
		{
			//return iterator(_head->_next);
			//原生指针_head不能直接当作迭代器使用，_head++得不到下一个结点对象的地址
			//用_head->_next构造一个迭代器类类型的对象，并初始化该对象中的_node成员变量
			//_head->_next={xxx}、_node={xxx}，起始时二者中存放的内容一样

			//构造好的迭代器类类型的对象会被返回给iterator类类型的变量it

			//it++会调用迭代器类类型对象中的++重载函数：_node = _node->_next;	return *this，
			//而不是return _head然后it++就会得到下一个对象的地址

			return _head->_next;//返回类型的迭代器类类型的对象，_head->_next会调用该类的构造函数构造一个对象出来，运用了单参数构造函数会发生隐式类型转换（Node* -> iterator）
		}

		iterator end()
		{
			return _head;//同理
		}

		const_iterator begin()const
		{
			return _head->_next;
		}

		const_iterator end()const
		{
			return _head;
		}

		////初始尾插函数
		//void push_back(const T& x)
		//{
		//	//Node* newnode = new Node(x);//newnode指向一个在堆上构造被x初始化的Node类类型的匿名结点对象，故newnode的类型是Node*

		//	//Node* tail = _head->_prev;//tail指向哨兵位的前驱结点（尾结点），工具人，用完就可以扔，
		//	//_prev存放的是前驱结点对象的地址，结点类型是Node，故tail是Node*

		//	//交换指向
		//	//tail->_next = newnode;
		//	//newnode->_prev = tail;
		//	//newnode->_next = _head;
		//	//_head->_prev = newnode;
		//}

		//复用接口后的尾插函数
		void push_back(const T& x)//调用end()函数，end函数返回链表的尾部迭代器
		{
			insert(end(), x);
		}

		//头插函数
		void push_front(const T& x)
		{
			insert(begin(), x); // 返回链表头部迭代器
		}

		//尾删函数
		void pop_back()
		{
			erase(--end());//迭代器--，调用--重载函数
		}

		//头删函数
		void pop_front()
		{
			erase(begin());
		}

		//清除链表存放有效数据的结点，因为迭代器传入的是_head->_next而不是_head
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);//防止迭代器失效问题，erase会返回迭代器中最新存放的地址信息，更新it
			}
		}

		//销毁链表
		~list()
		{
			clear();
			delete _head;//删除_head指向的空间（哨兵位），因为之前new了一个哨兵位空间
			_head = nullptr;//将_head置空
		}

		//a(b)
		//拷贝构造函数
		list(const list<T>& lt)//const修饰lt（const list<T>& this,const list<T>& lt）
		{
			empty_init();//创建哨兵位
			for (auto& e : lt)//虽然这里是&可以对lt中的结点对象进行修改，但本质目的还是为了防止拷贝
			{
				push_back(e);//push_back(this,e)，e此时就是一个结点对象的引用
			}
		}

		//自定义交换函数
		void swap(list<T>& lt)//传引用传参直接在原对象基础上修改，（list<T>& this,list<T>& lt）
		{
			std::swap(_head, lt, _head);//借用算法库提供的swap函数
			std::swap(_size, lt._size);
		}

		//lt1 =  lt3
		//赋值运算符的重载
		list<T>& operator=(list<T> lt)//右操作对象拷贝构造一个临时对象，传引用返回返回的是交换后的对象
		{
			swap(lt);//（this，lt）
			return *this;//返回交换后得到的对象
		}

		//求大小
		size_t size()const
		{
			return _size;
		}

		//判空
		bool empty()
		{
			return _size == 0;
		}

	private:
		Node* _head;//_head用于指向链表的哨兵位结点，结点类实例化出的结点对象的类型是Node*，故                
		size_t _size;//_head也是Node*型
	};

	//头尾插、头尾删、指定位置前插、删除指定位置并更新迭代器，迭代器的基础实现
	void test_list1()
	{
		list<int> lt; 
		lt.push_back(1);
		lt.push_back(2);

		list<int>::iterator it = lt.begin();//it是迭代器类型的变量
		//cout << typeid(it).name() << endl;//it的类型是struct bit::ListIterator<int>

		while (it != lt.end())
		{
			cout << *it << " "; //*it == it.operator*()
			++it;               //++it == it.operator++(int)
		}

		cout << endl;

		lt.push_front(3);
		lt.push_front(4);

		for (auto& e : lt)//迭代器写好后用范围for，编译器自动调用迭代器
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

	//迭代器的进阶理解与补充实现
	void test_list2()
	{
		list<A> lt;
		A aa1(1, 1);
		A aa2 = { 1,1 };//C++11提供的多参数的构造函数的隐式类型转换，initializer_list类型变为A类型
		lt.push_back(aa1);//使用有名对象尾插
		lt.push_back(aa2);
		lt.push_back(A(2, 2));//匿构造名对象并尾插
		lt.push_back({ 3,3 });//多参数的构造函数的隐式类型转换
		lt.push_back({ 4,4 });

		list<A>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//cout << *it << endl;////*it得到it中存放的A类类型对象，自定义类型数据不支持流插入

			//获取A类类型对象中存放的成员变量的值
			//方法一：*.
			//cout << (*it)._a1 << ":" << (*it)._a2 << endl;
			//++it;//指向链表中存放的下一个A类类型的对象

			//方法二：->
			cout << it->_a1 << ":" << it->_a2 << endl;
			++it;


			//等价于：cout << it->->_a1 << ":" << it->->_a2 << endl;//编译器为了可读性省略了一个->
			//等价于：cout << it.operator->()->_a1 << ":" << it.operator->()->_a2 << endl;	
			//it.operator->()->_a1 : （A* "匿名"指针） -> _a1
		}
		cout << endl;
	}


	//打印函数
	void PrintList(const list<int>& clt)//传入的是被const修饰的clt（只读）
	{
		//list<int>::iterator it = clt.begin();//错误，普通迭代器对链表对象的访问会造成权限放大
		list<int>::const_iterator it = clt.begin();//const修饰的链表，同样的要用const修饰的迭代器
		while (it != clt.end())
		{
			cout << *it << " ";
			++it;
		}

		cout << endl;
	}

	///迭代器的最终实现
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

