#include <iostream>
#include <stdexcept>

class Member
{
public:
    explicit Member(const char* name) : name_(name)
    {
        std::cout << "construct " << name_ << '\n';
    }
    ~Member()
    {
        std::cout << "destroy " << name_ << '\n';
    }

private:
    const char* name_;
};

class Operation
{
public:
    Operation()
    {
        std::cout << "constructor throws\n";
        throw std::runtime_error("initialization failed");
    }
    ~Operation()
    {
        // Конструктор не завершился, поэтому эта строка не появится.
        std::cout << "destroy Operation\n";
    }

private:
    Member first_{"first"};
    Member second_{"second"};
};

int main()
{
    try
    {
        Operation operation;
    }
    catch (const std::exception& error)
    {
        std::cout << "caught: " << error.what() << '\n';
    }
}
