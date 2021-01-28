#pragma once
#include <fstream>

#include <sanctuary/io/console.hpp>
#include <sanctuary/utility/string.hpp>
#include <sanctuary/utility/format.hpp>


namespace snc {

struct LogType {
    struct Info {
        static constexpr const char* format = "INFO: {}\n";
    };

    struct Debug {
        static constexpr const char* format = "DEBUG: {}\n";
    };

    struct Warning {
        static constexpr const char* format = "WARNING: {}\n";
    };

    struct Error {
        static constexpr const char* format = "ERROR: {}\n";
    };
};

template<class T>
concept LogLevel = requires {
    { T::format };
};


class Logger {
private:
    String        _buffer  {};
    std::ofstream _stream  {};
    bool          _verbose {};
    bool          _error   {};

    inline bool should_flush(size_t offset) const {
        return (_buffer.length() + offset) >= 1024;
    }

public:
    Logger(const String& path, bool verbose = true)
        : _stream(static_cast<std::string>(path))
        , _verbose(verbose)
    {
        _buffer.reserve(1024);
    }

    ~Logger() {
        flush();
    }

    inline explicit operator const String&() const {
        return _buffer;
    }

    template<LogLevel type = LogType::Info, class... Args>
    void log(const String& str, Args&&... args) {
        const auto msg = snc::format(str, std::forward<Args>(args)...);
        const auto res = snc::format(type::format, msg);
        if (should_flush(res.length()))
            flush();
        if (_verbose)
            snc::print(res);
        _buffer.append(res);
    }

    template<class... Args>
    void debug(const String& fmt, Args&&... args) {
        log<LogType::Debug>(fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    void warn(const String& fmt, Args&&... args) {
        log<LogType::Warning>(fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    void error(const String& fmt, Args&&... args) {
        log<LogType::Error>(fmt, std::forward<Args>(args)...);
    }

    inline void flush() {
        if (!_stream.is_open())
            return;
        _stream << _buffer;
        _stream.flush();
        _buffer.clear();
    }

    void set_verbose(bool enabled = true) {
        _verbose = enabled;
    }
};

}
