#pragma once

//前向声明
template <typename... Types>
struct Visitor;

//通过递归继承创建每个类型的Visit虚函数
template <typename T, typename... Types>
struct Visitor<T, Types...> : Visitor<Types...>
{
    using Visitor<Types...>::Visit; //通过using避免隐藏基类的visit同名方法
    virtual void Visit(const T&) = 0;
};

//递归终止条件
template <typename T>
struct Visitor<T>
{
    virtual void Visit(const T&) = 0;
};
