﻿
// Copyright 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <sstd/boost/iostreams/device/file.hpp>
#include <sstd/boost/iostreams/filter/gzip.hpp>
#include <sstd/boost/iostreams/device/back_inserter.hpp>
#include <sstd/boost/iostreams/copy.hpp>
#include <sstd/boost/iostreams/compose.hpp>
#include <sstd/boost/core/lightweight_test.hpp>

namespace io = boost::iostreams;

int main()
{
    io::file_source fs( "test.txt.gz", std::ios_base::binary );
    io::gzip_decompressor gz;

    std::string s;
    io::copy( io::compose( gz, fs ), io::back_inserter( s ) );

    BOOST_TEST( s == "=== reference output ===" );

    return boost::report_errors();
}
