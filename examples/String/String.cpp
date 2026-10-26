#include "String.hpp"
#include <cstring>
#include <cstddef>
#include <cctype>
#include <new>
#include <stdexcept>

#define STRING_ENABLE_LOGGING false // comment for production

#ifdef STRING_ENABLE_LOGGING
    #define LOG(x) std::cout << x << std::endl
#else
    #define LOG(x) (void)0
#endif

String::String()
    : str(new char[1]{'\0'}), len(0)
{
    LOG("Default constructor " << this << ": (empty)");
}

String::String(const char* s)
    : String()
{
    LOG("Const char* constructor (after delegation) " << this << ": " << s);
    if (s != nullptr && s[0] != '\0')
    {
        delete[] str;
        len = std::strlen(s);
        str = new char[len + 1];
        std::strcpy(str, s);
    }
}

String::String(const String& other)
    : str(new char[other.len + 1]), len(other.len)
{
    std::strcpy(str, other.str);
    LOG("Copy constructor " << this << ": "  << (len == 0 ? "(empty)" : str));
}

String::String(String&& other) noexcept
    : str(other.str), len(other.len)
{
    LOG("Move constructor " << this << " <- " << &other << ": " << (len == 0 ? "(empty)" : str));
    other.str = new char[1]{'\0'};
    other.len = 0;
}

// Private constructor
String::String(char* buf, size_t length) noexcept
    : str(buf), len(length)
{
    LOG("Private buffer constructor " << this << ": " << (len == 0 ? "(empty)" : str));
}

String::~String()
{
    LOG("Destructor " << this << ": " << (len == 0 ? "(empty)" : str));
    delete[] str;
}

String& String::operator=(const String& other)
{
    LOG("Copy assignment " << this << " <- " << &other << " (\"" << str << "\" <- \"" << other.str << "\")");
    if (this == &other)
    {
        return *this;
    }

    delete[] str;
    len = other.len;
    str = new char[len + 1];
    std::strcpy(str, other.str);

    return *this;
}

String& String::operator=(String&& other) noexcept
{
    LOG("Move assignment " << this << " <- " << &other << " (\"" << str << "\" <- \"" << other.str << "\")");
    if (this != &other)
    {
        delete[] str;
        str = other.str;
        len = other.len;
        other.str = new char[1]{'\0'};
        other.len = 0;
    }

    return *this;
}

String String::operator+(const String& other) const
{
    size_t newLength = len + other.len;

    LOG("Operator+ called on \""
        << (len == 0 ? "(empty)" : str)
        << "\" + \""
        << (other.len == 0 ? "(empty)" : other.str)
        << "\" → new length = " << newLength
    );

    if (newLength == 0)
    {
        return String();
    }

    char* newStr = new char[newLength + 1];
    std::memcpy(newStr, str, len);
    std::memcpy(newStr + len, other.str, other.len);
    newStr[newLength] = '\0';

    String result(newStr, newLength);

    LOG("  → created temporary: \""
        << (result.len == 0 ? "(empty)" : result.str)
        << "\""
    );

    return result;
}

String& String::operator+=(const String& other)
{
    LOG("Operator+= on \""
        << (len == 0 ? "(empty)" : str)
        << "\" with \""
        << (other.len == 0 ? "(empty)" : other.str)
        << "\""
    );

    *this = *this + other;
    return *this;
}

bool String::operator==(const String& other) const
{
    return std::strcmp(str, other.str) == 0;
}

bool String::operator!=(const String& other) const
{
    return !(*this == other);
}

bool String::operator<(const String& other) const
{
    return std::strcmp(str, other.str) < 0;
}

bool String::operator>(const String& other) const
{
    return other < *this;
}

char& String::operator[](size_t index)
{
    if (index >= len)
    {
        throw std::out_of_range("String index out of range");
    }
    return str[index];
}

const char& String::operator[](size_t index) const
{
    if (index >= len)
    {
        throw std::out_of_range("String index out of range");
    }
    return str[index];
}

size_t String::find(const String& substr) const
{
    const char* pos = std::strstr(str, substr.str);
    return pos ? pos - str : String::npos;
}

