#include <iostream>
#include <thread>
#include <fstream>

class Image
{
    std::string m_fileName;

protected:
    void setFileName(const std::string &fileName) { m_fileName = fileName; }

public:
    Image() = default;
    Image(const std::string &fileName)
        : m_fileName(fileName){};
    virtual ~Image() = default;
    const std::string &getFileName() const { return m_fileName; }
    virtual void load() = 0;
    virtual void load(const std::string &fileName) = 0;
    virtual void display() = 0;
};

class Bitmap : public Image
{
    std::string m_buffer;

public:
    // Bitmap() = default;
    // Bitmap(const std::string &fileName);
    using Image::Image;  // C++17 inherit constructors: this class constructors will call base class constructors

    void load() override
    {
        m_buffer.clear();
        std::ifstream file(getFileName());
        if (!file) {
            throw std::runtime_error{"Failed to open file"};
        }
        std::string line;
        std::cout << "Loading bitmap[";
        using namespace std::chrono_literals;
        while (std::getline(file, line)) {
            m_buffer += line + '\n';
            std::this_thread::sleep_for(100ms);
            std::cout << '.' << std::flush;
        }
        std::cout << "] Done!\n";
    }

    void load(const std::string &fileName) override
    {
        setFileName(fileName);
        load();
    }

    void display() override { std::cout << m_buffer; }
};

class BitmapProxy : public Image
{
    Bitmap *m_pBitmap{};
    std::string m_fileName;
    bool m_loaded{false};

public:
    BitmapProxy()
        : BitmapProxy{""}
    {
    }

    BitmapProxy(const std::string fileName) { m_pBitmap = new Bitmap{fileName}; }

    ~BitmapProxy() { delete m_pBitmap; }

    void load() override { m_fileName.clear(); }

    void load(const std::string &fileName) override
    {
        m_fileName = fileName;
        load();
    }

    void display() override
    {
        if (!m_loaded) {
            std::cout << "[Proxy] loading bitmap\n";
            if (m_fileName.empty()) {
                m_pBitmap->load();
            } else {
                m_pBitmap->load(m_fileName);
            }
        }
        m_pBitmap->display();
    }
};

int main()
{
    // Image *p{new Bitmap{"smily.txt"}};
    // p->load();
    // p->display();
    // delete p;

    Image *pProxy{new BitmapProxy{"smily.txt"}};
    pProxy->load();
    pProxy->display();  // if we dont display, bitmap will not be loaded
    delete pProxy;
}
