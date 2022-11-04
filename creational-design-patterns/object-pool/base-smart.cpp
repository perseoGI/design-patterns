#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class SharedObject
{
    bool m_isUsed{true};

public:
    void methodA() { std::cout << __func__ << std::endl; }
    void methodB() { std::cout << __func__ << std::endl; }
    void reset() {}
    void setUsed(bool use) { m_isUsed = use; }
    bool isUsed() { return m_isUsed; }
};

class ObjectPool
{
    using ObjectPoolPtr = std::unique_ptr<SharedObject>;
    ObjectPool() = default;
    inline static std::vector<ObjectPoolPtr> m_pooledObjects{};

public:
    static ObjectPoolPtr acquireObject()
    {
        for (auto &ptr : m_pooledObjects) {
            if (!ptr->isUsed()) {
                ptr->setUsed(true);
                ptr.reset();
                return std::move(ptr);
            }
        }
        std::cout << "Creating new instance\n";
        auto newObject{std::make_unique<SharedObject>()};
        m_pooledObjects.push_back(std::move(newObject));
        return std::move(newObject);
    }

    // TODO fix bug
    static void releaseObject(SharedObject *ptr) { ptr->setUsed(false); }
};

int main()
{
    auto obj{ObjectPool::acquireObject()};
    obj->methodA();
    obj->methodB();
    ObjectPool::releaseObject(obj.get());
    // auto obj1{ObjectPool::acquireObject()};
    // obj1->methodA();
    // auto obj2{ObjectPool::acquireObject()};
    // obj2->methodA();

    return 0;
}
