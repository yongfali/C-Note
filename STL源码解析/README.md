## STL源码解析

### 第一章：STL源码概述与版本介绍
* 前闭后开区间[first, last)，表示从first开始，直到last-1，迭代器最后一个指的是最后一个元素的下一个位置，如下图所示
> ![](Images/Iterator.png)
* STL中的迭代器实际上可以理解为一种泛化的指针类型，重载了operator*(), operator->(),operator++()和operator++(int)
* 仿函数实际上是重载了 
```c++
template<typename T>
class C{
public:
	T operator()(param lists){
		...
	}
};

int main(){
	C<T> cObj;

	//以下使用仿函数，就像使用一般函数一样
	cout << cObj(value lists) << endl;

	//以下使用仿函数，会先产生临时对象（第一对小括号），然后临时对象调用第二对小括号
	cout << cObj()(value lists) << endl;

	return 0;
}
```

### 第二章：空间配置器
* SGI 虽然也定义有一个符合部分标准、名为allocator的配置器，但是SGI却从未使用过，也不建议我么使用，主要是因为其效率不佳，他只是把C++的::operator new 和::operator delete 做了一层薄薄的包装
* STL规定的配置器结构示意图如下
> ![](Images/STL_allocator.png)

### 第三章：迭代器概念与traits编程技法
* STL的中心思想就是将容器和算法分开，彼此独立设计，最后通过一个迭代器使他们链接在一起（迭代器扮演桥梁的作用）
* 迭代器相应型别有五种
> 1. value type:是指迭代器所指对象的型别
> 2. difference type：是指两个迭代器之间的距离，可以用来表示一个容器的最大容量
> 3. reference type 
> 4. pointer type
> 5. iterator_category：包括input iterator（只读）,output iterator（维写）, forward iterator, bidirectional iterator（双向迭代器）, random access iterator（随机迭代器，支持偏移量大于1）
* [traits编程](https://blog.csdn.net/shudou/article/details/10270971 "traits编程详解")主要是帮助算法识别迭代器的属性（通过内嵌的类型声明），提升算法的运行效率
```c++
template<typename Iterator, typename T>
void func_impl(Iterator iter, T t)
{
    T temp;//这里就解决了问题
    //这里做原本func()的工作
}
 
template<typename Iterator>
void func(Iterator iter)
{
    func_impl(iter, *iter);//func的工作全部都移到func_impl里面了
}
 
int main(int argc, const char *argv[])
{
    int i;
    func(&i);
}
//函数func作为对外接口，实际的操作却由函数func_impl执行，通过函数func_impl的参数类型推导，获取到Iterator指向对象的类型T，但是如果需要返回类型是迭代器所指对象的类型，其无能为力了
```

### 第四章：序列容器
### 1. vector概述
* vector是动态的array，当容量不足时以两倍的方式进行扩容，然后完成元素的搬迁和原空间的释放，位于头文件<vector>中

**1.1. vector定义摘要**
* SGI STL将vector实现于更底层的<stl_vector.h>

**1.2. vector的迭代器**
```c++
//vector容器的迭代器模板
tempalte <typename T, class Alloc = alloc>
class vector{
public:
	typedef T value_type;
	typedef value_type* iterator;
...
};
```
**1.3. vector的数据结构**
* vector采用的数线性连续空间，它以两个迭代器start和finish分别指向配置来的连续空间目前已经使用的范围，并以迭代器end_of_storage指向整个连续空间的尾端（包含备用空间）。具体示意图如下图所示

```c++
template <typename T, class Alloc = alloc>
class vector{
//嵌套类型
public:
	typedef T           value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef value_type& reference;
	typedef size_t      size_type;
	typedef ptrdiff_t difference_type;
...
protected:
	iterator start;
	iterator finish;
	iterator end_of_storage;

public:
	iterator begin(){return start;}
	iterator end(){return finish;}
	size_type size() const{return size_type(end() - begin());}
	size_type capacity() const{return size_type(end_of_storage - begin());}
	bool empty(){return begin() == end();}
	reference operator[](size_type n) {return *(beging() + n);}
	reference front() {return *(begin());}
	reference back() {return *(end() - 1);}
...
};
```
> ![](Images/vector_struct.png)

**1.4. vector 的构造与内存管理**
* vector提供了很多默认的构造函数，其中一个允许我们指定空间大小及初值
```c++
//构造函数
vector(size_type n, const T& value){fill_initialize(n, value);}

//填充并初始化
void fill_initialize(size_type n, const T& value){
	start = allocate_and_fill(n, value);
	finish = start + n;
	end_of_storage = finish;
}

//配置而后填充
iterator allocate_and_fill(size_type n, const T& x){
	iterator result = data_allocator::allocate(n); //配置n个元素空间
	uninitialized_fill_n(result, n, x); //会根据第一参数的型别特性决定使用算法fill_n()或反复调用construct()
	return result;
}
```
* push_back()将新元素插入时会先检测是否还要备用空间，有的话直接插入并调整finish++，否则就扩充空间（重新配置两倍大小空间->移动数据->释放原来的空间），这个过程会使院迭代器失效，因此需要赋值给一个新的迭代器

**1.5. vector的元素操作：pop_back, erase,clear,insert**

#### 2. list概述
* list是一个双向链表，空间不是连续的，对于删除和插入永远是常数个时间
```c++
template <typename T>
struct __list_node{
	typedef void* void_pointer;
	void_pointer prev; // void型，其实可以设为__list_node<T>*
	void_pointer next;
	T data;
}
```
* list的插入和删除只会使被操作的节点的迭代器失效，因为其地址不是连续的，因此只需要对迭代器指针++即可，而vector由于其连续的存储空间会导致元素位置的前移或后移而使得所有迭代器指针失效
> ![](Images/list_iterator.png)

**2.1. list的构造与内存管理**
* list_test.cpp测试了list的部分操作
* 它的构造和析构同vector大致相似
* list提供一个默认的构造函数不指定任何参数而创建一个空list，如下图所示
```c++
public:
	list(){empty_initialize();}

protected:
	void empty_initialize(){
		node = get_node();
		node -> prev = node;
		node -> next = node;
	}
```
> ![](Images/empty_list.png)
* list的push_back()函数内部实际上调用的是insert函数
```c++
void push_back(const T& x){ insert(end(), x);}
```
**2.2 list的操作**
* 常见的操作有push_front(),push_back(),erase(),pop_front(),pop_back(),clear(),remove(),unique(),splice(),merge(),reverse(),sort()
* 由于list不是连续的因此clear()nebula是不是通过erase删除区间来执行的，而是通过循环遍历一个一个节点删除，析构的
* list内部提供了一个所谓的迁移操作（transfer）：将某连续范围内的元素迁移到指定的位置之前。这也是为实现splice、sort和merge等奠定了基础

#### 3. deque

**3.1 deque概述**
* 是一个双向开口的连续线性存储空间，即容器两端都可以进行插入和删除操作，示意图如下
> ![](Images/deque_struct.png)
* deque和vector的区别在于，前者没有容量的概念，因为它是一个动态分段连续的空间组成的（也称为缓冲区，可以看做是一个个的vector组成），有段控中心对分配的每一段进行管理（段控中心实际上就是一个map,每一个map对应管理一个连续的缓存空间区)
* deque 本身比较复杂其内部的实现，因此其迭代器的实现也很复杂，主要在分段连续中的迭代器的++或--和跳转操作等如何实现平滑的转移而让用户没有察觉，因此在能用vector解决问题的时候，尽量不要使用deque
* deque内部的排序是通过先把元素复制到vector中排好序后再复制回来
* ![](Images/deque.png)

