#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

// A "solution" to test a Singleton class by inheriting from a base class

class Printer;
using PrinterPtr = std::shared_ptr<Printer>;
using Creator = std::function<PrinterPtr()>;

class PrinterProvider {

  inline static std::unordered_map<std::string, PrinterInfo> m_printers{};
  PrinterProvider();
  inline static std::recursive_mutex
      m_mutex; // allow doble locking mutex by same thread
public:
  static void registerPrinter(const std::string &name, Creator creator) {
    std::lock_guard lock{m_mutex};
    std::cout << "Registring printer " << name << '\n';
    m_printers[name].creator = creator;
  }
  static PrinterPtr getPrinter(const std::string &name) {
    std::lock_guard lock{m_mutex};
    if (auto it{m_printers.find(name)}; it != m_printers.end()) {
      if (!it->second.printer) {
        m_printers[name].printer = m_printers[name].creator();
      }
      return m_printers[name].printer;
    }
    throw std::runtime_error("No printer with name " + name + " found");
  }
};

class Printer {
protected:
  Printer() = default;

public:
  Printer(const Printer &) = delete;
  Printer &operator=(const Printer &) = delete;
  virtual ~Printer() = default;
  virtual void print(const std::string &data) = 0;
};

class LocalPrinter : public Printer {
public:
  void print(const std::string &data) override {
    std::cout << "[LOCAL PRINTER] " << data << std::endl;
  }
  LocalPrinter &getInstance() {
    static LocalPrinter instance;
    return instance;
  }
};


int main() {
  PrinterProvider::registerPrinter("local");

  auto httpPrinter = PrinterProvider::getPrinter("http");
  httpPrinter->print("hehe");
}
