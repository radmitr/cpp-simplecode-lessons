// C++17 — string_view; MQTT 3.1.1 — QoS 1 PUBLISH/PUBACK и дедупликация приложения.
#include <cstdint>
#include <exception>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>

#include "../../../basics/additions/common/check.hpp"

std::uint16_t puback(std::string_view packet)
{
    if (packet.size() != 4 || static_cast<unsigned char>(packet[0]) != 0x40
        || static_cast<unsigned char>(packet[1]) != 2) throw std::invalid_argument("bad PUBACK");
    const auto id = static_cast<std::uint16_t>((static_cast<unsigned char>(packet[2]) << 8)
        | static_cast<unsigned char>(packet[3]));
    if (id == 0) throw std::invalid_argument("zero packet identifier");
    return id;
}
int main()
{
    try
    {
        // Фиксированная часть PUBACK: тип/флаги, Remaining Length, Packet Identifier.
        const std::string ack("\x40\x02\x00\x07", 4);
        check(puback(ack) == 7, "PUBACK id");
        bool rejected = false;
        try { puback(std::string("\x40\x02\x00\x00", 4)); }
        catch (const std::invalid_argument&) { rejected = true; }
        check(rejected, "zero id rejected");
        std::set<std::string> processed;
        int changes = 0;
        for (const auto operation : {"order-42", "order-42", "order-43"})
            if (processed.insert(operation).second) ++changes;
        check(changes == 2, "business deduplication");
        std::cout << "PUBACK=7; operations=2\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
