#include "Command.hpp"
#include <iostream>
#include <queue>

// 命令模式的作用是将请求封装为一个对象，将请求的发起者和执行者解耦，支持对请求排队以及撤销和重做。
//
//
// 由于将请求都封装成一个个命令对象了，使得我们可以集中处理或者延迟处理这些命令请求，
// 而且不同的客户对象可以共享这些命令， 还可以控制请求的优先级、排队、支持请求命令撤销和重做等等。
// 命令模式的这些好处是显而易见的，但是，在实际使用过程中它的问题也暴露出来了。随着请求的增多，
// 请求的封装类--命令类也会越来越多，尤其是GUI应用中，请求是非常多的。越来越多的命令类会导致类爆炸，难以管理。

struct CalcFunctor
{
    int operator()() const
    {
        return 0;
    };

    int operator()(int a) const
    {
        return a;
    };

    int operator()(int a, int b) const
    {
        return a + b;
    };
};

struct CalcClass
{
    int do_sum(int a, int b)
    {
        return a + b;
    }

    int do_multiply(int a, int b)
    {
        return a * b;
    }
};

int calc(int a, int b)
{
    return a + b;
}

int calc_with_callback(int a, const std::function<int(int)>& cb)
{
    return cb(a);
}

void test_command()
{
    using LazyTask = CommCommand<int>;

    std::queue<LazyTask> m_lazy_queue;

    LazyTask task;

    // 自由函数
    task.Wrap(calc, 0, 10);
    m_lazy_queue.push(task);

    task.Wrap(calc_with_callback, 10, [](int a) {
        std::cout << "calc callback " << a << std::endl;
        return a * 10;
    });
    m_lazy_queue.push(task);

    // lambda
    task.Wrap([] {
        return 0;
    });
    m_lazy_queue.push(task);

    task.Wrap(
        [](int a) {
            return a;
        },
        10);
    m_lazy_queue.push(task);

    task.Wrap(
        [](int a, int b) {
            return a + b;
        },
        20, 30);
    m_lazy_queue.push(task);

    int a = 5;
    task.Wrap(
        [&a](int b) {
            std::cout << "a: " << a << ", b: " << b << std::endl;
            return a + b;
        },
        20);
    m_lazy_queue.push(task);

    // 函数对象
    CalcFunctor functor;
    task.Wrap(functor);
    m_lazy_queue.push(task);

    task.Wrap(functor, 10);
    m_lazy_queue.push(task);

    task.Wrap(CalcFunctor(), 10, 20);
    m_lazy_queue.push(task);

    // 成员函数
    CalcClass calc_obj;
    task.Wrap(&CalcClass::do_sum, &calc_obj, 10, 20);
    m_lazy_queue.push(task);

    task.Wrap(&CalcClass::do_multiply, &calc_obj, 10, 20);
    m_lazy_queue.push(task);

    int sum = 0;
    while (!m_lazy_queue.empty())
    {
        sum += m_lazy_queue.front().Execute();
        m_lazy_queue.pop();
    }
    std::cout << "sum result: " << sum << std::endl;
}

int main()
{
    test_command();
    return 0;
}
