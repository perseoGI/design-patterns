#include <cstdio>
#include <memory>

class Logger
{
    // Needed as ~Logger is private to avoid manually deleting instance
    struct Deleter {
        void operator()(Logger *p) { delete p; }
    };

    FILE *m_pStream;
    Logger() { m_pStream = fopen("log.txt", "w"); }

    inline static std::unique_ptr<Logger, Deleter> m_pInstance{};  // lazy instance
    ~Logger() { fclose(m_pStream); }

public:
    Logger(const Logger &) = delete;  // delete copy constructor

    static Logger &getInstance()
    {  // Only method to access instance
        if (!m_pInstance) {
            m_pInstance.reset(new Logger{});
        }
        return *m_pInstance;
    }

    void log(const char *message) { fprintf(m_pStream, "%s", message); }
};

int main()
{
    Logger &logger = Logger::getInstance();
    logger.log("hi doggy");
    // delete logger;
    // auto *p = &logger;
    // delete p;            // invalid operation

    return 0;
}
