
template <typename T>
class BaseSingleton
{
protected:
    BaseSingleton() = default;
    BaseSingleton(const BaseSingleton &) = delete;
    BaseSingleton &operator=(const BaseSingleton &) = delete;

public:
    static T &getInstance()
    {
        static T *instance{new T{}};
        return *instance;
    }
};

#define MAKE_SINGLETON(class_name) \
private:                           \
    class_name() = default;        \
    friend class BaseSingleton<class_name>;

class GameManager : public BaseSingleton<GameManager>
{
    // private:
    //     GameManager() = default;
    //     friend class BaseSingleton<GameManager>;

    // Or use the macro!
    MAKE_SINGLETON(GameManager);

public:
    void loadGame() {}
};

class Logger : public BaseSingleton<Logger>
{
private:
    Logger() = default;
    friend class BaseSingleton<Logger>;

public:
    void log(const char *message) {}
};

int main()
{
    GameManager &gm = GameManager::getInstance();
    // GameManager gm1 = gm;    // imposible    // imposible
    gm.loadGame();

    return 0;
}
