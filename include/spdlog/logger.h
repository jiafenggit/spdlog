//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

// Thread safe logger
// Has name, log level, vector of std::shared sink pointers and formatter
// Upon each log write the logger:
// 1. Checks if its log level is enough to log the message
// 2. Format the message using the formatter function
// 3. Pass the formatted message to its sinks to performa the actual logging

#include <spdlog/sinks/base_sink.h>
#include <spdlog/common.h>

#include <vector>
#include <memory>
#include <string>


namespace spdlog
{

class logger
{
public:
    logger(const std::string& logger_name, sink_ptr single_sink);
    logger(const std::string& name, sinks_init_list);
    template<class It>
    logger(const std::string& name, const It& begin, const It& end);

    virtual ~logger();
    logger(const logger&) = delete;
    logger& operator=(const logger&) = delete;

    template <typename... Args> void log(level::level_enum lvl, const char* fmt, const Args&... args);
    template <typename... Args> void log(level::level_enum lvl, const char* msg);

    template <typename T> void log(level::level_enum lvl, const T&);
    template <typename... Args> void trace(const char* fmt, const Args&... args);
    template <typename... Args> void debug(const char* fmt, const Args&... args);
    template <typename... Args> void info(const char* fmt, const Args&... args);
    template <typename... Args> void notice(const char* fmt, const Args&... args);
    template <typename... Args> void warn(const char* fmt, const Args&... args);
    template <typename... Args> void error(const char* fmt, const Args&... args);
    template <typename... Args> void critical(const char* fmt, const Args&... args);
    template <typename... Args> void alert(const char* fmt, const Args&... args);
    template <typename... Args> void emerg(const char* fmt, const Args&... args);


    template <typename T> void trace(const T&);
    template <typename T> void debug(const T&);
    template <typename T> void info(const T&);
    template <typename T> void notice(const T&);
    template <typename T> void warn(const T&);
    template <typename T> void error(const T&);
    template <typename T> void critical(const T&);
    template <typename T> void alert(const T&);
    template <typename T> void emerg(const T&);

    bool should_log(level::level_enum) const;
    void set_level(level::level_enum);
    level::level_enum level() const;
    const std::string& name() const;
    void set_pattern(const std::string&);
    void set_formatter(formatter_ptr);

    // automatically call flush() if message level >= log_level
    void flush_on(level::level_enum log_level);
    virtual void flush();

protected:
    virtual void _sink_it(details::log_msg&);
    virtual void _set_pattern(const std::string&);
    virtual void _set_formatter(formatter_ptr);

    std::string _name;
    std::vector<sink_ptr> _sinks;
    formatter_ptr _formatter;
    spdlog::level_t _level;
    spdlog::level_t _flush_level;
};
}

#include <spdlog/details/logger_impl.h>


