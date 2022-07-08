#include "Singleton.hpp"
#include <string>
#include <iostream>

class A
{
public:
    A() : m_name("unknown")
    {
        std::cout << "A constructor" << std::endl;
    }

    A(const std::string& name)
        : m_name(std::move(name))
    {
        std::cout << "A constructor, name: " << m_name << std::endl;
    }

    ~A()
    {
        std::cout << "A desctructor" << std::endl;
    }

    const std::string& get_name() const
    {
        return m_name;
    }

    void set_name(std::string name)
    {
        m_name = std::move(name);
    }

private:
    std::string m_name;
};

struct B
{
    int value = 0;
};

void test_singleton()
{
    A* a1 = Singleton<A>::Instance();
    A* a = Singleton<A>::Instance("hello");
    std::cout << "a name: " << a->get_name() << std::endl;

    A* b = Singleton<A>::GetInstance();
    std::cout << "b name: " << b->get_name() << std::endl;

    Singleton<A>::DestroyInstance();

    Singleton<B>::Instance();
}


int main()
{
    test_singleton();
    return 0;
}
