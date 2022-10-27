#include <iostream>
#include <string>

// A "solution" to test a Singleton class by inheriting from a base class

class Printer {
protected:
    Printer() = default;

public:
    ~Printer() = default;
    Printer(const Printer&) = delete;
    Printer& operator =(const Printer&) = delete;
    
    static Printer &getInstance(const std::string &type);

    virtual void print(const std::string &data) = 0 ;
};


class LocalPrinter : public Printer {
    static LocalPrinter m_instance;
    LocalPrinter() = default ;
public:
    static LocalPrinter &getInstance() {
        return m_instance;    
    }
    void print(const std::string &data) override {
        std::cout << "[LOCAL PRINTER] " << data << std::endl;
    }
};

LocalPrinter  LocalPrinter::m_instance;

Printer &Printer::getInstance(const std::string &type) {
    if (type == "local")
        return LocalPrinter::getInstance();
}


int main(){
    Printer &printer = Printer::getInstance("local");
    printer.print("hello wooorld");
}
