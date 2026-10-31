#include <cassert>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

struct Inventory
{
    int available = 3;
    std::mutex mtx;
};

// Возвращаем управление захватом: мьютекс остаётся занят после выхода из функции.
std::unique_lock<std::mutex> lockInventory(Inventory& inventory)
{
    std::unique_lock<std::mutex> lock(inventory.mtx);
    return lock; // std::move здесь не нужен: возможны перемещение или NRVO.
}

// Принимаем unique_lock по значению: теперь эта функция отвечает за освобождение.
// Предусловие: lock владеет inventory.mtx, а наличие товара уже проверено.
void completeOrder(Inventory& inventory, int orderId, int quantity,
                   std::unique_lock<std::mutex> lock)
{
    assert(lock.owns_lock() && lock.mutex() == &inventory.mtx);
    inventory.available -= quantity;
    std::cout << "Order " << orderId << ": new owner holds lock = "
              << std::boolalpha << lock.owns_lock()
              << "; reserved " << quantity
              << "; remaining " << inventory.available << '\n';
} // Параметр lock уничтожается и освобождает мьютекс.

bool placeOrder(Inventory& inventory, int orderId, int quantity)
{
    auto lock = lockInventory(inventory);
    std::cout << "Order " << orderId << ": checking " << quantity
              << " items; available " << inventory.available << '\n';

    if (quantity <= 0 || inventory.available < quantity)
    {
        std::cout << "Order " << orderId << ": rejected\n";
        return false; // Здесь мьютекс освободит локальный lock.
    }

    // Между проверкой и списанием мьютекс не освобождается: другой заказ ждёт.
    completeOrder(inventory, orderId, quantity, std::move(lock));
    // std::move разрешил перемещение; параметр completeOrder принял владение.
    assert(!lock.owns_lock() && lock.mutex() == nullptr);
    // После передачи inventory.available без нового захвата читать нельзя.
    return true;
} // При успехе локальный lock уже перемещён и ничего не освобождает.

int main()
{
    Inventory inventory;
    bool firstAccepted = false;
    bool secondAccepted = false;

    // Два покупателя хотят по две единицы, а на складе всего три.
    std::thread first([&]() { firstAccepted = placeOrder(inventory, 1, 2); });
    std::thread second([&]() { secondAccepted = placeOrder(inventory, 2, 2); });
    first.join();
    second.join();

    // После join() оба потока завершились: читать остаток можно без захвата.
    const int accepted = static_cast<int>(firstAccepted) + static_cast<int>(secondAccepted);
    std::cout << "Accepted orders: " << accepted << '\n';
    std::cout << "Remaining items: " << inventory.available << '\n';
    return accepted == 1 && inventory.available == 1 ? 0 : 1;
}
