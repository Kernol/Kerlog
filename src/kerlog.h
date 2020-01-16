// Kerlog. Logger program
// Copyright (C) 2020 Evgeny Zaytsev
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef KERLOG_LIBRARY_H
#define KERLOG_LIBRARY_H

#include <iostream>
#include <fstream>
#include <vector>

#define KERLOG_DEBUG(message) Kerlog::defaultLogger.printMessage(Kerlog::LogLevel::Debug, __FUNCTION__, message)
#define KERLOG_DEBUG_VERBOSE(message)\
    Kerlog::defaultLogger.printMessage(Kerlog::LogLevel::Debug, __PRETTY_FUNCTION__, message)
#define KERLOG_WARNING(message) Kerlog::defaultLogger.printMessage(Kerlog::LogLevel::Warning, __FUNCTION__, message)
#define KERLOG_WARNING_VERBOSE(message)\
    Kerlog::defaultLogger.printMessage(Kerlog::LogLevel::Warning, __PRETTY_FUNCTION__, message)
#define KERLOG_ERROR(message) Kerlog::defaultLogger.printMessage(Kerlog::LogLevel::Error, __FUNCTION__, message)
#define KERLOG_ERROR_VERBOSE(message)\
    Kerlog::defaultLogger.printMessage(Kerlog::LogLevel::Error, __PRETTY_FUNCTION__, message)

    //todo: improve
#define KERLOG_SET_FILE_STREAM(logLevel, filename)\
    std::ofstream filename##Stream;\
    filename##Stream.open(#filename".txt");\
    Kerlog::defaultLogger.setStream(logLevel, filename##Stream)

#define KERLOG_DISABLE_LOG_LEVEL(logLevel) Kerlog::defaultLogger.disableLogLevel(logLevel)
#define KERLOG_ENABLE_LOG_LEVEL(logLevel, stream) Kerlog::defaultLogger.setStream(logLevel, stream)

namespace Kerlog
{
    enum Errors
    {
        Success = 0,
        WrongLogLevel = 1
    };

    enum LogLevel
    {
        Debug = 0,
        Warning = 1,
        Error = 2
    };

    class Stream
    {
        std::ostream* _stream; //todo: shared/unique ptr
        bool _enabled;

    public:
        Stream();
        Stream(std::ostream* stream);
        ~Stream();
        void setStream(std::ostream &stream);
        void printMessage(const std::string& function, const std::string& message) const;
        void disable();
        inline bool isEnabled() const;
    };

    class Logger
    {
        std::vector<Stream> _streams;
    public:
        Logger();
        ~Logger() = default;
        Errors disableLogLevel(LogLevel logLevel);
        Errors setStream(LogLevel logLevel, std::ostream& stream);
        void printMessage(LogLevel logLevel, const std::string& function, const std::string& message) const;
    };

    extern Logger defaultLogger;
}

#endif