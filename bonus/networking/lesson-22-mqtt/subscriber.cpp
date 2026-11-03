// C++17 — std::string_view; MQTT 3.1.1 — внешний сетевой протокол.
#include "mqtt.hpp"
#include "../../../common/console.hpp"

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();
    try
    {
        net::Runtime runtime;
        auto socket = mqtt::connect(net::portArgument(argc, argv, 1883), "lesson-subscriber");
        std::string subscription("\x00\x01", 2); // Packet Identifier = 1.
        subscription += mqtt::field(mqtt::topic);
        subscription += '\0'; // Запрошен QoS 0.
        mqtt::send(socket, 0x82, subscription);
        const auto ack = mqtt::receive(socket);
        if (ack.header != 0x90 || ack.body != std::string("\x00\x01\x00", 3))
            throw std::runtime_error("Неверный SUBACK или подписка отклонена");
        std::cout << "Subscribed: " << mqtt::topic << std::endl;
        const auto packet = mqtt::receive(socket, std::chrono::seconds(30));
        const auto prefix = mqtt::field(mqtt::topic);
        if (packet.header != 0x30 || packet.body.compare(0, prefix.size(), prefix) != 0)
            throw std::runtime_error("Ожидался PUBLISH без retain с QoS 0 в нужную тему");
        std::cout << "Received: " << packet.body.substr(prefix.size()) << '\n';
        mqtt::send(socket, 0xE0); // DISCONNECT: брокер не присылает подтверждение.
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}
