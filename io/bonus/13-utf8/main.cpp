#include <string>
#include <string_view>
#include <cstdint>
#include "../common/check.hpp"

bool valid_utf8(std::string_view text) {
    std::size_t i=0;
    while(i<text.size()) {
        const auto first=static_cast<unsigned char>(text[i++]);
        if(first<0x80) continue;
        unsigned count=0; std::uint32_t value=0,minimum=0;
        if(first>=0xc2 && first<=0xdf) {count=1;value=first&0x1f;minimum=0x80;}
        else if(first>=0xe0 && first<=0xef) {count=2;value=first&0x0f;minimum=0x800;}
        else if(first>=0xf0 && first<=0xf4) {count=3;value=first&7;minimum=0x10000;}
        else return false;
        if(text.size()-i<count) return false;
        for(unsigned n=0;n<count;++n) {
            const auto next=static_cast<unsigned char>(text[i++]);
            if((next&0xc0)!=0x80) return false;
            value=(value<<6)|(next&0x3f);
        }
        if(value<minimum || value>0x10ffff || (value>=0xd800 && value<=0xdfff)) return false;
    }
    return true;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        const std::u8string_view unicode=u8"ёж";
        const std::string bytes(reinterpret_cast<const char*>(unicode.data()),unicode.size());
        check(bytes.size()==4 && valid_utf8(bytes),"UTF-8 encoding mismatch");
        check(!valid_utf8(std::string("\xc0\xaf",2)),"overlong UTF-8 accepted");
        check(!valid_utf8(std::string("\xed\xa0\x80",3)),"surrogate UTF-8 accepted");
        check(!valid_utf8(std::string("\xf4\x90\x80\x80",4)),"out-of-range code point accepted");
        check(!valid_utf8(std::string("\xe2\x82",2)),"truncated UTF-8 accepted");
        std::string text="\xef\xbb\xbfline1\r\nline2\n";
        text.erase(0,3);
        std::string normalized;
        for(std::size_t i=0;i<text.size();++i) {
            if(text[i]=='\r' && i+1<text.size() && text[i+1]=='\n') continue;
            normalized+=text[i];
        }
        check(normalized=="line1\nline2\n","line normalization failed");
        std::cout << "UTF-8 validation and CRLF normalization verified\n";
        std::cout << "OK 13-utf8\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
