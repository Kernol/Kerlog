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

#define CATCH_CONFIG_MAIN

#include "kerlog.h"
#include "catch.hpp"

//todo: refactor tests
TEST_CASE("Kerlog test")
{
    SECTION("Coverage")
    {
        KERLOG_DEBUG("DEBUG");
        KERLOG_WARNING("WARNING");
        KERLOG_ERROR("ERROR");
        KERLOG_DEBUG_VERBOSE("DEBUG");
        KERLOG_WARNING_VERBOSE("WARNING");
        KERLOG_ERROR_VERBOSE("ERROR");
        KERLOG_SET_FILE_STREAM(Kerlog::LogLevel::Debug, debug);
        KERLOG_DEBUG("FILE DEBUG");
        KERLOG_DISABLE_LOG_LEVEL(Kerlog::LogLevel::Debug);
        KERLOG_DEBUG("NO DEBUG");
        KERLOG_ENABLE_LOG_LEVEL(Kerlog::LogLevel::Debug, std::cout);
        KERLOG_DEBUG("ENABLED DEBUG");
    }
}