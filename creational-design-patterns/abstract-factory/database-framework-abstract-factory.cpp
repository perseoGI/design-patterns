#include <iostream>
#include <vector>

class Connection
{
    std::string m_connectionString;

public:
    void setConnectionString(const std::string &connString) { m_connectionString = connString; }

    const std::string &getConnectionString() const { return m_connectionString; }
    virtual void open() = 0;
    virtual ~Connection() = default;
};

class RecordSet
{
public:
    virtual const std::string &get() = 0;
    virtual bool hasNext() = 0;
    virtual ~RecordSet() = default;
};

class Command
{
    std::string m_commandString;

protected:
    Connection *m_pConnection{};

public:
    void setCommandString(const std::string &commandString) { m_commandString = commandString; }
    void setConnection(Connection *pConn) { m_pConnection = pConn; }
    Connection *getConnection() const { return m_pConnection; }
    const std::string &getCommandString() const { return m_commandString; }

    virtual void executeCommand() = 0;
    virtual RecordSet *executeQuery() = 0;
    virtual ~Command() = default;
};

// SQL server Database
class SqlConnection : public Connection
{
public:
    void open() override
    {
        std::cout << "[SqlConnection] Opening connection on " << getConnectionString() << std::endl;
    }
};

class SqlRecordSet : public RecordSet
{
    const std::vector<std::string> m_db{"Interestelar", "Inception", "Coherence", "Dr Strange"};
    std::vector<std::string>::const_iterator m_cursor;

public:
    SqlRecordSet()
        : m_cursor(m_db.begin())
    {
    }

    const std::string &get() override
    {
        std::cout << "[SqlRecordSet] geting result\n";
        return *m_cursor++;
    }

    bool hasNext() override { return m_cursor != m_db.end(); }
};

class SqlCommand : public Command
{
public:
    void executeCommand() override
    {
        std::cout << "[SqlCommand] Executiong command on " << m_pConnection->getConnectionString() << std::endl;
    }

    // Factory method design pattern -> returns instance of a class
    SqlRecordSet *executeQuery() override
    {
        std::cout << "[SqlCommand] Executing query " << getCommandString() << std::endl;
        return new SqlRecordSet{};
    }
};

// MySQL database
class MySQLConnection : public Connection
{
public:
    void open() override
    {
        std::cout << "[MySQLConnection] Opening connection on " << getConnectionString() << std::endl;
    }
};

class MySQLRecordSet : public RecordSet
{
    const std::vector<std::string> m_db{"Interestelar", "Inception", "Coherence", "Dr Strange"};
    std::vector<std::string>::const_iterator m_cursor;

public:
    MySQLRecordSet()
        : m_cursor(m_db.begin())
    {
    }

    const std::string &get() override
    {
        std::cout << "[MySQLRecordSet] geting result\n";
        return *m_cursor++;
    }

    bool hasNext() override { return m_cursor != m_db.end(); }
};

class MySQLCommand : public Command
{
public:
    void executeCommand() override
    {
        std::cout << "[MySQLCommand] Executiong command on " << m_pConnection->getConnectionString() << std::endl;
    }

    // Factory method design pattern -> returns instance of a class
    MySQLRecordSet *executeQuery() override
    {
        std::cout << "[MySQLCommand] Executing query " << getCommandString() << std::endl;
        return new MySQLRecordSet{};
    }
};

class DatabaseFactory
{
public:
    virtual Connection *createConnection() = 0;
    virtual Command *createCommand() = 0;
    virtual ~DatabaseFactory() = default;
};

class SqlServerFactory : public DatabaseFactory
{
public:
    Connection *createConnection() override { return new SqlConnection{}; }
    Command *createCommand() override { return new SqlCommand{}; }
};

class MySQLFactory : public DatabaseFactory
{
public:
    Connection *createConnection() override { return new MySQLConnection{}; }
    Command *createCommand() override { return new MySQLCommand{}; }
};

int main()
{
    DatabaseFactory *pDb{new SqlServerFactory{}};
    // DatabaseFactory *pDb{new MySQLFactory{}};
    Connection *pConn{pDb->createConnection()};
    pConn->setConnectionString("uid=perseo;db=movies");
    pConn->open();

    Command *pCmd{pDb->createCommand()};
    pCmd->setConnection(pConn);
    pCmd->setCommandString("SELECT * FROM movies");
    RecordSet *result{pCmd->executeQuery()};
    while (result->hasNext()) {
        std::cout << result->get() << std::endl;
    }
}
