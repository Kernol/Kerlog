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

#include "kerlog.h"

Kerlog::Logger Kerlog::defaultLogger;

Kerlog::Stream::Stream() : _stream(&std::cout), _enabled(true) {}

Kerlog::Stream::Stream(std::ostream* stream) : _stream(stream), _enabled(true) {}

Kerlog::Stream::~Stream()
{
    _stream = nullptr;
}

void Kerlog::Stream::setStream(std::ostream &stream)
{
    _stream = &stream;
    _enabled = true;
}

void Kerlog::Stream::printMessage(const std::string& function, const std::string& message) const
{
    *_stream << function << ": " << message << std::endl;
}

void Kerlog::Stream::disable()
{
    _stream = nullptr;
    _enabled = false;
}

bool Kerlog::Stream::isEnabled() const
{
    return _enabled;
}

Kerlog::Logger::Logger() : _streams(3, &std::cout) {}

Kerlog::Errors Kerlog::Logger::disableLogLevel(LogLevel logLevel)
{
    if(logLevel >= 3)
        return WrongLogLevel;
    _streams[logLevel].disable();
    return Success;
}

Kerlog::Errors Kerlog::Logger::setStream(LogLevel logLevel, std::ostream& stream)
{
    if(logLevel >= 3)
        return WrongLogLevel;
    _streams[logLevel].setStream(stream);
    return Success;
}

void Kerlog::Logger::printMessage(LogLevel logLevel, const std::string& function, const std::string& message) const
{
    if(_streams[logLevel].isEnabled())
        _streams[logLevel].printMessage(function, message);
}