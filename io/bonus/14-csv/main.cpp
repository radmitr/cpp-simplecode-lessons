#include <vector>
#include <string>
#include <string_view>
#include "../common/check.hpp"

using Rows=std::vector<std::vector<std::string>>;
Rows parse_csv(std::string_view text) {
    Rows rows; std::vector<std::string> row; std::string field;
    bool quoted=false,closed=false,pending=false;
    auto finish_field=[&]{row.push_back(field);field.clear();closed=false;};
    auto finish_row=[&]{finish_field();rows.push_back(row);row.clear();pending=false;};
    for(std::size_t i=0;i<text.size();++i) {
        const char c=text[i]; pending=true;
        if(quoted) {
            if(c=='"') {
                if(i+1<text.size() && text[i+1]=='"') {field+='"';++i;}
                else {quoted=false;closed=true;}
            } else field+=c;
            continue;
        }
        if(c==',') {finish_field();continue;}
        if(c=='\n' || c=='\r') {
            if(c=='\r' && i+1<text.size() && text[i+1]=='\n') ++i;
            finish_row(); continue;
        }
        if(closed) throw std::invalid_argument("data after closing quote");
        if(c=='"') {
            if(!field.empty()) throw std::invalid_argument("quote inside unquoted field");
            quoted=true;
        } else field+=c;
    }
    if(quoted) throw std::invalid_argument("unclosed quote");
    if(pending) finish_row();
    return rows;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        const auto rows=parse_csv("id,name\r\n1,\"Ada, A\"\r\n2,\"line1\nline2\"\n3,\"a\"\"b\"\n4,\n");
        check(rows.size()==5 && rows[1][1]=="Ada, A" && rows[2][1]=="line1\nline2","CSV quoted fields failed");
        check(rows[3][1]=="a\"b" && rows[4][1].empty(),"CSV escaping or empty field failed");
        check(parse_csv("").empty(),"empty CSV must have no records");
        for(const auto& invalid:{"a\"b,c", "\"unfinished", "\"closed\"extra"}) {
            bool rejected=false;
            try {(void)parse_csv(invalid);} catch(const std::invalid_argument&) {rejected=true;}
            check(rejected,"malformed CSV accepted");
        }
        std::cout << "quoted commas, newlines, empty fields and escaped quotes verified\n";
        std::cout << "OK 14-csv\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
