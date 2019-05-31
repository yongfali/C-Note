## Effective C++ (第3版)学习笔记

## 说明： 本书主要是为了如何高效的运用C++，并编写属于自己的项目，使其具有易管理、可移植、可扩充等特征。
## 第一章：自己习惯C++

### 条款01：视C++为一个语言联邦
* C++ 可以理解为由以下四部分组成
> 1. C语言
> 2. object-orientend C++ (面向对象编程)
> 3. Templete C++ (泛化编程、模板编程 GP)
> 4. STL(标准库，是一个Templete模板库)

### 条款02：尽量以const, enum, inline替换#define
* 在一个头文件申明一个常量指针时，尽量包含两部分的限定
> 例： const char * const_name = value;
* enum和#define定义的量不能进行取址操作
*#define 定义的量没有作用域的范围，只是对其进行简单的字符替换操作，因此不能用于域范围限定量的设置
*inline函数与编译器内联起来，当函数调用的时候可以不用跳转到定义的地方，而是在编译阶段进行复制替换，可以加快运行效率，但会增大空间开销

### 条款03：尽可能使用const
*const指向哪里，其限定的就是哪（const 可以作用于域内的对象，函数参数，函数返回类型，成员函数本体），比如以下四个例子：
> 1. const char * p = value || char const * p = value; // non-const pointer, const data 
> 2. char * const p = value; // const pointer, non-const data
> 3. const char * const p = value; // const pointer, const data
> 4. char * p = value; // non-const pointer, non-const data 

### 条款04：确定对象被使用前已被初始化
* 对象未被初始化，则有可能出现在不同编译环境下出现不同的结果，或不可预期的错误
* 对象初始化和对象赋值不是同一个概念，构造函数体内的操作是赋值，而用initialization list 则是初始化操作
* 对象初始化的效率要比独享赋值的效率高，因为赋值一般会创建一个临时对象，进行拷贝，然后销毁临时对象
* 为免除跨编译单元之初始化问题，一般用local static 对象替换non-local static对象

## 第二章： 构造，析构，赋值

### 条款05 了解C++默认编写并调用哪些函数
* 对于任何一个类都有一个默认的构造函数、析构函数、拷贝构造函数和赋值重载函数，由编译器提供
* 如果不希望编译器生成默认的构造函数或赋值重载函数则可以自定义重载或者显示申明"=delete"
> 1. class_name(const class_name & obj) = delete
> 2. class_name operator=(const class_nam & obj) = delete

### 条款06：若不想使用编译器自动生成的函数，就该明确拒绝
* 可以将默认生成的函数在private中进行声明，并且不提供具体的实现便可以阻止

### 条款07： 为多态基类声明virtual析构函数
* 多态性质的基类应该声明一个带有virtual的析构函数，如果该类不是用来做多态基类，则不声明virtual析构函数，因为声明一个virtua会增加一个指针大小的空间开销，会对应一个指向虚基表（vpt)的指针、
* <strong> 虚基表继承的实例见：virtual_function.cpp</sstrong>

### 条款08 别让异常逃离析构函数
* 如果一个被析构函数调用的函数排除异常，析构函数应该捕捉任何异常，然后吞下他们或结束程序
* 如果需要对操作函数运行期抛出的异常做出反应，那么class应该提供一个普通函数（而非在析构函数中）执行该操作

### 条款09：绝不在构造和析构过程中调用virtual函数
* 

### 条款10，11：令operator= 返回一个reference to *this，处理“自我赋值”
* 返回引用主要是为了能够进行连续赋值(a=b=c)，同时还能避免一次拷贝，提高效率（a=b)，下面给出了赋值重载的基本代码框架
* 对于函数若值返回，则会执行一次拷贝，产生一个值的副本给赋值的对象，而该副本是右值，所以在再次赋值时由于不能取址而出错
```c++

class widget{
public:
	...
	Widget & operator=(const Widget & rhs){
		if(rhs == *this) // 检测rhs和当前赋值对象是否是同一个，实现自我赋值
			return *this;
		...
		return *this;
	}
	...
};

```

### 条款12：复制对象时勿忘其每一个成分
* 若自己重载了默认的考诶构造函数和赋值运算符，那么需要对数据的每一部分进行复制，在继承时也一样，因为自己定以后会屏蔽掉默认的方法，编译器对于这种业务逻辑的错误，不会报错

## 第三章：资源管理

### 条款13、14、15：资源管理
* 资源的获取在构造函数中完成，释放在析构函数中完成
* 直接把申请资源的对象放到对象中管理，能有效防止内存泄漏的风险，如使用智能指针

### 条款16：成对使用new和delete时要采用相同的形式
* new 动态申请内存，是通过重载operator new函数，然后调用的malloc()函数
* delete 释放内存，也是通过重载 operator delete函数，然后底层通过调用free()函数
* new 和 delete 搭配， new[] 和 delete[]搭配使用

### 条款17：以独立语句将newed对象置入智能指针
* 以独立语句将newed对象存储于智能指针内，如果不这样做，一旦异常抛出，有可能导致难以察觉的资源泄漏问题

## 第四章：设计与声明

### 条款20：宁以pass-by-reference-to-const 替换 pass-by-value
* 值传递会导致副本的产生，导致多次调用拷贝构造函数和析构函数，从而增大时间可空间成本
```c++
class Person{
public:
	Person();
	virtual ~Person();
	...
private:
	string name;
	string address;
};

class Student : public Person{
public:
	Student();
	~Student();
private:
	sting schoolName;
	string schoolAddress;	
};
bool validateStudent(Student s); //函数以值传递的方式接受一个学生对象
Student plato;
bool platoIsOK = validateStudent(plato);//该调用一共会调用6次构造函数和6次析构函数
//student 构造函数一次，Student 两个string对象各一次拷贝构造，然后分别各对应一次析构函数
//Student继承了Person，Person构造一次，和其两个string对象各一次拷贝构造，然后分别各一次析构
```
* 若上述代码改为传递引用则没有任何的构造函数和析构函数被调用
```c++
bool validataStudent(const Student & s); // pass-by-references
```
* pass-by-value也并不是一无是处，语言本身内置的类型和STL容器的迭代器和函数对象，一般采用值传递因为引用传递的本质还是指针的传递，而底层的实现对值的处理要比指针的处理效率更高

### 条款21：当必须返回对象时，不要试图返回他的引用
* 引用实际上是现有某一个对象的别名
* 并不是所有的返回值都是引用才好，有时根据实际需要返回值才是必须的，虽然会牺牲一些时间和空间成本但也是值得的，相比于获得错误的结果要好
* 绝不要返回pointer或reference指向一个local stack对象或返回reference指向一个head-allocated对象，或返回pointer或reference指向一个local static对象而有可能同时需要多个这样的对象。

### 条款22：将成员变量声明为private
* 该操作将赋予客户访问数据的一致性、课细微划分访问空中、允诺约束条件获得保证，并提供class实现者更充分的弹性
* protected 并不比public更具有封装性

### 条款23、24：宁以non-member、non-friend替换member函数
* 面向对象指的是对数据的封装性，并不是基于方法的封装性，有时非成员函数比成员函数的所带来的封装性更好
* 对于封装，越多的东西被封装，就可以留给开发人员更多的操作空间，而给客户带来更低的影响
* friend函数对class private成员的访问权利和member函数相同，因此两者的封装性差不多

### 条款25：考虑写出一个不抛出异常的swap函数
*  

