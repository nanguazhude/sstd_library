﻿/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   common.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * This header includes other Boost.Log headers that are commonly used in logging applications.
 * Note that the header does not include any headers required to setup the library, as usually
 * they aren't needed in more than one translation unit of the application.
 */

#ifndef BOOST_LOG_COMMON_HPP_INCLUDED_
#define BOOST_LOG_COMMON_HPP_INCLUDED_

#include <sstd/boost/log/detail/config.hpp>

#include <sstd/boost/log/core.hpp>

#include <sstd/boost/log/sources/global_logger_storage.hpp>
#include <sstd/boost/log/sources/record_ostream.hpp>

#include <sstd/boost/log/sources/basic_logger.hpp>
#include <sstd/boost/log/sources/severity_logger.hpp>
#include <sstd/boost/log/sources/channel_logger.hpp>
#include <sstd/boost/log/sources/severity_channel_logger.hpp>
#include <sstd/boost/log/sources/exception_handler_feature.hpp>

#include <sstd/boost/log/attributes/constant.hpp>
#include <sstd/boost/log/attributes/named_scope.hpp>
#include <sstd/boost/log/attributes/scoped_attribute.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_COMMON_HPP_INCLUDED_
