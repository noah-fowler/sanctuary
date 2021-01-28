#include <sanctuary/filesystem/text_file.hpp>
#include <sanctuary/utility/algorithms.hpp>


namespace snc {

TextFile::TextFile(const String& path, Logger* logger) {
    read(path, logger);
}

TextFile::operator bool() const {
    return !_error;
}

TextFile::operator const String&() const {
    return _buffer;
}

bool TextFile::read(const String& path, Logger* logger) {
    auto stream = std::ifstream{ static_cast<std::string>(path) };
    if (!stream) {
        if (logger)
            logger->error("Failed to read text file: {}", path);
        return {};
    }
    const auto len = stream.seekg(0, std::ios::end).tellg();
    auto temp = std::string(static_cast<size_t>(len), ' ');
    stream.seekg(0, std::ios::beg);
    stream.read(&temp[0], len);
    _buffer = String(temp);
    return true;
}

bool TextFile::write(const String& path, Logger* logger) {
    return {};
}

bool TextFile::empty() const {
    return _buffer.empty();
}

auto TextFile::lines() const -> size_t {
    return snc::count(_buffer, '\n');
}

auto TextFile::line(size_t idx) const -> String {
    return {};
}

}
