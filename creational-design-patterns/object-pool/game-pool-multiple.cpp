#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Actor
{
    bool m_isVisible{true};

public:
    void setVisible(bool visible) { m_isVisible = visible; }
    bool isVisible() { return m_isVisible; }
    virtual void update() = 0;
    virtual ~Actor() = default;
};

class Alien : public Actor
{
public:
    Alien() { std::cout << "++++ Alien created\n"; }
    ~Alien() { std::cout << "~~~~ Alien destroyed\n"; }
    void update() { std::cout << "@ "; }
};

class Missile : public Actor
{
public:
    Missile() { std::cout << "++++ Missile created\n"; }
    ~Missile() { std::cout << "~~~~ Missile destroyed\n"; }
    void update()
    {
        std::cout << "->";
        std::flush(std::cout);
    }
};

using ActorPtr = std::shared_ptr<Actor>;

class ActorPool
{
    inline static std::unordered_map<std::string, std::vector<ActorPtr>> m_actorPool{};
    ActorPool() = default;

    // Bad design: invalidates Open-Close principle
    static ActorPtr internalCreate(const std::string &key)
    {
        std::cout << "Creating new instance of type " << key << '\n';
        if (key == "missile")
            return std::make_shared<Missile>();
        if (key == "alien")
            return std::make_shared<Alien>();
        return nullptr;
    }

public:
    static ActorPtr accquireActor(const std::string &key)
    {
        if (m_actorPool.count(key) > 0) {
            for (auto &obj : m_actorPool[key]) {
                if (!obj->isVisible()) {
                    std::cout << "Returning an existing instance of " << key << '\n';
                    obj->setVisible(true);
                    return obj;
                }
            }
        }
        auto newObj{internalCreate(key)};
        m_actorPool[key].push_back(newObj);
        return newObj;
    }

    // Here is not required because we have the visibility flag
    static void releaseActor(const std::string &key, const ActorPtr &missile)
    {
        for (auto &obj : m_actorPool[key]) {
            if (obj == missile) {
                obj->setVisible(false);
                return;
            }
        }
    }
};

std::vector<ActorPtr> actors{};

void fire()
{
    actors.push_back(ActorPool::accquireActor("missile"));
    actors.push_back(ActorPool::accquireActor("alien"));
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
    auto loop{2};
    while (loop > 0) {
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
        --loop;
    }
}

int main()
{
    gameLoop();
    return 0;
}
