#include <iostream>
#include <memory>

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

class SpreadsheetDocument : public Document
{
    void read() override { std::cout << __func__ << std::endl; }

    void write() override { std::cout << __func__ << std::endl; }
};

using DocumentPtr = std::unique_ptr<Document>;
class Application
{
    DocumentPtr m_pDocument;

public:
    // Application is now tightly coupled with TextDocument
    void newDoc() { m_pDocument = create(); }
    void open()
    {
        m_pDocument = create();
        m_pDocument->read();
    }
    void save()
    {
        m_pDocument = create();
        m_pDocument->write();
    }
    virtual DocumentPtr create() = 0;
};

class TextApplication : public Application
{
public:
    DocumentPtr create() override { return std::make_unique<TextDocument>(); }
};

class SpreadsheetApplication : public Application
{
public:
    DocumentPtr create() override { return std::make_unique<SpreadsheetDocument>(); }
};

int main()
{
    TextApplication app;
    app.newDoc();
    app.open();
    app.save();
    SpreadsheetApplication sheetApp;
    sheetApp.open();
}
