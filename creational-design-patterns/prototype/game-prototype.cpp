#include <iostream>
#include <string_view>
#include <thread>
#include <random>

class Animation
{
    std::string m_animationData{};

public:
    Animation() = default;
    Animation(std::string_view animFile)
    {
        using namespace std;
        std::cout << "[Animation Loading]: " << animFile;
        for (auto i{0}; i < 10; ++i) {
            std::cout << '.' << std::flush;
            std::this_thread::sleep_for(200ms);
        }
        std::cout << '\n';
        m_animationData.assign("^^^^^");
    }
    const std::string &getAnimationData() const { return m_animationData; }
    void setAnimationData(const std::string &animationData) { m_animationData = animationData; }
};

struct Position {
    int x;
    int y;
    friend std::ostream &operator<<(std::ostream &os, const Position &p)
    {
        return os << '(' << p.x << ',' << p.y << ')';
    }
};

class Vehicle
{
    int m_speed{};
    int m_hitPoints{};
    std::string m_name{};  // debug

    Animation *m_pAnimation{};
    Position m_position{};

public:
    Vehicle(int speed, int hitpoints, const std::string &name, std::string_view animFile, Position position)
        : m_speed(speed)
        , m_hitPoints(hitpoints)
        , m_name(name)
        , m_position(position)
    {
        m_pAnimation = new Animation{animFile};
    }

    int getSpeed() const { return m_speed; }
    int getHitPoints() const { return m_hitPoints; }
    const std::string &getName() const { return m_name; }
    const std::string &getAnimation() const { return m_pAnimation->getAnimationData(); }
    Position getPosition() const { return m_position; }

    void setSpeed(int speed) { m_speed = speed; }
    void setHitPoints(int hitpoints) { m_hitPoints = hitpoints; }
    void setName(const std::string &name) { m_name = name; }
    void setAnimationData(const std::string &animData) { m_pAnimation->setAnimationData(animData); }
    void setPosition(const Position &pos) { m_position = pos; }

    virtual void update() = 0;
    virtual Vehicle *clone() = 0;

    // Rule of five!
    // If any derived clases had a pointer (resource) this methods should be overridden
    virtual ~Vehicle() { delete m_pAnimation; }

    // Deep copy -> prevent segfault when double deleting a shallow copy
    Vehicle(const Vehicle &vehicle)
        : m_speed(vehicle.m_speed)
        , m_hitPoints(vehicle.m_hitPoints)
        , m_name(vehicle.m_name)
        , m_position(vehicle.m_position)
    {
        m_pAnimation = new Animation{};
        m_pAnimation->setAnimationData(vehicle.m_pAnimation->getAnimationData());
    }

    Vehicle &operator=(const Vehicle &other)
    {
        if (this != &other) {
            m_speed = other.m_speed;
            m_name = other.m_name;
            m_hitPoints = other.m_hitPoints;
            m_position = other.m_position;
            m_pAnimation->setAnimationData(other.getAnimation());
        }
        return *this;
    }

    Vehicle(const Vehicle &&vehicle)
        : m_speed(vehicle.m_speed)
        , m_hitPoints(vehicle.m_hitPoints)
        , m_name(vehicle.m_name)
        , m_position(vehicle.m_position)
    {
        m_pAnimation = new Animation{};
        m_pAnimation->setAnimationData(vehicle.m_pAnimation->getAnimationData());
    }

    Vehicle &operator=(Vehicle &&other) noexcept
    {
        if (this != &other) {
            m_speed = other.m_speed;
            m_name = std::move(other.m_name);
            m_hitPoints = other.m_hitPoints;
            m_position = other.m_position;
            delete m_pAnimation;
            m_pAnimation = other.m_pAnimation;

            other.m_speed = 0;
            other.m_name.clear();
            other.m_hitPoints = 0;
            other.m_position = {0, 0};
            other.m_pAnimation = nullptr;
        }
        return *this;
    }
};

class GreenCar : public Vehicle
{
    using Vehicle::Vehicle;

public:
    void update() override
    {
        std::cout << '[' << getName() << "]\n"
                  << "\tAnimation:" << getAnimation() << '\n'
                  << "\tSpeed:" << getSpeed() << '\n'
                  << "\tHitPoints:" << getHitPoints() << '\n'
                  << "\tPosition:" << getPosition() << '\n';
    }
    Vehicle *clone() override
    {
        std::cout << "[GreenCar] Cloning->" << getName() << std::endl;
        return new GreenCar{*this};  // COPY CONSTRUCTOR CALLED!
    }
};

class RedCar : public Vehicle
{
    using Vehicle::Vehicle;
    float m_speedFactor{1.5f};
    std::default_random_engine m_engine{100};
    std::bernoulli_distribution m_dist{.5};

public:
    void setSpeedFactor(float f) { m_speedFactor = f; }

