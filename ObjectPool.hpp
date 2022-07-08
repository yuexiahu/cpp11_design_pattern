#pragma once

#include <string>
#include <stdexcept>
#include <functional>
#include <memory>
#include <map>
#include "NonCopyable.hpp"

template <typename T>
class ObjectPool : NonCopyable
{
    template <typename... Args>
    using Constructor = std::function<std::shared_ptr<T>(Args...)>;

public:
    ~ObjectPool()
    {
        m_cleaning = true;
    }

    // 默认创建多少个对象
    template <typename... Args>
    void Init(size_t num, Args&&... args)
    {
        if (num == 0)
            throw std::logic_error("object num out of range.");

        std::string constructName = typeid(Constructor<Args...>).name(); // 不区分引用
        for (size_t i = 0; i < num; i++)
        {
            m_object_map.emplace(constructName,
                                 std::shared_ptr<T>(new T(std::forward<Args>(args)...), [this, constructName](T* p) {
                                     // 删除器中不直接删除对象，而是回收到对象池中，以供下次使用
                                     if (!m_cleaning)
                                     {
                                         m_object_map.emplace(constructName, std::shared_ptr<T>(p));
                                     }
                                 }));
        }
    }

    // 从对象池中获取一个对象
    template <typename... Args>
    std::shared_ptr<T> Get()
    {
        std::string constructName = typeid(Constructor<Args...>).name();

        auto range = m_object_map.equal_range(constructName);
        for (auto it = range.first; it != range.second; ++it)
        {
            // 找到一个对象弹出
            auto ptr = it->second;
            m_object_map.erase(it);
            return ptr;
        }

        return nullptr;
    }

private:
    std::multimap<std::string, std::shared_ptr<T>> m_object_map;
    bool m_cleaning = false;
};
