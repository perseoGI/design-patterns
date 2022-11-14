#include <iostream>
#include <string_view>
#include <thread>
#include <random>
#include <unordered_map>
#include <memory>

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

class Vehicle;
using VehiclePtr = std::shared_ptr<Vehicle>;

class Vehicle
{
    int m_speed{};
    int m_hitPoints{};
    std::string m_name{};  // debug

    Animation *m_pAnimation{};
    Position m_position{};
    std::string m_color{};

public:
    Vehicle() { m_pAnimation = new Animation{}; }

    Vehicle(int speed,
            int hitpoints,
            const std::string &name,
            std::string_view animFile,
            Position position,
            std::string_view color)
        : m_speed(speed)
        , m_hitPoints(hitpoints)
        , m_name(name)
        , m_position(position)
        , m_color(color)
    {
        m_pAnimation = new Animation{animFile};
    }

    int getSpeed() const { return m_speed; }
    int getHitPoints() const { return m_hitPoints; }
    const std::string &getName() const { return m_name; }
    const std::string &getAnimation() const { return m_pAnimation->getAnimationData(); }
    Position getPosition() const { return m_position; }
    const std::string &getColor() const { return m_color; }

    void setSpeed(int speed) { m_speed = speed; }
    void setHitPoints(int hitpoints) { m_hitPoints = hitpoints; }
    void setName(const std::string &name) { m_name = name; }
    void setAnimationData(const std::string &animData) { m_pAnimation->setAnimationData(animData); }
    void setPosition(const Position &pos) { m_position = pos; }
    void setColor(const std::string &color) { m_color = color; }

    virtual void update() = 0;
    virtual VehiclePtr clone() = 0;

    // Rule of five!
    // If any derived clases had a pointer (resource) this methods should be overridden
    virtual ~Vehicle() { delete m_pAnimation; }

    // Deep copy -> prevent segfault when double deleting a shallow copy
    Vehicle(const Vehicle &vehicle)
        : m_speed(vehicle.m_speed)
        , m_hitPoints(vehicle.m_hitPoints)
        , m_name(vehicle.m_name)
        , m_position(vehicle.m_position)
        , m_color(vehicle.m_color)
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
            m_color = other.m_color;
        }
        return *this;
    }

    Vehicle(const Vehicle &&vehicle)
        : m_speed(vehicle.m_speed)
        , m_hitPoints(vehicle.m_hitPoints)
        , m_name(vehicle.m_name)
        , m_position(vehicle.m_position)
        , m_color(vehicle.m_color)
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
            m_color = other.m_color;

            other.m_speed = 0;
            other.m_name.clear();
            other.m_hitPoints = 0;
            other.m_position = {0, 0};
            other.m_pAnimation = nullptr;
            other.m_color.clear();
        }
        return *this;
    }
};

class Car : public Vehicle
{
    using Vehicle::Vehicle;
    float m_speedFactor{1.5f};
    std::default_random_engine m_engine{100};
    std::bernoulli_distribution m_dist{.5};

public:
    void setSpeedFactor(float f) { m_speedFactor = f; }

    void update() override
    {
        std::cout << '[' << getColor() << ' ' << getName() << "]\n"
                  << "\tAnimation:" << getAnimation() << '\n';
        if (m_dist(m_engine))
            std::cout << "\tIncrease speed temporarily: " << getSpeed() * m_speedFactor << '\n';
        else
            std::cout << "\tSpeed:" << getSpeed() << '\n';

        std::cout << "\tHitPoints:" << getHitPoints() << '\n' << "\tPosition:" << getPosition() << '\n';
    }

    VehiclePtr clone() override
    {
        std::cout << "[Car] Cloning->" << getName() << std::endl;
        return std::shared_ptr<Vehicle>{new Car{*this}};  // COPY CONSTRUCTOR CALLED!
    }
};

class Bus : public Vehicle
{
    using Vehicle::Vehicle;
    std::default_random_engine m_engine{100};
    std::bernoulli_distribution m_dist{.5};

public:
    void update() override
    {
        std::cout << '[' << getColor() << ' ' << getName() << "]\n"
                  << "\tAnimation:" << getAnimation() << '\n';
        if (m_dist(m_engine) && getColor() == "Red")
            std::cout << "\tMoving out of the way\n";
        else
            std::cout << "\tSpeed:" << getSpeed() << '\n';
        std::cout << "\tHitPoints:" << getHitPoints() << '\n' << "\tPosition:" << getPosition() << '\n';
    }

