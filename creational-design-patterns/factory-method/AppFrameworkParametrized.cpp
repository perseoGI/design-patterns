#include <iostream>
#include <memory>

class Document
{
public:
    virtual void read() = 0;
    virtual void write() = 0;
    virtual ~Document() = default;
};

using DocumentPtr = std::unique_ptr<Document>;

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

// Factory class
class DocumentFactory
{
public:
    // Factory method
    static DocumentPtr create(const std::string &type)
    {
        if (type == "text")
            return std::make_unique<TextDocument>();
        else if (type == "spreadsheet")
            return std::make_unique<SpreadsheetDocument>();
        throw std::runtime_error("no type found");
    }
};

class Application
{
    DocumentPtr m_pDocument;

public:
    // Application is now tightly coupled with TextDocument
    void newDoc() { m_pDocument = DocumentFactory::create("text"); }

    void open()
    {
        m_pDocument = DocumentFactory::create("text");
        m_pDocument->read();
    }

    void save()
    {
        m_pDocument = DocumentFactory::create("text");
        m_pDocument->write();
    }
};

int main()
{
    Application app;
    app.newDoc();
    app.open();
    app.save();
}
