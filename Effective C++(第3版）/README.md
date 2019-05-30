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