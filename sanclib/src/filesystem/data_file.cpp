#include <sanctuary/filesystem/data_file.hpp>
#include <fstream>


namespace snc {

inline bool is_section(const String& str) {
    return str.ends_with(":");
}

inline bool is_entry(const String& str) {
    return str.substr(str.mismatch(" ")).starts_with("- ");
}

inline bool is_key(const String& str) {
    return str.contains(": ");
}

DataFile::DataFile(const String& path, Logger* logger) {
    load(path, logger);
}

DataFile::operator bool() const {
    return !_error;
}

bool DataFile::load(const String& path, Logger* logger) {
    auto stream = std::ifstream{ static_cast<std::string>(path) };
    if (!stream.is_open()) {
        if (logger)
            logger->error("Failed to open DataFile: {}", path);
        _error = true;
        return false;
    }
    auto stack = Map<size_t, DataKey>{};
    auto line = String{};
    size_t row = 0u;
    size_t col = 0u;

    auto id = [&] {
    };

    auto pop = [&]() {
        while (!stack.empty() && stack.back().first <= col)
            stack.pop_back();
    };

    auto push_key = [&](DataKey&& key) {
        pop();
        stack[col] = std::move(key);
    };

    auto push_entry = [&](DataEntry&& entry) {
        pop();
        if (stack.empty()) {
            if (logger)
                logger->error("{}:{} - {}\n--- Found entry with no scope ", row, col, path);
            _error = true;
            return;
        }
        stack.back().second.entries.emplace_back(entry);
    };

    while (std::getline(stream, static_cast<std::string&>(line))) {
        ++row;
        col = line.mismatch(" ");
        if (col == String::npos)
            continue;
        else if (is_entry(line))
            push_entry(DataEntry{ line.substr(col + 2) });
        else if (is_section(line))
            push_key(DataKey{ line.substr(col, line.length() - col - 1) });
        else if (is_key(line)) {
            const size_t delim = line.match(": ");
            push_key(DataKey{ line.substr(col, delim - col) });
            push_entry(DataEntry{ line.substr(delim + 2) });
        }
        else {
            if (logger)
                logger->error("{}:{} - {}\n--- Unknown line type", row, col, path);
            _error = true;
        }
    }
    return !_error;
}

bool DataFile::save(const String& path, Logger* logger) {
    return {};
}

bool DataFile::contains(const String& key) const {
    return {};
}

bool DataFile::set(const String& key) {
    return {};
}

template<class T>
auto DataFile::get(const String& key) const -> T {
    return T{};
}

}
