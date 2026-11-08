// C++20 — std::binary_semaphore::try_acquire().
#include <iostream>
#include <semaphore>

int main()
{
    std::binary_semaphore permit(1);
    // Ложная неудача разрешена. Для короткого опыта повторяем попытку до успеха.
    while (!permit.try_acquire()) {}
    const bool second = permit.try_acquire(); // Разрешение уже у нас: false.
    std::cout << "First acquired; second: " << std::boolalpha << second << '\n';
    permit.release(); // Возвращаем ровно одно забранное разрешение.
    return second ? 1 : 0;
}
