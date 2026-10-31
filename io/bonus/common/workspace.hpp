#pragma once
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

// Только этот объект владеет созданной им временной папкой.
class LessonWorkspace
{
public:
    LessonWorkspace()
    {
        const char* supplied = std::getenv("CPP_LESSON_WORK_DIR");
        base_ = std::filesystem::weakly_canonical(supplied ? std::filesystem::path(supplied)
                                                        : std::filesystem::temp_directory_path());
        const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
        for (int attempt = 0; attempt < 100; ++attempt)
        {
            const auto candidate = base_ / ("cpp-lesson-" + std::to_string(stamp) + '-' + std::to_string(attempt));
            if (std::filesystem::create_directory(candidate)) { directory_ = candidate; return; }
        }
        throw std::runtime_error("Cannot create lesson workspace");
    }
    LessonWorkspace(const LessonWorkspace&) = delete;
    LessonWorkspace& operator=(const LessonWorkspace&) = delete;
    ~LessonWorkspace()
    {
        // Проверяем абсолютный путь и владение перед рекурсивной очисткой.
        if (!directory_.empty() && directory_.is_absolute() && directory_.parent_path() == base_
            && directory_.filename().string().rfind("cpp-lesson-", 0) == 0)
        {
            std::error_code ignored;
            std::filesystem::remove_all(directory_, ignored);
        }
    }
    const std::filesystem::path& path() const { return directory_; }
private:
    std::filesystem::path base_;
    std::filesystem::path directory_;
};

inline void write_text(const std::filesystem::path& path, const std::string& text)
{
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    if (!output.write(text.data(), static_cast<std::streamsize>(text.size())))
        throw std::runtime_error("Cannot write text");
    output.close();
    if (!output) throw std::runtime_error("Cannot close output");
}
inline std::string read_text(const std::filesystem::path& path)
{
    std::ifstream input(path, std::ios::binary);
    if (!input) throw std::runtime_error("Cannot open text");
    std::string result((std::istreambuf_iterator<char>(input)), {});
    if (input.bad()) throw std::runtime_error("Cannot read text");
    return result;
}
