#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>
#include "../common/check.hpp"

struct Record {std::uint32_t id; std::string name;};
using Bytes=std::vector<unsigned char>;
std::uint32_t checksum(const Bytes& bytes,std::size_t count) {
    std::uint32_t hash=2166136261u;
    for(std::size_t i=0;i<count;++i) hash=(hash^bytes[i])*16777619u;
    return hash;
}
void put(Bytes& bytes,std::uint32_t value) {for(unsigned i=0;i<4;++i) bytes.push_back(static_cast<unsigned char>(value>>(8*i)));}
std::uint32_t take(const Bytes& bytes,std::size_t& offset,std::size_t end) {
    if(offset>end || end-offset<4) throw std::runtime_error("truncated integer");
    std::uint32_t value=0; for(unsigned i=0;i<4;++i) value|=std::uint32_t(bytes[offset++])<<(8*i);
    return value;
}
Bytes encode_records(const std::vector<Record>& records) {
    if(records.size()>1000) throw std::runtime_error("too many records");
    Bytes bytes{'R','E','C','2'}; put(bytes,static_cast<std::uint32_t>(records.size()));
    for(const auto& record:records) {
        if(record.name.size()>4096) throw std::runtime_error("name too long");
        put(bytes,record.id);put(bytes,static_cast<std::uint32_t>(record.name.size()));
        bytes.insert(bytes.end(),record.name.begin(),record.name.end());
    }
    put(bytes,checksum(bytes,bytes.size())); return bytes;
}
std::vector<Record> decode_records(const Bytes& bytes) {
    if(bytes.size()<12 || std::string(bytes.begin(),bytes.begin()+4)!="REC2") throw std::runtime_error("unknown format");
    const auto end=bytes.size()-4; auto checkOffset=end;
    if(take(bytes,checkOffset,bytes.size())!=checksum(bytes,end)) throw std::runtime_error("checksum mismatch");
    std::size_t offset=4;const auto count=take(bytes,offset,end);
    if(count>1000) throw std::runtime_error("too many records");
    std::vector<Record> result;
    for(std::uint32_t i=0;i<count;++i) {
        const auto id=take(bytes,offset,end);const auto length=take(bytes,offset,end);
        if(length>4096 || length>end-offset) throw std::runtime_error("invalid name length");
        result.push_back({id,std::string(bytes.begin()+offset,bytes.begin()+offset+length)});offset+=length;
    }
    if(offset!=end) throw std::runtime_error("trailing bytes");
    return result;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        const std::vector<Record> source{{7,"Ada"},{9,"Bob"}};
        const auto bytes=encode_records(source);
        const auto restored=decode_records(bytes);
        check(restored.size()==2 && restored[1].name=="Bob" && restored[0].id==7,"record round trip failed");
        auto damaged=bytes; damaged[8]^=1;
        bool rejected=false;
        try {(void)decode_records(damaged);} catch(const std::runtime_error&) {rejected=true;}
        check(rejected,"corrupted checksum accepted");
        rejected=false;
        try {(void)decode_records(std::vector<unsigned char>{'R','E','C','2'});} catch(const std::runtime_error&) {rejected=true;}
        check(rejected,"truncated record accepted");
        std::cout << "versioned records round trip; corruption rejected\n";
        std::cout << "OK 16-versioned-records\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
