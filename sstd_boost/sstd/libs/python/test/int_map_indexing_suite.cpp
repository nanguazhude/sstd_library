// Copyright David Abrahams 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstd/boost/python/class.hpp>
#include <sstd/boost/python/suite/indexing/map_indexing_suite.hpp>

void int_map_indexing_suite()
{
    using namespace boost::python;

    // Compile check only...
    class_<std::map<int, int> >("IntMap")
        .def(map_indexing_suite<std::map<int, int> >())
    ;
}
