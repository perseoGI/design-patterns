#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <mutex>

template <typename T>
class DefaultAllocator
{
public:
    T *operator()() { return new T{}; }
    void operator()(T *p) { delete p; }
    void reset() {}
};

class NoLock
{
public:
    virtual void lock() {}
    virtual void unlock() {}
};

class MutexLock : public NoLock
{
    std::mutex m_mutex{};

public:
    void lock() override { m_mutex.lock(); }
    void unlock() override { m_mutex.unlock(); }
};

// Strategy pattern
template <typename T,
          size_t max_size = std::numeric_limits<size_t>::max(),
          typename Lock = NoLock,  // Allow passing custom lock object: no lock by default
          typename AllocatorT = DefaultAllocator<T>>
class ObjectPool
{
    struct ObjectInfo {
        bool m_isUsed{};
        T *m_pObject{};
    };
    inline static std::vector<ObjectInfo> m_pooledObjects{};
    inline static AllocatorT m_allocator{};
    inline static Lock m_lock{};

public:
    static T *aquire()
    {
        m_lock.lock();
        for (auto &obj : m_pooledObjects) {
            if (!obj.m_isUsed) {
                std::cout << "[POOL] returning existing object\n";
                obj.m_isUsed = true;
                return obj.m_pObject;
            }
        }
        if (m_pooledObjects.size() == max_size) {
            throw std::runtime_error("Reached pool max size of " + std::to_string(max_size));
        }
        std::cout << "[POOL] creating new object\n";
        auto pObj{m_allocator()};
        m_pooledObjects.push_back({true, pObj});
        m_lock.unlock();
        return pObj;
    }

    static void release(T *object)
    {
        m_lock.lock();
        for (auto &obj : m_pooledObjects) {
            if (obj.m_pObject == object) {
                obj.m_isUsed = false;
            }
        }
        m_lock.unlock();
    }

    static void clear()
    {
        m_lock.lock();
        for (auto &obj : m_pooledObjects) {
            if (obj.m_isUsed)
                std::cout << "[WARNING]: deleting object still in use\n";
            m_allocator(obj.m_pObject);
        }
        m_allocator.reset();
        m_pooledObjects.clear();
        m_lock.unlock();
    }
};

class Test
{
    Test() {}

public:
    void foo(){};

    friend class TestAllocator;
};

class TestAllocator
{
public:
    Test *operator()() { return new Test{}; }
    void operator()(Test *p) { delete p; }
    void reset() {}
};

int main()
{
    using IntPool = ObjectPool<int>;
    auto p1{IntPool::aquire()};
    auto p2{IntPool::aquire()};
    auto p3{IntPool::aquire()};
    IntPool::release(p1);
    auto p4{IntPool::aquire()};
    IntPool::clear();

    using TestPool = ObjectPool<Test, 2, MutexLock, TestAllocator>;  // will not compile because using new on private
                                                                     // constructor is invalid
    auto t1{TestPool::aquire()};
    auto t2{TestPool::aquire()};
    // auto t3{TestPool::aquire()};     // this will fail due to pool limit

    return 0;
}
