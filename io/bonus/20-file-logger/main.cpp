#include <chrono>
#include <cstdint>
#include <utility>
#include "../common/check.hpp"

#include "../common/workspace.hpp"
class Logger {
public:
    Logger(std::filesystem::path file,std::uintmax_t limit):file_(std::move(file)),limit_(limit){}
    void log(const std::string& level,const std::string& message) {
        if(message.find_first_of("\r\n")!=std::string::npos || level.find_first_of("\r\n")!=std::string::npos)
            throw std::invalid_argument("multiline log entry");
        const auto seconds=std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        const auto line="["+std::to_string(seconds)+"] "+level+" "+message+"\n";
        if(line.size()>limit_) throw std::invalid_argument("entry too large");
        if(std::filesystem::exists(file_) && std::filesystem::file_size(file_)+line.size()>limit_) {
            auto previous=file_;previous+=".1";
            std::error_code ignored;std::filesystem::remove(previous,ignored);
            std::filesystem::rename(file_,previous);
        }
        std::ofstream out(file_,std::ios::app|std::ios::binary);
        out << line;out.close();if(!out) throw std::runtime_error("log write failed");
    }
private:std::filesystem::path file_;std::uintmax_t limit_;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        LessonWorkspace work;const auto path=work.path()/"application.log";
        Logger logger(path,80);
        for(int i=0;i<6;++i) logger.log("INFO","event "+std::to_string(i));
        check(std::filesystem::exists(path) && std::filesystem::exists(path.parent_path()/"application.log.1"),"rotation did not happen");
        check(std::filesystem::file_size(path)<=80,"log size exceeded");
        check(read_text(path).find("event 5")!=std::string::npos,"latest event missing");
        bool rejected=false;
        try {logger.log("INFO",std::string(100,'x'));} catch(const std::invalid_argument&) {rejected=true;}
        check(rejected,"oversized entry accepted");
        std::cout << "bounded log rotated and latest entry preserved\n";
        std::cout << "OK 20-file-logger\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
