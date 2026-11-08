// C++17 — string_view; MQTT 3.1.1 — QoS 1 PUBLISH и PUBACK.
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "../28-mqtt/mqtt.hpp"
#include "../common/net.hpp"

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto socket = mqtt::connect(net::portArgument(argc, argv, 1883), "qos1-demo");
        std::string body = mqtt::field("lesson/qos1");
        body.append("\x00\x07", 2);
        body += "operation=order-42";
        mqtt::send(socket, 0x32, body);
        const auto ack = mqtt::receive(socket);
        if (ack.header != 0x40 || ack.body != std::string("\x00\x07", 2))
            throw std::runtime_error("expected PUBACK id 7");
        mqtt::send(socket, 0xe0);
        std::cout << "PUBACK=7\nOK reference-example\n";
    }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
