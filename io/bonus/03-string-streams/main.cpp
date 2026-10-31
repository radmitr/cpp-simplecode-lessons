#include <sstream>
#include <string>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        std::istringstream input("7 Ada 42");
        int id=0, score=0; std::string name;
        check(static_cast<bool>(input >> id >> name >> score), "record parsing failed");
        input >> std::ws;
        check(input.eof() && id==7 && name=="Ada" && score==42, "trailing data or wrong record");
        std::ostringstream output;
        output << id << ':' << name << ':' << score;
        check(output.str()=="7:Ada:42", "record formatting failed");
        input.clear(); input.str("9 Bob 10");
        check(static_cast<bool>(input >> id >> name >> score) && id==9, "stream reuse failed");
        std::cout << output.str() << '\n';
        std::cout << "OK 03-string-streams\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
