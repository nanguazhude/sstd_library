﻿/*
 *             Copyright Andrey Semashev 2018.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   file_mapping_abi.cpp
 * \author Andrey Semashev
 * \date   10.03.2018
 *
 * \brief  This file contains ABI test for file_mapping.hpp
 */

#include <sstd/boost/winapi/file_mapping.hpp>
#include <windows.h>
#include "abi_test_tools.hpp"

int main()
{
    BOOST_WINAPI_TEST_CONSTANT(SEC_FILE);
    BOOST_WINAPI_TEST_CONSTANT(SEC_IMAGE);
    BOOST_WINAPI_TEST_CONSTANT(SEC_RESERVE);
    BOOST_WINAPI_TEST_CONSTANT(SEC_COMMIT);
    BOOST_WINAPI_TEST_CONSTANT(SEC_NOCACHE);

    BOOST_WINAPI_TEST_CONSTANT(SECTION_QUERY);
    BOOST_WINAPI_TEST_CONSTANT(SECTION_MAP_WRITE);
    BOOST_WINAPI_TEST_CONSTANT(SECTION_MAP_READ);
    BOOST_WINAPI_TEST_CONSTANT(SECTION_MAP_EXECUTE);
    BOOST_WINAPI_TEST_CONSTANT(SECTION_EXTEND_SIZE);
    BOOST_WINAPI_TEST_CONSTANT(SECTION_ALL_ACCESS);

    BOOST_WINAPI_TEST_CONSTANT(FILE_MAP_COPY);
    BOOST_WINAPI_TEST_CONSTANT(FILE_MAP_WRITE);
    BOOST_WINAPI_TEST_CONSTANT(FILE_MAP_READ);
    BOOST_WINAPI_TEST_CONSTANT(FILE_MAP_ALL_ACCESS);

#if BOOST_WINAPI_PARTITION_DESKTOP
#if !defined(BOOST_NO_ANSI_APIS)
    BOOST_WINAPI_TEST_FUNCTION_SIGNATURE(OpenFileMappingA);
#endif
#endif // BOOST_WINAPI_PARTITION_DESKTOP

#if BOOST_WINAPI_PARTITION_DESKTOP || BOOST_WINAPI_PARTITION_SYSTEM
    BOOST_WINAPI_TEST_FUNCTION_SIGNATURE(MapViewOfFile);
    BOOST_WINAPI_TEST_FUNCTION_SIGNATURE(MapViewOfFileEx);
    BOOST_WINAPI_TEST_FUNCTION_SIGNATURE(OpenFileMappingW);
#endif // BOOST_WINAPI_PARTITION_DESKTOP || BOOST_WINAPI_PARTITION_SYSTEM

#if BOOST_WINAPI_PARTITION_APP || BOOST_WINAPI_PARTITION_SYSTEM
    BOOST_WINAPI_TEST_FUNCTION_SIGNATURE(FlushViewOfFile);
    BOOST_WINAPI_TEST_FUNCTION_SIGNATURE(UnmapViewOfFile);
#endif // BOOST_WINAPI_PARTITION_APP || BOOST_WINAPI_PARTITION_SYSTEM

    return boost::report_errors();
}
