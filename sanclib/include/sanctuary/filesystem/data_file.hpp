#pragma once

#include <sanctuary/utility/string.hpp>
#include <sanctuary/utility/logger.hpp>
#include <sanctuary/containers/list.hpp>
#include <sanctuary/containers/map.hpp>


namespace snc {

struct DataEntry {
    String data{};
};


struct DataKey {
    String name{};
    List<DataEntry> entries{};
};


class DataFile {
private:
    List<DataKey> _keys{};
    bool _error{};

public:
    DataFile()                    = default;
    DataFile(const DataFile&)     = default;
    DataFile(DataFile&&) noexcept = default;
    DataFile& operator =(const DataFile&)     = default;
    DataFile& operator =(DataFile&&) noexcept = default;

    DataFile(const String&, Logger* = nullptr);

    operator bool() const;

    bool load(const String&, Logger* = nullptr);
    bool save(const String&, Logger* = nullptr);

    bool contains(const String&) const;
    bool set(const String& key);

    template<class T>
    auto get(const String&) const -> T;
};

}
