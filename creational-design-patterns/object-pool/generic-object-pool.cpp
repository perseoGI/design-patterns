#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

template <typename T>
class ObjectPool
{
    struct ObjectInfo {
        bool m_isUsed{};
        T *m_pObject{};
    };
    inline static std::vector<ObjectInfo> m_pooledObjects{};

public:
    [[nodiscard("Object will remain unused")]] static T *aquire()
    {
        for (auto &obj : m_pooledObjects) {
            if (!obj.m_isUsed) {
                std::cout << "[POOL] returning existing object\n";
                obj.m_isUsed = true;
                return obj.m_pObject;
            }
        }
        std::cout << "[POOL] creating new object\n";
        auto pObj{new T{}};
        m_pooledObjects.push_back({true, pObj});
        return pObj;
    }

    static void release(T *object)
    {
        for (auto &obj : m_pooledObjects) {
            if (obj.m_pObject == object) {
                obj.m_isUsed = false;
            }
        }
    }

    static void clear()
    {
        for (auto &obj : m_pooledObjects) {
            if (obj.m_isUsed)
                std::cout << "[WARNING]: deleting object still in use\n";
            delete obj.m_pObject;
        }
        m_pooledObjects.clear();
    }
};

class Test
{
    Test() {}

public:
    void foo(){};
};

int main()
{
    using IntPool = ObjectPool<int>;
    // using TestPool = ObjectPool<Test>;  // will not compile because using new on private constructor is invalid
    auto p1{IntPool::aquire()};
    auto p2{IntPool::aquire()};
    auto p3{IntPool::aquire()};
    IntPool::release(p1);
    auto p4{IntPool::aquire()};
    IntPool::clear();
    return 0;
}