**3.2 deque的迭代器**
* deque的中控器（控制中心）、缓冲区、迭代器的示意图如下所示
> ![](Images/deque_iterator.png)
* 注：迭代器中包含四部分
> 1. cur表示所指的缓冲区中现行元素（deque是由多个缓冲区拼接而成的），如上图所示
> 2. first 表示此迭代器所指缓冲区的头
> 3. last表示此迭代器所指指缓冲区的尾（含备用空间）
> 4. node 指向段控中心，对应map中的哪一个节点

**3.3 deque的数据结构**
* 和其它序列容器相似

**3.4 deque的构造与内存管理**
* deque的段控中心map一般会前后预留一些，以便扩充时用
* map的每个节点对应一个缓冲区（一个缓冲区一般是一个连续的vector实现）map start指针刚开始一般位于段控中心中部，这样便于头尾的扩充
* 当缓冲内容不足时会触发push_back_aux()先配置一块新的缓冲区，再设新元素内容，然后更改迭代器finish的状态
* 具体可以通过以下两个图理解，第二个图对应的是触发了push_back_aux()
> ![](Images/deque_status.png)
> ![](Images/deque_status2.png)
* 前端插入同后端插入原理相似，触发的是push_front_aux()函数而已

**3.5 deque的常见操作**
* pop_back(),pop_front(),push_back(),push_front(),clear(),erase(),insert(),empty(),size()等

