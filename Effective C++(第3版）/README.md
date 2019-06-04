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

## 第五章：实现

### 条款26：尽可能延后变量定义式的出现时间
* 因为当一个变量没有完全被使用的时候延迟定义就有可能避免不必要的构造和析构所带来的开销
```c++
//example 01 变量定义于循环体外
Widget w;
for(int i = 0; i < n; ++i){
	w = 取决于i的某一个值;
	...
}

//example 02 变量定义于循环体内
for(int i = 0; i < n; ++i){
	Widget w;
	w = 取决于i的某一个值;
	...
}
// example 01 执行构造、析构和赋值各1次；
// example 02 执行构造、析构各n次
//虽然前者效率稍高，但更倾向于用后者，除非当n足够大或者明知前者效率要远高于后者
```
### 条款27：尽量少做转型动作,若不可避免应当使用下面的新式风格进行转化
* 传统类型的转换
> 1. C风格的转换：(int) a;
> 2. 函数式风格的转换：int(a)

* C++定义了四种新的显示类型风格的转换
> 1. static_cast<T>(expression) // 很像 C 语言中的旧式类型转换。它能进行基础类型之间的转换，也能将带有可被单参调用的构造函数或用户自定义类型转换操作符的类型转换，还能在存有继承关系的类之间进行转换（即可将基类转换为子类，也可将子类转换为基类），还能将 non-const对象转换为 const对象（注意：反之则不行，那是const_cast的职责）
```c++
double d = 3.14159265;
int i = static_cast<int>(d);
class A {};
class B
{
	public:
	B (A a) {};
}; 
A a;
B b = static_cast<B>(a);

class CBase {};
class CDerived: public CBase {};
CBase * a = new CBase;
CDerived * b = static_cast<CDerived *>(a);
```
> 2. dynamic_cast<T>(expression) // dynamic_cast 主要用来在继承体系中的安全向下转型。它能安全地将指向基类的指针转型为指向子类的指针或引用，并获知转型动作成功是否。如果转型失败会返回null（转型对象为指针时）或抛出异常（转型对象为引用时）。dynamic_cast 会动用运行时信息（RTTI）来进行类型安全检查，因此 dynamic_cast 存在一定的效率损失。（我曾见过属于优化代码80/20法则中的20那一部分的一段游戏代码，起初使用的是 dynamic_cast，后来被换成 static_cast 以提升效率，当然这仅是权宜之策，并非好的设计）
```c++
class CBase { };
class CDerived: public CBase { };
CBase b;
CBase* pb;
CDerived d;
CDerived* pd;
pb = dynamic_cast<CBase*>(&d);     // ok: derived-to-base
pd = dynamic_cast<CDerived*>(&b);  // error: base-to-derived
```
> 3. const_cast<T>(expression) // const_cast 可去除对象的常量性（const），它还可以去除对象的易变性（volatile）。const_cast 的唯一职责就在于此，若将 const_cast 用于其他转型将会报错
```c++
void print (char * str)
{
	cout << str << endl;
}
int main ()
{
	const char * c = " http://www.cppblog.com/kesalin/";
	print ( const_cast<char *> (c) );
	return 0;
}
```
> 4. reinterpret<T>(expression) // reinterpret_cast 用来执行低级转型，如将执行一个 int 的指针强转为 int。其转换结果与编译平台息息相关，不具有可移植性，因此在一般的代码中不常见到它。reinterpret_cast 常用的一个用途是转换函数指针类型，即可以将一种类型的函数指针转换为另一种类型的函数指针，但这种转换可能会导致不正确的结果。总之，reinterpret_cast 只用于底层代码，一般我们都用不到它，如果你的代码中使用到这种转型，务必明白自己在干什么

* <strong>typeid</strong> 定义在标准头文件```<typeinfo>```中，用于获取表达式的类型，它返回一个数据类型或类名字的字符串。当 typeid 用于自定义类型时，它使用 RTTI 信息来获取对象的动态类型。基于 typeid，我们可以构建出比较对象（动态）类型的操作


### 条款28：避免返回handles指向对象内部部分
* 主要是为了防止破坏数据的封装性，帮助const成员函数的行为更像一个const

### 条款29：
* 带有异常安全的函数应该满足一下两个条件：
> 1. 不泄漏任何资源（可参见条款13资源的管理）
> 2. 不允许数据的破坏

* 这样的函数区分为三种可能的保障：基本类型，强烈型，不抛异常型
* 强烈保障，往往是以"copy and swap"来实现的

### 条款30：透彻了解inlining的里里外外
* inline 只是对编译器的一个申请，不是强制命令，可以显示声明，也可以隐式声明如在类中定义实现的函数可以看做是隐式的inline
* inline 的一个好处就是就在函数调用时不用来回跳转，而增大时间开销，但是过的依赖会导致空间开销的增大，因为它是对函数调用的一个本体的替换
* inline有点类似于宏定义#define，是发生在编译阶段的一个本体替换，但是比宏定义要安全
* inline 不该作用于virtual函数因为前者是在编译阶段就得完成本体的替换，明确调用的对象，而后者是动态编译过程，是需要在调用时才能明确调用的本体
* inline函数还有个缺点就是在代码调试阶段没法进行，因为在调试时往往不能针对一个没有函数本体的代码进行打断点操作
* inline 一般作用于小型，频繁调用的函数身上

### 条款31：将文件间的编译依存关系降到最低
* 主要是为了降低编译链接的次数，提升编译的效率使之松耦合

## 第六章：继承与面向对象设计

### 条款32：确定你的public继承模式是"is-a"关系
* public继承意味'is-a'，适用于base classes 身上的每一件事情也一定适用于derived classes身上，因为每一个derived class对象也都是一个base class对象

### 条款33：避免遮掩继承而来的名称
* 编译时多态一般是在某一个类内实行的，尽量避免派生类还去重载基类的函数这种做法不可取，但是对于虚函数或纯虚函数则需要重写以实现运行时多态，可以通过指向父类的指针或引用调用子类的方法

### 条款34、35：区分接口继承和实现继承
* 声明一个纯虚函数的目的是为了让派生类只继承函数的接口（子类必须实现父类的接口）
* 声明一个非纯虚函数的目的，是让派生类继承该函数的接口和缺省实现（子类可重写该实现也可不实现）
* 非虚函数具体制定接口继承以及强制性实现继承

### 条款36：绝不定义继承而来的non-virtual函数
* 一般不在子类去重载父类的non-virtual函数，因为它是静态绑定的，是在定义时就绑定到对应的类了，这样会导致语义理解出错
* 子类会继承父类的所有方法和要实现的接口，因此不建议去定义继承而来的non-virtual函数

### 条款37：绝不重新定义继承而来的缺省参数值
* 因为缺省的参数值都是静态绑定的，而virtual函数，重写则属于是动态绑定，因此重写时必须保持函数前后的一致性
* 如果想改变默认的缺省值，则可以通过将虚函数定义为private，然后通过public non-virtual 函数调用便可
```c++
class Shape{
public:
	enum ShapeColor {Red, Green, Blue};
	void draw(ShapeColor color = Red) const
	{
		doDraw(color);
	}
	...
private:
	virtual void doDraw(ShapeColor color) const = 0;
};

class Rectangle : public Shape{
public:
	...
private:
	virtual void doDram(ShapeColor color) const;
};
```
### 条款38：通过复合塑模出has-a
* 复合是类型之间的一种关系，当某种对象内含其它种类的类型对象，便是这种关系

### 条款39、40：明智而审慎地使用private继承和多重继承
* 多继承容易导致歧义的出现，当继承的多个父类有同名的方法时，容易导致子类的对象在调用该方法时出现歧义
* 解决多重继承体系歧义的方法
> 1. 明确指定其调用的方法属于哪一个类
> 2. 改为虚继承便可以实现运行时动态选择对应的方法
* 但是virtual继承会增加大小、速度、初始化（及赋值）复杂度等成本

## 第七章 模板与泛型编程

### 条款41：了解隐式接口和编译期多态
* 类和模板都支持接口和多态
* 对类而言接口是显式的，以函数签名为中心，多态则是通过virtual函数发生于运行期间
* 对template参数而言，接口是隐式的，奠基于有效表达式。多态则是通过template具现化和桉树重载解析发生于编译期

### 条款42：了解typename的双重意义
* 声明template参数时，前缀关键字class和typename可互换
* 请使用关键字typename标识嵌套从属类型名称；但不得在基类列或成员初始值内以它作为基类修饰符

### 条款43-48：暂时没细看

## 第八章 定制new和delete
### 条款49：了解new-handler的行为
* se_new_handler 允许客户指定一个函数，在内存分配无法获得满足时被调用
* Nothrow new 是一个颇为局侠的工具，因为他只适用于内存的分配；后继的构造函数调用还是可能抛出异常

### 条款50：了解new和delete的合理替换时机
* 一般情况下默认的operator new operator delete基本就够了但是有时为了改善性能、对heap运用错误进行调试、收集heap使用信息，便需要对其进行自定义以满足需求

### 条款51、52：编写new和delete时需要固守常规
* operator  new的返回值，当成功时返回的是一个指向申请成功的内存地址指针，失败则返回bad_alloc异常
* 这里的失败是建立在operator new多次尝试的基础上然后new-handing函数返回的是null指针时才抛出bad_alloc异常，因为内存申请每次失败后会调用new-handing函数，该函数将执行某些内存释放的动作用于新申请的内存要求
```c++
//operator new 伪代码
void* operator new(std::sizt_t size) throw(std::bad_alloc){
	using namespace std;
	if(size == 0){ //处理0-byte申请
		size = 1;  //将它视为1-byte申请
	}
	while(true){ // operator new 内含的无穷循环
		尝试分配size bytes;
		if(分配成功)
			return (指向分配成功内存区域的指针);

		//分配失败，找出目前的new-handing函数
		new_handler globalHandler = set_new_handler(0);
		set_new_handler(globalHandler);

		if(globalHandler) (*globalHandler)();
		else throw(std::bad_alloc());
	}
}

// opreator delete 声明
void operator delete(void * rawMemory) throw(); //global作用域中的正常签名式
void operator delete(void* rawMemory, std::size_t size) throw();//class作用域中典型的签名式
```
* Write palcement delete if you write palcement new

## 第九章 杂项讨论

### 条款53：不要轻易忽视编译器的警告
* 不要过分看重编译器的警告信息，也不可忽视警告信息，因为有些编译器警告是不同编译平台的原因，也有可能会造成致命的错误

### 条款54：让自己熟悉包括TR1在内的标准程序库
* C++98列入的C++标准库的主要成分有：
> 1. STL，覆盖容器，迭代器，算法，仿函数（函数对象），容器适配器，内存管理器
> 2. Iostreams，覆盖用户自定缓冲功能、国际化I/O，以及预定义的对象，cin、cout,cerr和clog
> 3. 国际化支持，包括多区域能力，像wchar_t和wstring（由wchar_ts组成的string）等类型都对促进Unicode有帮助
> 4. 数值处理，包括复数模板（complex）和纯数值数组（valarray)
> 5. 异常阶层体系，包括base class exception 及其derived classes logic_error和runtime_error，以及更深继承的各个classes

* TR1详细叙述了14个新组建，都放在了std命名空间内，更确切的说是放在了嵌套的命名空间tr1内
```c++
std::str1::shared_ptr //一般std::作用域可以省略不写
```
> 1. 智能指针