    VehiclePtr clone() override
    {
        std::cout << "[Bus] Cloning->" << getName() << std::endl;
        return std::shared_ptr<Vehicle>{new Bus{*this}};  // COPY CONSTRUCTOR CALLED!
    }
};

enum class VehicleType { RedCar, GreenCar, YellowBus, BlueBus };

class VehiclePrototype
{
    inline static std::unordered_map<std::string, VehiclePtr> m_prototypes{};
    VehiclePrototype() = default;

public:
    static std::vector<std::string> getKeys()
    {
        std::vector<std::string> keys{};
        keys.reserve(m_prototypes.size());
        for (const auto &kv : m_prototypes)
            keys.push_back(kv.first);
        return keys;
    }
    static void registerPrototype(const std::string &key, VehiclePtr prototype)
    {
        if (auto it{m_prototypes.find(key)}; it == m_prototypes.end()) {
            m_prototypes[key] = prototype;
        }
    }

    static VehiclePtr deregisterPrototype(const std::string &key)
    {
        if (auto it{m_prototypes.find(key)}; it != m_prototypes.end()) {
            auto vehicle{it->second};
            m_prototypes.erase(it);
            return vehicle;
        }
        return nullptr;
    }

    static VehiclePtr getPrototype(const std::string &key)
    {
        if (auto it{m_prototypes.find(key)}; it != m_prototypes.end()) {
            return it->second->clone();  // clone!!!
        }
        return nullptr;
    }
};

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
            return new Car{speed, hitpoints, name, animFile, position, "Red"};
        case VehicleType::GreenCar:
            return new Car{speed, hitpoints, name, animFile, position, "Green"};
        case VehicleType::YellowBus:
            return new Bus{speed, hitpoints, name, animFile, position, "Yellow"};
        case VehicleType::BlueBus:
            return new Bus{speed, hitpoints, name, animFile, position, "Blue"};
        default:
            throw std::runtime_error("Unknown vehicle type");
    }
}

VehiclePtr createRedCar()
{
    auto vehicle{VehiclePrototype::getPrototype("car")};
    vehicle->setColor("Red");
    vehicle->setSpeed(30);
    vehicle->setHitPoints(10);
    Animation anim{"red.anim"};
    vehicle->setAnimationData(anim.getAnimationData());
    vehicle->setPosition({0, 0});
    return vehicle;
}

VehiclePtr createGreenCar()
{
    auto vehicle{VehiclePrototype::getPrototype("car")};
    vehicle->setColor("Green");
    vehicle->setSpeed(30);
    vehicle->setHitPoints(10);
    Animation anim{"red.anim"};
    vehicle->setAnimationData(anim.getAnimationData());
    vehicle->setPosition({0, 0});
    return vehicle;
}

VehiclePtr createYellowBus()
{
    auto vehicle{VehiclePrototype::getPrototype("bus")};
    vehicle->setColor("Yellow");
    vehicle->setSpeed(25);
    vehicle->setHitPoints(20);
    Animation anim{"yellow.anim"};
    vehicle->setAnimationData(anim.getAnimationData());
    vehicle->setPosition({100, 200});
    return vehicle;
}

VehiclePtr createBlueBus()
{
    auto vehicle{VehiclePrototype::getPrototype("bus")};
    vehicle->setColor("Blue");
    vehicle->setSpeed(25);
    vehicle->setHitPoints(20);
    Animation anim{"blue.anim"};
    vehicle->setAnimationData(anim.getAnimationData());
    vehicle->setPosition({200, 200});
    return vehicle;
}

class GameManager
{
    std::vector<VehiclePtr> m_vehicles{};

public:
    void run()
    {
        // Use a factory method to prevent coupling concrete implementations with game logic and remove dependencies
        m_vehicles.push_back(createRedCar());
        m_vehicles.push_back(createGreenCar());
        m_vehicles.push_back(createYellowBus());
        m_vehicles.push_back(createBlueBus());

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
};

int main()
{
    VehiclePrototype::registerPrototype("car", std::make_shared<Car>());
    VehiclePrototype::registerPrototype("bus", std::make_shared<Bus>());
    GameManager gm;
    gm.run();
    return 0;
}