#### 4. stack

**4.1 概述**
* stack是一种后进先出的数据结构，只允许对栈顶的元素进行操作，位于头文件```<stack>```中。不存在遍历行为，因此没有迭代器，结构如下图所示
> ![](Images/stack.png)
* stack的底层默认实现是deque，是对其进行了一些定制化的改变，因此也称为容器适配器
```c++
template <typename T, class Sequence = deque<T> >
class stack{
	.....
};
```
* stack 也可以使用list作为其底层的序列容器，因为list也满足双端开口和一些基本的容器函数

#### 5. queue

**5.1 概述**
* queue是一种先进先出的数据结构，位于头文件```<queue>```中，只允许从队尾插入新值，从队首删除元素，其它位置元素则不可获取或操作，也没有迭代器，结构如下图所示
> ![](Images/queue.png)
* queue的底层默认实现是deque，是对其进行了一些定制化的改变，因此也称为容器适配器
```c++
template <typename T, class Sequence = deque<T> >
class queue{
	.....
};
```

#### 5. heap

**5.1 概述**
* heap不属于STL容器的组建，但是他是实现优先队列的底层机制
* heap内部是一个完全二叉树，可以用一个数组或vector表示，位置0表示堆顶元素，根据堆顶元素可以分为max-heap和min-heap
> max-heap指的是二叉树中的每一个父节点都大于其左右子节点，STL默认的是max-heap
> min-heap指的是二叉树中的每一个父节点都小于其左右子节点

