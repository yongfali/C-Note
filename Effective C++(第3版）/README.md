## Effective C++ (第3版)学习笔记

## 说明： 本书主要是为了如何高效的运用C++，并编写属于自己的项目，使其具有易管理、可移植、可扩充等特征。
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

### 条款13：以对象管理资源
* 
