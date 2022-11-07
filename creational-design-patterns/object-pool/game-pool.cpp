#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <algorithm>

class Missile
{
    bool m_isVisible{true};

public:
    Missile()
    {
        std::cout << "++++ Missile created\n";
        // Expensive example of initialization
        int acc{};
        for (auto i{0}; i < 1000000000; ++i) {
            acc *= std::rand();
            acc /= std::rand();
        };
    }
    ~Missile() { std::cout << "Missile destroy\n"; }
    void setVisible(bool visible) { m_isVisible = visible; }
    bool isVisible() { return m_isVisible; }
    void update()
    {
        std::cout << "->";
        std::flush(std::cout);
    }
};

using ActorPtr = std::shared_ptr<Missile>;
std::vector<ActorPtr> actors{};

class ActorPool
{
    inline static std::vector<ActorPtr> m_actorPool{};
    ActorPool() = default;

public:
    static ActorPtr accquireObject()
    {
        for (auto &obj : m_actorPool) {
            if (!obj->isVisible()) {
                std::cout << "Returning an existing instance\n";
                obj->setVisible(true);
                return obj;
            }
        }
        std::cout << "Creating new instance\n";
        auto newObj{std::make_shared<Missile>()};
        m_actorPool.push_back(newObj);
        return newObj;
    }

    // Here is not required because we have the visibility flag
    static void releaseObject(const ActorPtr &missile)
    {
        for (auto &obj : m_actorPool) {
            if (obj == missile) {
                obj->setVisible(false);
            }
        }
    }
};

void fire()
{
    actors.push_back(ActorPool::accquireObject());
    actors.push_back(ActorPool::accquireObject());
}

void animate()
{
    std::for_each(actors.begin(), actors.end(), [](auto &missile) { missile->update(); });
}

void explode()
{
    using namespace std;
    std::cout << "X\n";
    // Return instances to the pool with visibility flag!
    std::for_each(actors.begin(), actors.end(), [](auto &missile) { missile->setVisible(false); });
    actors.clear();
    std::this_thread::sleep_for(1s);
    std::cout << "\n\n";
}

void gameLoop()
{
    using namespace std;
    int counter{};
    while (true) {
        ++counter;
        if (counter == 1) {
            fire();
        } else if (counter >= 1 && counter <= 5) {
            animate();
        } else if (counter > 5) {
            explode();
            counter = 0;
        }
        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    gameLoop();
    return 0;
}
