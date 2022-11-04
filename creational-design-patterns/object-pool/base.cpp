#include <iostream>
#include <vector>
#include <algorithm>

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
    ObjectPool() = default;
    inline static std::vector<SharedObject *> m_pooledObjects{};

public:
    static SharedObject *acquireObject()
    {
        const auto it = std::find_if(
            m_pooledObjects.begin(), m_pooledObjects.end(), [](SharedObject *object) { return !object->isUsed(); });
        if (it != m_pooledObjects.end()) {
            (*it)->setUsed(true);
            (*it)->reset();
            return *it;
        } else {
            std::cout << "Creating new instance\n";
            auto newObject = new SharedObject{};
            m_pooledObjects.push_back(newObject);
            return newObject;
        }
    }

    static void releaseObject(SharedObject *object) { object->setUsed(false); }
};

int main()
{
    auto obj{ObjectPool::acquireObject()};
    obj->methodA();
    obj->methodB();
    ObjectPool::releaseObject(obj);
    auto obj1{ObjectPool::acquireObject()};
    obj1->methodA();
    auto obj2{ObjectPool::acquireObject()};
    obj2->methodA();

    return 0;
}
