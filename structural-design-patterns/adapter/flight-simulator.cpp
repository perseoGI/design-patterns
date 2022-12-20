#include <iostream>
#include <random>
#include <thread>

class Input
{
public:
    virtual bool up() = 0;
    virtual bool down() = 0;
    virtual bool right() = 0;
    virtual bool left() = 0;
    virtual ~Input() = default;
};

class Keyboard : public Input
{
    std::default_random_engine m_engine{1234};
    bool simulateInput()
    {
        std::bernoulli_distribution dist{.5};
        return dist(m_engine);
    }

public:
    bool up() override { return simulateInput(); }
    bool down() override { return simulateInput(); }
    bool right() override { return simulateInput(); }
    bool left() override { return simulateInput(); }
};

void game(Input *pInput)
{
    int count{5};
    while (count != 0) {
        std::cout << "=================\n";
        if (pInput->up()) {
            std::cout << "Pitch up\n";
        } else if (pInput->down()) {
            std::cout << "Pitch down\n";
        } else {
            std::cout << "Plane leveled\n";
        }
        if (pInput->right()) {
            std::cout << "Turning right\n";
        } else if (pInput->left()) {
            std::cout << "Turning left\n";
        } else {
            std::cout << "Flying straight\n";
        }
        using namespace std;
        std::this_thread::sleep_for(1s);
        --count;
    }
}

// This is not ours
// Has different interface the game expects
class Accelerometer
{
    std::default_random_engine m_engine{1234};

public:
    double getHorizontalAxis()
    {
        std::uniform_int_distribution<> dist{-10, 10};
        auto value{dist(m_engine)};
        std::cout << "[Horizontal]: " << value << '\n';
        return value;
    }
    double getVerticalAxis()
    {
        std::uniform_int_distribution<> dist{-10, 10};
        auto value{dist(m_engine)};
        std::cout << "[Vertical]: " << value << '\n';
        return value;
    }
};

// Create an ObjectAdapter
class AccelerometerObjectAdapter : public Input
{
    Accelerometer m_accelerometer;

public:
    bool up() override { return m_accelerometer.getVerticalAxis() > 0; }
    bool down() override { return m_accelerometer.getVerticalAxis() < 0; }
    bool right() override { return m_accelerometer.getHorizontalAxis() > 0; }
    bool left() override { return m_accelerometer.getVerticalAxis() < 0; }
};

// This class make more sense to adapt it via class adapter
class OtherAccelerometer
{
    std::default_random_engine m_engine{1234};

public:
    double getHorizontalAxis()
    {
        auto limits{initialize()};
        std::uniform_int_distribution<> dist{limits.first, limits.second};
        auto value{dist(m_engine)};
        std::cout << "[Horizontal]: " << value << '\n';
        return value;
    }
    double getVerticalAxis()
    {
        auto limits{initialize()};
        std::uniform_int_distribution<> dist{limits.first, limits.second};
        auto value{dist(m_engine)};
        std::cout << "[Vertical]: " << value << '\n';
        return value;
    }
    virtual std::pair<int, int> initialize() { return {-10, 10}; }
};

class AccelerometerClassAdapter : public Input, public OtherAccelerometer
{
public:
    bool up() override { return getVerticalAxis() > 0; }
    bool down() override { return getVerticalAxis() < 0; }
    bool right() override { return getHorizontalAxis() > 0; }
    bool left() override { return getVerticalAxis() < 0; }
    std::pair<int, int> initialize() override { return {-1, 1}; }
};

int main()
{
    // Keyboard k;
    // game(&k);

    // AccelerometerObjectAdapter acc;
    AccelerometerClassAdapter acc;
    game(&acc);
}
