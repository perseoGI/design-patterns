#include <iostream>
#include <sstream>
#include <ctime>

class Clock
{
private:
    inline static int m_hour{};
    inline static int m_minute{};
    inline static int m_second{};

    static void getCurrentTime()
    {
        time_t raw_time;
        time(&raw_time);
        tm *local_time = localtime(&raw_time);
        m_hour = local_time->tm_hour;
        m_minute = local_time->tm_min;
        m_second = local_time->tm_sec;
    }

    Clock();

public:
    static int hour()
    {
        getCurrentTime();
        return m_hour;
    }
    static int minute()
    {
        getCurrentTime();
        return m_minute;
    }
    static int second()
    {
        getCurrentTime();
        return m_second;
    }

    static std::string timeAsString()
    {
        std::stringstream ss;
        getCurrentTime();
        ss << m_hour << ':' << m_minute << ':' << m_second;
        return ss.str();
    }
};

int main()
{
    std::cout << Clock::timeAsString() << std::endl;
    return 0;
}