**5.2 heap算法**
* push_heap算法，实际上就是一个堆排序算法，通过不断地调整二叉树中父节点和左右子节点的大小而实现的
> 可参见我的[排序算法-堆排序](https://github.com/yongfali/JianzhiOffer/blob/master/allSort.cpp "堆排序算法代码")
> ![](Images/push_heap.png)
* pop_heap算法，每次取出堆顶元素然后调整元素使之为新的堆，<strong>实际上是把堆顶元素放入到vector或array的尾端，完成删除操作。</strong> 同push_heap算法实现原理一样，都对应堆排序
> ![](Images/pop_heap.png)
* 
sort_heap算法实际就是不断的pop然后调整堆顶元素的过程，从而达到排序的过程，大顶堆可以实现递增排序，小顶堆可以实现递减排序
* make_heap算法，生成堆的过程,传入迭代器的首尾指针即可
* heap的测试见heap_test.cpp 

#### 6. priority_queue

**6.1 概述**
* 可以理解为一个拥有权值的queue，缺省情况下是一个max-heap，内部实现的默认容器是vector，再加上heap的处理规则就行，也是一种容器适配器
```c++
template <typename T, class Sequence = vector<int>
			class Compare = less<typename Sequence::value_type> >
class  priority_queue{
	....
};
```
*  priority_queue 位于头文件```c++ <queue> ```中，没有迭代器，只能对队首的元素进行读取操作，因此也不提供遍历的功能

#### 7. slist

**7.1 概述**
* Slist与list的区别在于前者是单向链表，并且不是STL中标准的容器，不过单向链表消耗的空间更小，某些操作效率更高
* 由于单向因此，在指定位置插入或删除都需要从头遍历链表因此，slist只提供了insert_after()和erase_after()，当然也不提供push_back，而是提供push_front，有点类似于倒序创建链表

### 第五章：关联式容器
* 标准的关联式容器包括set和map，以及他两的衍生体multiset和multimap，他们的底层实现均为红黑树
* SGI STL还提供了不在标准规范之内的关联容器，hash_set和hash_map，以及对应的hash_multiset和hash_multimap，他们的底层均为hashmap
> ![](Images/all_container.png)
**1. 树的介绍**
* 平衡树指的是任意一个节点的左右子树的深度之差不超过1，限制这一条件主要是为了防止树在频繁的插入和删除过程中退化为单链表
* 树的平衡被破坏指的是某个节点的左右子树的深度之差为2，具体可以分为以下四种情况
> 1. 插入节点位于X的左子节点的左子树-左左
> 2. 插入节点位于X的左子节点的右子树-左右
> 3. 插入节点位于X的右子节点的左子树-右左
> 4. 插入节点位于X的右子节点的右子树-右右
> ![](Images/AVL_tree.png)

* 针对以上四种情况其中1和4称为外侧插入，可以通过单旋转的方式进行调整，2和3称为内侧插入，可通过双旋转方式调整
> ![](Images/tree_single_rotation.png) ![](Images/tree_double_rotation.png)

* **右旋即将当前节点调转至其左孩子节点的右节点，左旋则为右孩子的左节点，红黑树旋转只此两种。实际上只针对不平的点进行旋转调整**

**1.2 红黑树（RB-tree）**
* 也是一种特殊二叉搜索树，作为关联容器的底部实现机制，具有以下性质
> 1. 每个节点不是红色就是黑色
> 2. 根节点为黑色
> 3. 如果某一节点为红色，其子节点必须为黑色，也就是父子节点不能同时为红色【新增节点之父节点必须为黑】
> 4. 任一节点到树的尾端（NULL，也被视为黑节点）的任何路径，所含的黑节点树必须相同【该条款决定插入的新节点必须为红色】

* 对于二叉搜索树而言其极值是很容易找到的，分别位于最左和最右
```c++
static base_ptr minnum(base_ptr pt){
	while(pt->left != nullptr)
		pt = pt -> left;
	return pt;
}

static base_ptr maxnum(base_ptr pt){
	while(pt->right != nullptr)
		pt = pt -> right;
	return pt;
}
```
**1.3 RB-tree的元素操作**
* 有两种插入操作，insert_unique()和insert_equal()，前者表示不允许插入重复的值，后者可以，插入之后需要对树进行平衡操作，即调用__rb_tree_rebalance()

**2. set**
* set是一个键和值相同的关联容器，会根据键值自动排序（由于底层是红黑树为平衡二叉搜索树），不允许重复的键值存在
* **set集合的迭代器为const_iterator，禁止对元素的值进行修改等操作**

```c++
template <typename Key, class Compare = less<Key>, class Alloc = alloc> //缺省采用递增排序
class set{
	...
};
```
* set 内部初始化实际调用的RB-tree的insert_unique()方法，实现键值的唯一，而multiset 才调用 insert_equal()

**3. map**

* map的特性是所有的元素会根据键值自动排序，map内部的键值对实际是一个pair对象，定义于<stl_pair.h>中
```c++
template <typename T1, typename T2>
struct pair{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	pair() : first(T1()), second(T2()){}
	pair(const T1& a, const T2& b) : first(a), second(b){}
};
```
* **map集合的迭代器为const_iterator，禁止对元素的值进行修改等操作**
* map的其它性质和操作同set相似

**4. multiset/multimap**
* 和set/map基本没有区，只是底层RB-tree的插入调用的都是insert_equal()，即允许重复值插入

**5. hashtable**
* hashtable容易产生hash冲突（常用的hash是求模取余法），解决的方法如下：
> 1. 线性探测：指的是当array对应位置被占据时，就对array循环探测每一个位置，直到有一个空位就插入，这样的缺陷就是探测时间开销过大，查找也类似当经过hash函数算出的位置不是目标值时，也进行循环线性搜索直到，找到该值
> 2. 二次探测：指的是当hash计算出的位置已经被占用时，不再线性探测空位置，而是采用 \\(s+1^2, s+2^2, s+3^2 ... s+i^2\\)，进行空位的探测

> 拉链法：即当hash计算出的位置已经被占用时，在该位置创建一个链表，对数据进行串联起来形成单链表或双链表（若链表过长也可以生成红黑树，二叉树之类的）
