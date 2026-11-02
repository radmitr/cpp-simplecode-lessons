// C++20 — std::osyncstream::emit() и передача буфера.
#include <iostream>
#include <sstream>
#include <streambuf>
#include <syncstream>

class TrackedBuffer : public std::stringbuf
{
public:
    int flushes = 0;
    int sync() override
    {
        ++flushes;
        return 0; // В учебном буфере сброс всегда успешен.
    }
};

int main()
{
    TrackedBuffer buffer;
    std::ostream destination(&buffer);
    bool correct = true;
    {
        std::osyncstream message(destination);
        message << "A";
        correct = correct && buffer.str().empty();

        message.emit(); // Текст дошёл до destination, сброс sync() не запрошен.
        correct = correct && buffer.str() == "A" && buffer.flushes == 0;

        message << "B" << std::flush; // Запомнить запрос; по умолчанию ещё не emit.
        correct = correct && buffer.str() == "A" && buffer.flushes == 0;
        message.emit(); // Теперь передать B и выполнить отложенный сброс.
        correct = correct && buffer.str() == "AB" && buffer.flushes == 1;

        message << std::emit_on_flush << "C" << std::flush; // Сразу передать и сбросить.
        correct = correct && buffer.str() == "ABC" && buffer.flushes == 2;
        message << std::noemit_on_flush << "D" << std::flush_emit; // Явная передача со сбросом.
        correct = correct && buffer.str() == "ABCD" && buffer.flushes == 3;
    }
    std::cout << "Transferred: " << buffer.str() << "; flushes: " << buffer.flushes << '\n';
    return correct ? 0 : 1;
}
