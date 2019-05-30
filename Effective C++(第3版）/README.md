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
* 


