#include <iostream>
#include <thread>

// #include <objbase.h>
// This emulates win32 HRESULT
enum class HRESULT {
    S_OK,
};

class IAnimate
{
public:
    virtual HRESULT setImage(unsigned char image) = 0;
    virtual HRESULT animate(int duration) = 0;
    virtual ~IAnimate() = default;
};

class Sprite : public IAnimate
{
    unsigned char m_image;

public:
    HRESULT setImage(unsigned char image) override
    {
        m_image = image;
        return HRESULT::S_OK;
    }

    HRESULT animate(int duration) override
    {
        using namespace std::chrono_literals;
        for (int i{0}; i < duration; ++i) {
            std::cout << m_image << std::flush;
            std::this_thread::sleep_for(1s);
        }
        return HRESULT::S_OK;
    }
};

void draw(IAnimate *p)
{
    p->setImage('#');
    p->animate(4);
}

int main()
{
    Sprite s;
    draw(&s);
}

// TBD: use an idl to create a server and client via RCP
