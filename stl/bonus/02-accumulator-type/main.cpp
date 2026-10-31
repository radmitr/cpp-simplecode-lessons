#include <iostream>
#include <numeric>
#include <type_traits>
#include <vector>

int main()
{
    std::vector<int> values{1000000000, 1000000000, 1000000000};
    const auto total = std::accumulate(values.begin(), values.end(), 0LL);
    static_assert(std::is_same_v<decltype(total), const long long>);
    std::cout << "Long long total: " << total << '\n';
    // Тип результата определяет init. Присваивание суммы в long long после
    // накопления в int не устранило бы уже случившееся переполнение.

    std::vector<double> fractions{1.5, 2.5};
    const int truncated = std::accumulate(fractions.begin(), fractions.end(), 0);
    const double precise = std::accumulate(fractions.begin(), fractions.end(), 0.0);
    // С init=0 каждая промежуточная сумма преобразуется обратно в int.
    std::cout << "Int init: " << truncated << '\n';
    std::cout << "Double init: " << precise << '\n';
    return total == 3000000000LL && truncated == 3 && precise == 4.0 ? 0 : 1;
}
