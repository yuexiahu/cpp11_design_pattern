#include "ObjectPool.hpp"
#include <iostream>

struct BigObject
{
    BigObject()
    {
    }

    BigObject(int a)
        : m_a(a)
    {
    }

    BigObject(const int& a, const int& b)
        : m_a(a)
        , m_b(b)
    {
    }

    void Print(const std::string& str)
    {
        std::cout << str << " a: " << m_a << ", b: " << m_b << std::endl;
    }

    int m_a = 0;
    int m_b = 0;
};

void Print(std::shared_ptr<BigObject> p, const std::string& str)
{
    if (p != nullptr)
    {
        p->Print(str);
    }
}

void test_object_pool()
{
    ObjectPool<BigObject> pool;
    pool.Init(2);

    {
        auto p = pool.Get();
        Print(p, "p");

        auto p2 = pool.Get();
        Print(p2, "p2");
    }
    // 除了作用域后，对象池返回出来的对象又会自动回收

    auto p = pool.Get();
    auto p2 = pool.Get();
    Print(p, "p");
    Print(p2, "p2");

    // 对象池支持重载构造函数
    pool.Init(2, 1);
    auto p4 = pool.Get<int>();
    Print(p4, "p4");
    pool.Init(2, 1, 2);
    auto p5 = pool.Get<int, int>();
    Print(p5, "p5");
}

int main()
{
    test_object_pool();
    return 0;
}