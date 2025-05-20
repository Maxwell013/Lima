#pragma once

#include <cstddef>
#include <ctime>
#include <iostream>
#include <sstream>
#include <unordered_map>

#define LOG_TRACE(...) lm::Logger::Main.log(lm::LogType::Trace, __VA_ARGS__)
#define LOG_DEBUG(...) lm::Logger::Main.log(lm::LogType::Debug, __VA_ARGS__)
#define LOG_INFO(...) lm::Logger::Main.log(lm::LogType::Info, __VA_ARGS__)
#define LOG_WARNING(...) lm::Logger::Main.log(lm::LogType::Warning, __VA_ARGS__)
#define LOG_ERROR(...) lm::Logger::Main.log(lm::LogType::Error, __VA_ARGS__)
#define LOG_FATAL(...) lm::Logger::Main.log(lm::LogType::Fatal, __VA_ARGS__)

#define LIMA_SET_FLAG(...) lm::Logger::Main.setFlag(__VA_ARGS__)
#define LIMA_CLEAR_FLAG(...) lm::Logger::Main.clearFlag(__VA_ARGS__)
#define LIMA_SET_FILTER(...) lm::Logger::Main.setFilter(__VA_ARGS__)
#define LIMA_CLEAR_FILTER(...) lm::Logger::Main.clearFilter(__VA_ARGS__)

namespace lm {

    typedef unsigned int flag;

    namespace flags {
        inline const flag TIMESTAMPS_PREFIX   = 1 << 0;
        inline const flag LOGTYPES_PREFIX     = 1 << 1;
        inline const flag WHITESPACE_PREFIX   = 1 << 2;
        inline const flag LOGTAG_PREFIX       = 1 << 3;
        inline const flag LOGTYPE_COLORS      = 1 << 4;
        inline const flag LOGTYPE_FILTER      = 1 << 5;
        inline const flag LOGTAG_FILTER       = 1 << 6;
        inline const flag WHITELIST_FILTER    = 1 << 7;
        inline const flag END_OF_LINE_SUFFIX  = 1 << 8;

        inline const flag DEFAULTS =
            TIMESTAMPS_PREFIX    |
            LOGTYPES_PREFIX      |
            WHITESPACE_PREFIX    |
            LOGTAG_PREFIX        |
            LOGTYPE_COLORS       |
            LOGTYPE_FILTER       |
            LOGTAG_FILTER        |
            END_OF_LINE_SUFFIX;
    };

    enum class LogType { Trace, Debug, Info, Warning, Error, Fatal, LogTypeCount };

    inline std::string str(const LogType p_logType) {
        switch (p_logType) {
            case LogType::Trace:
                return "[Trace]";
            case LogType::Debug:
                return "[Debug]";
            case LogType::Info:
                return "[Info]";
            case LogType::Warning:
                return "[Warning]";
            case LogType::Error:
                return "[Error]";
            case LogType::Fatal:
                return "[Fatal]";
            default:
                return "";
        }
    }

    inline std::ostream& operator<<(std::ostream& p_ostream, const LogType p_logType) { return p_ostream << str(p_logType); }

    class Logger {

    public:
        static Logger& Main;

        Logger(const std::string& p_logTag, const flag p_flags)
            : m_logTag(p_logTag), m_flags(p_flags) {
                s_logTagFilter[p_logTag] = false;
            }

    private:
        inline static bool s_logTypeFilter[(size_t)LogType::LogTypeCount] = { false };
        inline static std::unordered_map<std::string, bool> s_logTagFilter = {};
        const std::string m_logTag;
        flag m_flags;

        bool isFlagSet(flag p_flag) const { return (0 != (m_flags & p_flag)); }

        std::string prefix(LogType p_logType) const {
            std::ostringstream stream;

            if (isFlagSet(flags::LOGTYPE_COLORS))
                stream << color(p_logType);

            if (isFlagSet(flags::TIMESTAMPS_PREFIX))
                stream << timestamp();

            if (isFlagSet(flags::LOGTYPES_PREFIX))
                stream << p_logType;

            if (isFlagSet(flags::LOGTAG_PREFIX))
                stream << "[" << m_logTag << "]";

            if (isFlagSet(flags::WHITESPACE_PREFIX))
                stream << "    ";

            return stream.str();
        }

        std::string suffix() const {
            std::ostringstream stream;

            if (isFlagSet(flags::LOGTYPE_COLORS))
                stream << "\033[0m";

            if (isFlagSet(flags::END_OF_LINE_SUFFIX))
                stream << std::endl;

            return stream.str();
        }

        template<typename Type>
        static std::string fmt(const Type p_arg) {
            std::ostringstream stream;
            stream << p_arg;
            return stream.str();
        }

        template<typename Type, typename... Types>
        static std::string fmt(const Type p_arg, const Types... p_args) {
            std::ostringstream stream;
            stream << p_arg << fmt(p_args...);
            return stream.str();
        }

        void output(LogType p_logType, std::string p_message) const {
            if (isFlagSet(flags::LOGTYPE_FILTER) && filter(p_logType)) return;
            if (isFlagSet(flags::LOGTAG_FILTER) && filter()) return;
            std::cout << p_message;
        }

        bool filter(LogType p_logType) const { return isFlagSet(flags::WHITELIST_FILTER) != s_logTypeFilter[(size_t)p_logType]; }

        bool filter() const { return isFlagSet(flags::WHITELIST_FILTER) != s_logTagFilter[m_logTag]; }

        static std::string color(LogType p_logType) {
            switch (p_logType) {
                case LogType::Trace:
                    return "\033[0m";
                case LogType::Debug:
                    return "\033[32m";
                case LogType::Info:
                    return "\033[34m";
                case LogType::Warning:
                    return "\033[33m";
                case LogType::Error:
                    return "\033[31m";
                case LogType::Fatal:
                    return "\033[37;41m";
                default:
                    return "\033[0m";
            }
        }

        static std::string timestamp() {
            const std::time_t time = std::time(nullptr);
            char buffer[12];
            std::tm bt {};

            #ifdef LIMA_WINDOWS
                localtime_s(&bt, &time);
            #else
                localtime_r(&time, &bt);
            #endif
            return std::string(buffer, std::strftime(buffer, sizeof(buffer), "[%T]", &bt));
        }

    public:
        template<typename... Types>
        void log(const LogType p_logType, const Types... p_args) const {
            std::ostringstream stream;
            stream << prefix(p_logType) << fmt(p_args...) << suffix();
            output(p_logType, stream.str());
        }

        void setFlag(flag p_flag) { m_flags |= p_flag; }

        void clearFlag(flag p_flag) { m_flags &= ~p_flag; }

        static void setFilter(LogType p_logType) { s_logTypeFilter[(size_t)p_logType] = true; }

        static void setFilter(std::string p_logTag) { s_logTagFilter[p_logTag] = true; }

        static void clearFilter(LogType p_logType) { s_logTypeFilter[(int)p_logType] = false; }

        static void clearFilter(std::string p_logTag) { s_logTagFilter[p_logTag] = false; }
    };

    inline Logger& Logger::Main = *new Logger("LIMA", lm::flags::DEFAULTS);
} // namespace lm
