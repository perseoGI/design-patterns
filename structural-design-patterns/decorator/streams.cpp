#include <iostream>
#include <fstream>
#include <algorithm>

class InputStream
{
public:
    virtual bool read(std::string &text) = 0;
    virtual void close() = 0;
    virtual ~InputStream() = default;
};

class OutputStream
{
public:
    virtual void write(const std::string &text) = 0;
    virtual void close() = 0;
    virtual ~OutputStream() = default;
};

class FileInputStream : public InputStream
{
    std::ifstream m_reader;

public:
    FileInputStream() = default;
    FileInputStream(const std::string &fileName)
    {
        m_reader.open(fileName);
        if (!m_reader) {
            throw std::runtime_error{"File could not be opened"};
        }
    }

    bool read(std::string &text) override
    {
        text.clear();
        std::getline(m_reader, text);
        return !text.empty();
    }

    void close() override
    {
        if (m_reader.is_open()) {
            m_reader.close();
        }
    }
};

class FileOutputStream : public OutputStream
{
    std::ofstream m_reader;

public:
    FileOutputStream() = default;
    FileOutputStream(const std::string &fileName)
    {
        m_reader.open(fileName);
        if (!m_reader) {
            throw std::runtime_error{"File could not be opened"};
        }
    }

    void write(const std::string &text) override { m_reader << text; }

    void close() override
    {
        if (m_reader.is_open()) {
            m_reader.close();
        }
    }
};

class BufferedOutputStream : public FileOutputStream
{
    char m_buffer[512]{};
    using FileOutputStream::FileOutputStream;

public:
    void write(const std::string &text) override
    {
        std::cout << "Buffered write \n";
        // TODO implement real buffering
        FileOutputStream::write(text);
    }
    // TODO implement real buffering
    void close() override { FileOutputStream::close(); }
};

class BufferedInputStream : public FileInputStream
{
    char m_buffer[512]{};
    using FileInputStream::FileInputStream;

public:
    bool read(std::string &text) override
    {
        std::cout << "Buffered read \n";
        // TODO implement real buffering
        return FileInputStream::read(text);
    }
    void close() override { FileInputStream::close(); }
};

class EncryptedStream : public FileOutputStream
{
    using FileOutputStream::FileOutputStream;

public:
    void write(const std::string &text) override
    {
        std::string encrypted;
        encrypted.resize(text.size());
        std::transform(text.begin(), text.end(), encrypted.begin(), [](char ch) { return ch + 5; });
        FileOutputStream::write(encrypted);
    }
    void close() override { FileOutputStream::close(); }
};

class DecryptedStream : public FileInputStream
{
    using FileInputStream::FileInputStream;

public:
    bool read(std::string &text) override
    {
        std::string encrypted;
        auto result{FileInputStream::read(encrypted)};
        if (result) {
            text.resize(encrypted.size());
            std::transform(encrypted.begin(), encrypted.end(), text.begin(), [](char ch) { return ch - 5; });
        }
        return result;
    }
    void close() override { FileInputStream::close(); }
};

class CompressedOutputStream : public FileOutputStream
{
    using FileOutputStream::FileOutputStream;

public:
    void write(const std::string &text) override
    {
        // This is not a real implementation
        FileOutputStream::write("compressed" + text);
    }
    void close() override { FileOutputStream::close(); }
};

class DecompressedInputStream : public FileInputStream
{
    using FileInputStream::FileInputStream;

public:
    bool read(std::string &text) override
    {
        // This is not a real implementation
        const auto res{FileInputStream::read(text)};
        if (res) {
            text.erase(text.begin(), text.begin() + 10);
        }
        return res;
    }
    void close() override { FileInputStream::close(); }
};

void read()
{
    // FileInputStream input{"test.out"};
    // BufferedInputStream input{"test.out"};
    // DecryptedStream input{"test.out"};
    DecompressedInputStream input{"test.out"};
    std::string text;
    while (input.read(text)) {
        std::cout << text << std::endl;
    }
}

void write()
{
    // FileOutputStream output{"test.out"};
    // BufferedOutputStream output{"test.out"};
    // EncryptedStream output{"test.out"};
    CompressedOutputStream output{"test.out"};
    output.write("hello\n");
    output.write("world\n");
    output.write("my name is: \n");
    output.write("Perseo\n");
}

int main(int argc, char *argv[])
{
    write();
    read();

    return 0;
}
