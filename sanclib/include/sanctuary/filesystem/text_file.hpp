#pragma once
#include <fstream>

#include <sanctuary/utility/string.hpp>
#include <sanctuary/utility/logger.hpp>


namespace snc {

class TextFile {
private:
    String _buffer {};
    bool   _error  {};

public:
    TextFile()                    = default;
    TextFile(const TextFile&)     = default;
    TextFile(TextFile&&) noexcept = default;

    TextFile(const String& path, Logger* logger = nullptr);

    operator bool() const;
    operator const String&() const;

    bool read(const String& path, Logger* logger = nullptr);
    bool write(const String& path, Logger* logger = nullptr);

    bool empty() const;

    auto lines() const -> size_t;
    auto line(size_t idx) const -> String;
};

}
