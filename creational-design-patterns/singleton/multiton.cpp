#include <iostream>
#include <string>
#include <unordered_map>
#include <mutex>

// A "solution" to test a Singleton class by inheriting from a base class

class Printer;

class PrinterProvider {
    inline static std::unordered_map<std::string, Printer*> m_printers{};
    PrinterProvider();
    inline static std::recursive_mutex m_mutex;     // allow doble locking mutex by same thread
public:
    static void registerPrinter(const std::string &name, Printer* printer){
        std::lock_guard lock {m_mutex};
        std::cout << "Registring printer " << name << '\n';
        m_printers[name] = printer;
    }
    static Printer *getPrinterPtr(const std::string &name){
        std::lock_guard lock {m_mutex};
        if(auto it = m_printers.find(name); it != m_printers.end()) 
            return it->second;
        return nullptr;
    }
    static Printer &getPrinterRef(const std::string &name){
        std::lock_guard lock {m_mutex};
        if(auto pPrinter{getPrinterPtr(name)})
            return *pPrinter;
        throw std::runtime_error("No printer with name " + name + " found");
    }
};

class Printer {
protected:
    Printer() = default;

public:
    Printer(const Printer&) = delete;
    Printer& operator =(const Printer&) = delete;
    virtual ~Printer() = default;
    virtual void print(const std::string &data) = 0 ;
    virtual Printer &getInstance() = 0;
};


class LocalPrinter : public Printer {
    static LocalPrinter m_instance;
    LocalPrinter() {
        PrinterProvider::registerPrinter("local", this);
    };
public:
    void print(const std::string &data) override {
        std::cout << "[LOCAL PRINTER] " << data << std::endl;
    }
    LocalPrinter &getInstance() override { return m_instance; }
};
LocalPrinter LocalPrinter::m_instance ;


class HttpPrinter : public Printer {
    static HttpPrinter m_instance;
    HttpPrinter() {
        PrinterProvider::registerPrinter("http", this);
    };
public:
    void print(const std::string &data) override {
        std::cout << "[HTTP PRINTER] " << data << std::endl;
    }
    HttpPrinter &getInstance() override { return m_instance; }
};
HttpPrinter HttpPrinter::m_instance ;


int main(){
    Printer *printer = PrinterProvider::getPrinterPtr("local");
    if(printer)
        printer->print("hello wooorld");

    auto &httpPrinter = PrinterProvider::getPrinterRef("http").getInstance();
    httpPrinter.print("hehe");
}

