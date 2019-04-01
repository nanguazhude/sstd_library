﻿/*
 *             Copyright Andrey Semashev 2018.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   dbghelp_abi.cpp
 * \author Andrey Semashev
 * \date   09.03.2018
 *
 * \brief  This file contains ABI test for dbghelp.hpp
 */

#include <sstd/boost/winapi/dbghelp.hpp>
#include <windows.h>
#if !defined(BOOST_WINAPI_IS_MINGW)
#include <dbghelp.h>
#else
#include <imagehlp.h>
#endif
#include "abi_test_tools.hpp"

int main()
{
#if BOOST_WINAPI_PARTITION_DESKTOP

    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_COMPLETE);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_LEADING_UNDERSCORES);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_MS_KEYWORDS);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_FUNCTION_RETURNS);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_ALLOCATION_MODEL);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_ALLOCATION_LANGUAGE);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_MS_THISTYPE);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_CV_THISTYPE);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_THISTYPE);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_ACCESS_SPECIFIERS);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_THROW_SIGNATURES);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_MEMBER_TYPE);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_RETURN_UDT_MODEL);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_32_BIT_DECODE);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NAME_ONLY);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_ARGUMENTS);
    BOOST_WINAPI_TEST_CONSTANT(UNDNAME_NO_SPECIAL_SYMS);

    BOOST_WINAPI_TEST_STRUCT(API_VERSION, (MajorVersion)(MinorVersion)(Revision));

#endif // BOOST_WINAPI_PARTITION_DESKTOP

    return boost::report_errors();
}
