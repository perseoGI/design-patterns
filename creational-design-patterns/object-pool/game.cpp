#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <algorithm>

class Missile
{
    bool m_isVisible{false};

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

using MissilePtr = std::shared_ptr<Missile>;
std::vector<MissilePtr> missiles{};

void fire()
{
    missiles.push_back(std::make_shared<Missile>());
    missiles.push_back(std::make_shared<Missile>());
}

void animate()
{
    std::for_each(missiles.begin(), missiles.end(), [](auto &missile) { missile->update(); });
}

void explode()
{
    using namespace std;
    std::cout << "X\n";
    std::for_each(missiles.begin(), missiles.end(), [](auto &missile) { missile->setVisible(false); });
    missiles.clear();
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
