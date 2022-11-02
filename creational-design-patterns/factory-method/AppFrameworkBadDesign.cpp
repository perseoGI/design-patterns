#include <iostream>

class Document
{
public:
    virtual void read() = 0;
    virtual void write() = 0;
    virtual ~Document() = default;
};

class TextDocument : public Document
{
    void read() override { std::cout << __func__ << std::endl; }

    void write() override { std::cout << __func__ << std::endl; }
};

class Document;  // Use forward declaration (on separated files) in order to reduce dependency
class Application
{
    Document *m_pDocument;

public:
    // Application is now tightly coupled with TextDocument
    void newDoc() { m_pDocument = new TextDocument{}; }

    void open() { m_pDocument->read(); }
    void save() { m_pDocument->write(); }
};

int main()
{
    Application app;
    app.newDoc();
    app.open();
    app.save();
}
