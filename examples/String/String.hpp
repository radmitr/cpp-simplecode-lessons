#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <cstddef>

class String
{
public:
    static constexpr size_t npos = -1;
    static constexpr size_t MAX_INPUT = 1023;

    String();
    String(const char* s);
    String(const String& other);
    String(String&& other) noexcept;
    ~String();

    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;

    String operator+(const String& other) const;
    String& operator+=(const String& other);

    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;
    bool operator<(const String& other) const;
    bool operator>(const String& other) const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    size_t find(const String& substr) const;
    String substr(size_t pos, size_t count = npos) const;
    String& replace(size_t pos, size_t count, const String& replacement);

    String toUpper() const;
    String toLower() const;

    bool startsWith(const String& prefix) const;
    bool endsWith(const String& suffix) const;

    char* begin();
    const char* begin() const;
    char* end();
    const char* end() const;

    void print() const;
    const char* c_str() const;
    size_t length() const;
    size_t size() const;
    bool empty() const;
    void clear();

    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator>>(std::istream& is, String& str);
    friend std::istream& getline(std::istream& is, String& str, char delim);
    friend std::istream& getline(std::istream& is, String& str);

private:
    char* str;
    size_t len;

    String(char* buf, size_t length) noexcept;
};

std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& str);
std::istream& getline(std::istream& is, String& str, char delim);
std::istream& getline(std::istream& is, String& str);

#endif // STRING_HPP
