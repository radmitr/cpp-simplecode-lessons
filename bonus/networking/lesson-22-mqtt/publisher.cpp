// C++17 — std::string_view; MQTT 3.1.1 — внешний сетевой протокол.
#include "mqtt.hpp"
#include "../../../common/console.hpp"

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();
    try
    {
        net::Runtime runtime;
        auto socket = mqtt::connect(net::portArgument(argc, argv, 1883), "lesson-publisher");
        mqtt::send(socket, 0x30, mqtt::field(mqtt::topic) + "23.5");
        mqtt::send(socket, 0xE0);
        std::cout << "Published QoS 0: " << mqtt::topic << " = 23.5\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}
