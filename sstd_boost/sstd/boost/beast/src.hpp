//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_SRC_HPP
#define BOOST_BEAST_SRC_HPP

/*

This file is meant to be included once, in a translation unit of
the program, with the macro BOOST_BEAST_SEPARATE_COMPILATION defined.

*/

#define BOOST_BEAST_SOURCE

#include <sstd/boost/beast/core/detail/config.hpp>

#if defined(BOOST_BEAST_HEADER_ONLY)
# error Do not compile Beast library source with BOOST_BEAST_HEADER_ONLY defined
#endif

#include <sstd/boost/beast/_experimental/test/impl/error.ipp>
#include <sstd/boost/beast/_experimental/test/impl/fail_count.ipp>
#include <sstd/boost/beast/_experimental/test/impl/stream.ipp>

#include <sstd/boost/beast/core/detail/base64.ipp>
#include <sstd/boost/beast/core/detail/sha1.ipp>
#include <sstd/boost/beast/core/impl/error.ipp>
#include <sstd/boost/beast/core/impl/file_posix.ipp>
#include <sstd/boost/beast/core/impl/file_stdio.ipp>
#include <sstd/boost/beast/core/impl/file_win32.ipp>
#include <sstd/boost/beast/core/impl/flat_static_buffer.ipp>
#include <sstd/boost/beast/core/impl/saved_handler.ipp>
#include <sstd/boost/beast/core/impl/static_buffer.ipp>

#include <sstd/boost/beast/http/detail/basic_parser.ipp>
#include <sstd/boost/beast/http/detail/rfc7230.ipp>
#include <sstd/boost/beast/http/impl/basic_parser.ipp>
#include <sstd/boost/beast/http/impl/error.ipp>
#include <sstd/boost/beast/http/impl/field.ipp>
#include <sstd/boost/beast/http/impl/rfc7230.ipp>
#include <sstd/boost/beast/http/impl/status.ipp>
#include <sstd/boost/beast/http/impl/verb.ipp>

#include <sstd/boost/beast/websocket/detail/hybi13.ipp>
#include <sstd/boost/beast/websocket/detail/pmd_extension.ipp>
#include <sstd/boost/beast/websocket/detail/prng.ipp>
#include <sstd/boost/beast/websocket/detail/service.ipp>
#include <sstd/boost/beast/websocket/detail/utf8_checker.ipp>
#include <sstd/boost/beast/websocket/impl/error.ipp>

#include <sstd/boost/beast/zlib/detail/deflate_stream.ipp>
#include <sstd/boost/beast/zlib/detail/inflate_stream.ipp>
#include <sstd/boost/beast/zlib/impl/error.ipp>

#endif
