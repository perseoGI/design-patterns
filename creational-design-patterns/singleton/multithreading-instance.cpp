#include <cstdio>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

class Logger
{
    // Needed as ~Logger is private to avoid manually deleting instance
    struct Deleter {
        void operator()(Logger *p) { delete p; }
    };

    inline static std::mutex m_mutex{};
    FILE *m_pStream;
    inline static std::unique_ptr<Logger, Deleter> m_pInstance{};  // lazy instance

    Logger()
    {
        std::cout << __func__ << std::endl;
        m_pStream = fopen("log.txt", "w");
    }

    ~Logger()
    {
        std::cout << __func__ << std::endl;
        fclose(m_pStream);
    }

public:
    Logger(const Logger &) = delete;  // delete copy constructor

    static Logger &getInstance()
    {  // Only method to access instance
        // m_mutex.lock();
        // if (!m_pInstance) {
        //   m_pInstance.reset(new Logger{});
        // }
        // m_mutex.unlock();

        // Improve performance on multithreading -> Doble-checked locking pattern!
        // In this situation it is NOT SECURE -> see DLCP.md
        if (!m_pInstance) {
            m_mutex.lock();
            if (!m_pInstance) {
                m_pInstance.reset(new Logger{});
            }
            m_mutex.unlock();
        }

        return *m_pInstance;
    }

    void log(const char *message) { fprintf(m_pStream, "%s", message); }
};

int main()
{
    std::thread t1{[]() {
        Logger &lg = Logger::getInstance();
        lg.log("Thread 1 started");
    }};

    std::thread t2{[]() {
        Logger &lg = Logger::getInstance();
        lg.log("Thread 2 started");
    }};
    t1.join();
    t2.join();

    // without a mutex, possible 2 calls to constructor and destructor
    return 0;
}
