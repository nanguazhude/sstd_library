// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <geometry_test_common.hpp>

#include <sstd/boost/geometry/io/wkt/wkt.hpp>

#include <sstd/boost/geometry/algorithms/correct.hpp>
#include <sstd/boost/geometry/algorithms/within.hpp>

#include <sstd/boost/geometry/geometries/box.hpp>
#include <sstd/boost/geometry/geometries/polygon.hpp>
#include <sstd/boost/geometry/geometries/point_xy.hpp>
#include <sstd/boost/geometry/geometries/multi_polygon.hpp>

#include "test_within.hpp"


template <typename P>
void test_all()
{
    typedef bg::model::multi_polygon<bg::model::polygon<P> > mp;

    // test multi-with-one-polygon (trivial case)
    test_geometry<P, mp>("POINT(1 1)", "MULTIPOLYGON(((0 0,0 2,2 2,2 0,0 0)))", true);
    test_geometry<P, mp>("POINT(3 3)", "MULTIPOLYGON(((0 0,0 2,2 2,2 0,0 0)))", false);
    test_geometry<P, mp>("POINT(0 1)", "MULTIPOLYGON(((0 0,0 2,2 2,2 0,0 0)))", false);
    test_geometry<P, mp>("POINT(4 4)", "MULTIPOLYGON(((0 0,0 2,2 2,2 0,0 0)))", false);

    // test if it is in one of them
    std::string multi("MULTIPOLYGON("
        "((0 0,0 2,2 2,2 0,0 0))"
        "((3 3,3 6,6 6,6 3,3 3))"
        ")");
    test_geometry<P, mp>("POINT(4 4)", multi, true);
    test_geometry<P, mp>("POINT(1 1)", multi, true);
    test_geometry<P, mp>("POINT(0 1)", multi, false);
}

int test_main( int , char* [] )
{
    //test_all<bg::model::d2::point_xy<int> >();
    test_all<bg::model::d2::point_xy<double> >();

#if defined(HAVE_TTMATH)
    test_all<bg::model::d2::point_xy<ttmath_big> >();
#endif

    return 0;
}
