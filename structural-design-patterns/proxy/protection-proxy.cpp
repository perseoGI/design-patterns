#include <iostream>
#include <sstream>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <algorithm>

class Storage
{
public:
    virtual void createFile(const std::string &fileName) = 0;
    virtual void deleteFile(const std::string &fileName) = 0;
    virtual void updateFile(const std::string &fileName) = 0;
    virtual void viewFile(const std::string &fileName) = 0;
    virtual ~Storage() = default;
};

class Employee
{
    std::string m_name;
    std::string m_role;

public:
    Employee(const std::string &name, const std::string &role)
        : m_name{name}
        , m_role{role}
    {
    }

    std::string getInfo() const
    {
        std::ostringstream out;
        out << '[' << m_role << "] " << m_name;
        return out.str();
    }
    const std::string &getName() const { return m_name; }
    const std::string &getRole() const { return m_role; }
};

class Repository : public Storage
{
    Employee *m_pEmp;
    std::filesystem::path m_currentPath;

public:
    Employee *getUser() const { return m_pEmp; }

    void setEmployee(Employee *p) { m_pEmp = p; }

    Repository(const std::string &repoPath)
        : m_currentPath{repoPath}
    {
    }

    void createFile(const std::string &fileName) override
    {
        auto path{m_currentPath};
        path /= fileName;
        std::ofstream out{path};
        if (!out.is_open()) {
            throw std::runtime_error{"Could not create file"};
        }
        std::cout << getUser()->getInfo() << " is creating a file\n";
        std::string fileData;

        std::cout << "[CREATE] enter data:";
        getline(std::cin, fileData);
        out << fileData;
        std::cout << "File created successfully!\n";
    }

    void deleteFile(const std::string &fileName) override
    {
        auto path{m_currentPath};
        path /= fileName;
        if (!exists(path)) {
            throw std::runtime_error{"Path does not exist"};
        }
        std::cout << getUser()->getInfo() << " is deleting a file\n";

        std::cout << "File deleted successfully!\n";
    }

    void updateFile(const std::string &fileName) override
    {
        auto path{m_currentPath};
        path /= fileName;
        std::ofstream out{path};
        if (!out.is_open()) {
            throw std::runtime_error{"Could not create file"};
        }
        std::cout << getUser()->getInfo() << " is updating a file\n";
        std::string fileData;

        std::cout << "[UPDATE] enter data:";
        getline(std::cin, fileData);
        out << fileData;
        std::cout << "File updated successfully!\n";
    }

    void viewFile(const std::string &fileName) override
    {
        auto path{m_currentPath};
        path /= fileName;
        if (!exists(path)) {
            throw std::runtime_error{"Path does not exist"};
        }
        std::ofstream out{path};
        if (!out.is_open()) {
            throw std::runtime_error{"Could not create file"};
        }
        std::cout << getUser()->getInfo() << " is viewing a file\n";
        std::string fileData;

        getline(std::cin, fileData);
        out << fileData;
        std::cout << "File viewed successfully!\n";
    }
};

class RepoProxy : public Storage
{
    Repository *m_pRepo{};
    std::vector<std::string> m_authorizedRoles;
    bool isAuthorized() const
    {
        if (m_authorizedRoles.empty()) {
            throw std::runtime_error{"Authorized roles not set"};
        }
        return std::any_of(begin(m_authorizedRoles), end(m_authorizedRoles), [this](const std::string &role) {
            return getUser()->getRole() == role;
        });
    }
    Employee *getUser() const { return m_pRepo->getUser(); }

public:
    RepoProxy(const std::string &repoPath)
        : m_pRepo{new Repository{repoPath}}
    {
    }

    void setAuthorizedRules(std::initializer_list<std::string> authorizedRules)
    {
        m_authorizedRoles.assign(authorizedRules);
    }

    virtual ~RepoProxy() { delete m_pRepo; }

    void setEmployee(Employee *emp) { m_pRepo->setEmployee(emp); }

    void createFile(const std::string &fileName) override
    {
        if (isAuthorized())
            m_pRepo->createFile(fileName);
        else
            std::cout << getUser()->getInfo() << " is not authorized to create a file\n";
    }

    void deleteFile(const std::string &fileName) override
    {
        if (isAuthorized())
            m_pRepo->deleteFile(fileName);
        else
            std::cout << getUser()->getInfo() << " is not authorized to delete a file\n";
    }
    void updateFile(const std::string &fileName) override
    {
        if (isAuthorized())
            m_pRepo->updateFile(fileName);
        else
            std::cout << getUser()->getInfo() << " is not authorized to update a file\n";
    }
    void viewFile(const std::string &fileName) override
    {
        if (isAuthorized())
            m_pRepo->viewFile(fileName);
        else
            std::cout << getUser()->getInfo() << " is not authorized to view a file\n";
    }
};

int main()
{
    try {
        // Repository repo{R"(./)"};
        RepoProxy repo{R"(./)"};
        repo.setAuthorizedRules({"Manager", "Teach Lead"});
        Employee e1{"Perseo", "Programmer"};
        Employee e2{"Alex", "Manager"};
        Employee e3{"Pepe", "Teach Lead"};

        repo.setEmployee(&e1);
        repo.createFile("data.out");

        repo.setEmployee(&e2);
        repo.viewFile("data.out");
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