    void update() override
    {
        std::cout << '[' << getName() << "]\n"
                  << "\tAnimation:" << getAnimation() << '\n';
        if (m_dist(m_engine))
            std::cout << "\tIncrease speed temporarily: " << getSpeed() * m_speedFactor << '\n';
        else
            std::cout << "\tSpeed:" << getSpeed() << '\n';

        std::cout << "\tHitPoints:" << getHitPoints() << '\n' << "\tPosition:" << getPosition() << '\n';
    }

    Vehicle *clone() override
    {
        std::cout << "[RedCar] Cloning->" << getName() << std::endl;
        return new RedCar{*this};  // COPY CONSTRUCTOR CALLED!
    }
};

class BlueBus : public Vehicle
{
    using Vehicle::Vehicle;
    std::default_random_engine m_engine{100};
    std::bernoulli_distribution m_dist{.5};

public:
    void update() override
    {
        std::cout << '[' << getName() << "]\n"
                  << "\tAnimation:" << getAnimation() << '\n';
        if (m_dist(m_engine))
            std::cout << "\tMoving out of the way\n";
        std::cout << "\tSpeed:" << getSpeed() << '\n'
                  << "\tHitPoints:" << getHitPoints() << '\n'
                  << "\tPosition:" << getPosition() << '\n';
    }

    Vehicle *clone() override
    {
        std::cout << "[BlueBus] Cloning->" << getName() << std::endl;
        return new BlueBus{*this};  // COPY CONSTRUCTOR CALLED!
    }
};

class YellowBus : public Vehicle
{
    using Vehicle::Vehicle;
    std::default_random_engine m_engine{100};
    std::bernoulli_distribution m_dist{.5};

public:
    void update() override
    {
        std::cout << '[' << getName() << "]\n"
                  << "\tAnimation:" << getAnimation() << '\n';
        if (m_dist(m_engine))
            std::cout << "\tMoving out of the way\n";
        std::cout << "\tSpeed:" << getSpeed() << '\n'
                  << "\tHitPoints:" << getHitPoints() << '\n'
                  << "\tPosition:" << getPosition() << '\n';
    }

    Vehicle *clone() override
    {
        std::cout << "[YellowBus] Cloning->" << getName() << std::endl;
        return new YellowBus{*this};  // COPY CONSTRUCTOR CALLED!
    }
};

enum class VehicleType { RedCar, GreenCar, YellowBus, BlueBus };

// Parametrized factory method
Vehicle *create(VehicleType type,
                int speed,
                int hitpoints,
                const std::string &name,
                std::string_view animFile,
                Position position)
{
    switch (type) {
        case VehicleType::RedCar:
            return new RedCar{speed, hitpoints, name, animFile, position};
        case VehicleType::GreenCar:
            return new GreenCar{speed, hitpoints, name, animFile, position};
        case VehicleType::YellowBus:
            return new YellowBus{speed, hitpoints, name, animFile, position};
        case VehicleType::BlueBus:
            return new BlueBus{speed, hitpoints, name, animFile, position};
        default:
            throw std::runtime_error("Unknown vehicle type");
    }
}

class GameManager
{
    std::vector<Vehicle *> m_vehicles{};

public:
    void run()
    {
        // Use a factory method to prevent coupling concrete implementations with game logic and remove dependencies
        m_vehicles.push_back(create(VehicleType::RedCar, 30, 10, "RedCar", "red.anim", {0, 0}));
        m_vehicles.push_back(create(VehicleType::GreenCar, 30, 15, "GreenCar", "green.anim", {100, 0}));
        m_vehicles.push_back(create(VehicleType::YellowBus, 25, 20, "YellowBus", "yellow.anim", {100, 200}));
        m_vehicles.push_back(create(VehicleType::BlueBus, 25, 25, "BlueBus", "blue.anim", {200, 200}));

        using namespace std;
        int count{5};
        while (count != 0) {
            std::this_thread::sleep_for(1s);
            // system("clear");
            for (auto vehicle : m_vehicles) {
                vehicle->update();
            }

            if (count == 2) {
                auto vehicle{m_vehicles[0]->clone()};
                vehicle->setSpeed(30);
                vehicle->setHitPoints(15);
                vehicle->setName("bluuu");
                vehicle->setAnimationData("blue.anim");
                vehicle->setPosition({50, 50});
                m_vehicles.push_back(vehicle);
            }
            if (count == 3) {
                auto newRed{m_vehicles[0]->clone()};
                newRed->setSpeed(20);
                newRed->setHitPoints(5);
                newRed->setPosition({500, 50});
                m_vehicles.push_back(newRed);
            }
            --count;
        }
    }

    ~GameManager()
    {
        for (auto &vehicle : m_vehicles)
            delete vehicle;
    }
};

int main()
{
    GameManager gm;
    gm.run();
    return 0;
}