String String::substr(size_t pos, size_t count) const
{
    LOG("Substr(\"" << (len == 0 ? "(empty)" : str)
        << "\", " << pos << ", " << (count == npos ? "npos" : std::to_string(count))
        << ")"
    );

    if (pos > len)
    {
        throw std::out_of_range("String index out of range");
    }

    size_t actualCount = (count == npos || pos + count > len) ? len - pos : count;

    char* buffer = new char[actualCount + 1];
    if (actualCount > 0)
    {
        std::memcpy(buffer, str + pos, actualCount);
    }
    buffer[actualCount] = '\0';

    String result(buffer, actualCount);
    LOG("  → result: \"" << (result.len == 0 ? "(empty)" : result.str) << "\"");
    return result;
}

String& String::replace(size_t pos, size_t count, const String& replacement)
{
    LOG("Replace in \"" << (len == 0 ? "(empty)" : str)
        << "\" at " << pos << ", count=" << count
        << " with \"" << (replacement.len == 0 ? "(empty)" : replacement.str)
        << "\""
    );

    if (pos > len)
    {
        throw std::out_of_range("String::replace: pos out of range");
    }

    const size_t maxCount = len - pos;
    const size_t actualCount = (count == npos || count > maxCount) ? maxCount : count;
    const size_t newLen = len - actualCount + replacement.len;

    char* newStr = new char[newLen + 1];

    if (pos > 0)
    {
        std::memcpy(newStr, str, pos);
    }

    if (replacement.len > 0)
    {
        std::memcpy(newStr + pos, replacement.str, replacement.len);
    }

    const size_t afterPos = pos + actualCount;
    const size_t afterLen = len - afterPos;
    if (afterLen > 0)
    {
        std::memcpy(newStr + pos + replacement.len, str + afterPos, afterLen);
    }

    newStr[newLen] = '\0';

    delete[] str;
    str = newStr;
    len = newLen;

    LOG("  → replaced: \"" << str << "\"");
    return *this;
}

String String::toUpper() const
{
    String result = *this;
    for (char& c : result)
    {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    return result;
}

String String::toLower() const
{
    String result = *this;
    for (char& c : result)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
}

bool String::startsWith(const String& prefix) const
{
    if (prefix.len > len)
    {
        return false;
    }
    return std::strncmp(str, prefix.str, prefix.len) == 0;
}

bool String::endsWith(const String& suffix) const
{
    if (suffix.len > len)
    {
        return false;
    }
    size_t offset = len - suffix.len;
    return std::strcmp(str + offset, suffix.str) == 0;
}

char* String::begin()
{
    return str;
}

const char* String::begin() const
{
    return str;
}

char* String::end()
{
    return str + len;
}

const char* String::end() const
{
    return str + len;
}

void String::print() const
{
    std::cout << str;
}

const char* String::c_str() const
{
    return str;
}

size_t String::length() const
{
    return len;
}

size_t String::size() const
{
    return len;
}

bool String::empty() const
{
    return len == 0;
}

void String::clear()
{
    LOG("Clear \"" << (len == 0 ? "(empty)" : str) << "\"");
    delete[] str;
    str = new char[1]{'\0'};
    len = 0;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, String& str)
{
    char buffer[String::MAX_INPUT + 1];

    if (is >> buffer)
    {
        delete[] str.str;
        str.len = std::strlen(buffer);
        str.str = new char[str.len + 1];
        std::strcpy(str.str, buffer);
    }
    else
    {
        delete[] str.str;
        str.str = new char[1]{'\0'};
        str.len = 0;
    }

    return is;
}

std::istream& getline(std::istream& is, String& str, char delim)
{
    char buffer[String::MAX_INPUT + 1];

    if (is.getline(buffer, String::MAX_INPUT, delim))
    {
        delete[] str.str;
        str.len = std::strlen(buffer);
        str.str = new char[str.len + 1];
        std::strcpy(str.str, buffer);
    }
    else
    {
        delete[] str.str;
        str.str = new char[1]{'\0'};
        str.len = 0;
    }

    return is;
}

std::istream& getline(std::istream& is, String& str)
{
    return getline(is, str, '\n');
}
