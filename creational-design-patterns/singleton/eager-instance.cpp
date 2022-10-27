#include <cstdio>
#include <memory>

class Logger {
    FILE *pStream;
    Logger(){
        pStream = fopen("log.txt", "w");
    }

    static Logger m_instance;       // eager instance

public:
    Logger(const Logger&) = delete; // delete copy constructor
    Logger &operator= (const Logger &) = delete; // delete assignment operator

    static Logger &getInstance(){          // Only method to access instance
        return m_instance;
    }

    ~Logger() = default;
    void log(const char *message) {
        fprintf(pStream, "%s", message);
    }

};

Logger Logger::m_instance;

int main()
{
    Logger &logger = Logger::getInstance();  
    logger.log("hi from eager instance");

    return 0;
}
