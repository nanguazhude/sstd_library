// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_FACTORY_HPP
#define BOOST_GEOMETRY_PROJECTIONS_FACTORY_HPP

#include <map>
#include <string>

#include <sstd/boost/shared_ptr.hpp>

#include <sstd/boost/geometry/srs/projections/dpar.hpp>
#include <sstd/boost/geometry/srs/projections/factory_key.hpp>
#include <sstd/boost/geometry/srs/projections/proj4.hpp>
#include <sstd/boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <sstd/boost/geometry/srs/projections/proj/aea.hpp>
#include <sstd/boost/geometry/srs/projections/proj/aeqd.hpp>
#include <sstd/boost/geometry/srs/projections/proj/airy.hpp>
#include <sstd/boost/geometry/srs/projections/proj/aitoff.hpp>
#include <sstd/boost/geometry/srs/projections/proj/august.hpp>
#include <sstd/boost/geometry/srs/projections/proj/bacon.hpp>
#include <sstd/boost/geometry/srs/projections/proj/bipc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/boggs.hpp>
#include <sstd/boost/geometry/srs/projections/proj/bonne.hpp>
#include <sstd/boost/geometry/srs/projections/proj/cass.hpp>
#include <sstd/boost/geometry/srs/projections/proj/cc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/cea.hpp>
#include <sstd/boost/geometry/srs/projections/proj/chamb.hpp>
#include <sstd/boost/geometry/srs/projections/proj/collg.hpp>
#include <sstd/boost/geometry/srs/projections/proj/crast.hpp>
#include <sstd/boost/geometry/srs/projections/proj/denoy.hpp>
#include <sstd/boost/geometry/srs/projections/proj/eck1.hpp>
#include <sstd/boost/geometry/srs/projections/proj/eck2.hpp>
#include <sstd/boost/geometry/srs/projections/proj/eck3.hpp>
#include <sstd/boost/geometry/srs/projections/proj/eck4.hpp>
#include <sstd/boost/geometry/srs/projections/proj/eck5.hpp>
#include <sstd/boost/geometry/srs/projections/proj/eqc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/eqdc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/etmerc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/fahey.hpp>
#include <sstd/boost/geometry/srs/projections/proj/fouc_s.hpp>
#include <sstd/boost/geometry/srs/projections/proj/gall.hpp>
#include <sstd/boost/geometry/srs/projections/proj/geocent.hpp>
#include <sstd/boost/geometry/srs/projections/proj/geos.hpp>
#include <sstd/boost/geometry/srs/projections/proj/gins8.hpp>
#include <sstd/boost/geometry/srs/projections/proj/gn_sinu.hpp>
#include <sstd/boost/geometry/srs/projections/proj/gnom.hpp>
#include <sstd/boost/geometry/srs/projections/proj/goode.hpp>
#include <sstd/boost/geometry/srs/projections/proj/gstmerc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/hammer.hpp>
#include <sstd/boost/geometry/srs/projections/proj/hatano.hpp>
#include <sstd/boost/geometry/srs/projections/proj/healpix.hpp>
#include <sstd/boost/geometry/srs/projections/proj/krovak.hpp>
#include <sstd/boost/geometry/srs/projections/proj/igh.hpp>
#include <sstd/boost/geometry/srs/projections/proj/imw_p.hpp>
#include <sstd/boost/geometry/srs/projections/proj/isea.hpp>
#include <sstd/boost/geometry/srs/projections/proj/laea.hpp>
#include <sstd/boost/geometry/srs/projections/proj/labrd.hpp>
#include <sstd/boost/geometry/srs/projections/proj/lagrng.hpp>
#include <sstd/boost/geometry/srs/projections/proj/larr.hpp>
#include <sstd/boost/geometry/srs/projections/proj/lask.hpp>
#include <sstd/boost/geometry/srs/projections/proj/latlong.hpp>
#include <sstd/boost/geometry/srs/projections/proj/lcc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/lcca.hpp>
#include <sstd/boost/geometry/srs/projections/proj/loxim.hpp>
#include <sstd/boost/geometry/srs/projections/proj/lsat.hpp>
#include <sstd/boost/geometry/srs/projections/proj/mbtfpp.hpp>
#include <sstd/boost/geometry/srs/projections/proj/mbtfpq.hpp>
#include <sstd/boost/geometry/srs/projections/proj/mbt_fps.hpp>
#include <sstd/boost/geometry/srs/projections/proj/merc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/mill.hpp>
#include <sstd/boost/geometry/srs/projections/proj/mod_ster.hpp>
#include <sstd/boost/geometry/srs/projections/proj/moll.hpp>
#include <sstd/boost/geometry/srs/projections/proj/natearth.hpp>
#include <sstd/boost/geometry/srs/projections/proj/nell.hpp>
#include <sstd/boost/geometry/srs/projections/proj/nell_h.hpp>
#include <sstd/boost/geometry/srs/projections/proj/nocol.hpp>
#include <sstd/boost/geometry/srs/projections/proj/nsper.hpp>
#include <sstd/boost/geometry/srs/projections/proj/nzmg.hpp>
#include <sstd/boost/geometry/srs/projections/proj/ob_tran.hpp>
#include <sstd/boost/geometry/srs/projections/proj/ocea.hpp>
#include <sstd/boost/geometry/srs/projections/proj/oea.hpp>
#include <sstd/boost/geometry/srs/projections/proj/omerc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/ortho.hpp>
#include <sstd/boost/geometry/srs/projections/proj/qsc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/poly.hpp>
#include <sstd/boost/geometry/srs/projections/proj/putp2.hpp>
#include <sstd/boost/geometry/srs/projections/proj/putp3.hpp>
#include <sstd/boost/geometry/srs/projections/proj/putp4p.hpp>
#include <sstd/boost/geometry/srs/projections/proj/putp5.hpp>
#include <sstd/boost/geometry/srs/projections/proj/putp6.hpp>
#include <sstd/boost/geometry/srs/projections/proj/robin.hpp>
#include <sstd/boost/geometry/srs/projections/proj/rouss.hpp>
#include <sstd/boost/geometry/srs/projections/proj/rpoly.hpp>
#include <sstd/boost/geometry/srs/projections/proj/sconics.hpp>
#include <sstd/boost/geometry/srs/projections/proj/somerc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/stere.hpp>
#include <sstd/boost/geometry/srs/projections/proj/sterea.hpp>
#include <sstd/boost/geometry/srs/projections/proj/sts.hpp>
#include <sstd/boost/geometry/srs/projections/proj/tcc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/tcea.hpp>
#include <sstd/boost/geometry/srs/projections/proj/tmerc.hpp>
#include <sstd/boost/geometry/srs/projections/proj/tpeqd.hpp>
#include <sstd/boost/geometry/srs/projections/proj/urm5.hpp>
#include <sstd/boost/geometry/srs/projections/proj/urmfps.hpp>
#include <sstd/boost/geometry/srs/projections/proj/vandg.hpp>
#include <sstd/boost/geometry/srs/projections/proj/vandg2.hpp>
#include <sstd/boost/geometry/srs/projections/proj/vandg4.hpp>
#include <sstd/boost/geometry/srs/projections/proj/wag2.hpp>
#include <sstd/boost/geometry/srs/projections/proj/wag3.hpp>
#include <sstd/boost/geometry/srs/projections/proj/wag7.hpp>
#include <sstd/boost/geometry/srs/projections/proj/wink1.hpp>
#include <sstd/boost/geometry/srs/projections/proj/wink2.hpp>

namespace boost { namespace geometry { namespace projections
{

namespace detail
{

template <typename Params, typename CT, typename ProjParams>
class factory
{
private:
    typedef detail::factory_entry
        <
            Params,
            CT,
            ProjParams
        > entry_base;

    typedef typename factory_key_util<Params>::type key_type;
    typedef boost::shared_ptr<entry_base> entry_ptr;

    typedef std::map<key_type, entry_ptr> entries_map;

    entries_map m_entries;

public:

    factory()
    {
        detail::aea_init(*this);
        detail::aeqd_init(*this);
        detail::airy_init(*this);
        detail::aitoff_init(*this);
        detail::august_init(*this);
        detail::bacon_init(*this);
        detail::bipc_init(*this);
        detail::boggs_init(*this);
        detail::bonne_init(*this);
        detail::cass_init(*this);
        detail::cc_init(*this);
        detail::cea_init(*this);
        detail::chamb_init(*this);
        detail::collg_init(*this);
        detail::crast_init(*this);
        detail::denoy_init(*this);
        detail::eck1_init(*this);
        detail::eck2_init(*this);
        detail::eck3_init(*this);
        detail::eck4_init(*this);
        detail::eck5_init(*this);
        detail::eqc_init(*this);
        detail::eqdc_init(*this);
        detail::etmerc_init(*this);
        detail::fahey_init(*this);
        detail::fouc_s_init(*this);
        detail::gall_init(*this);
        detail::geocent_init(*this);
        detail::geos_init(*this);
        detail::gins8_init(*this);
        detail::gn_sinu_init(*this);
        detail::gnom_init(*this);
        detail::goode_init(*this);
        detail::gstmerc_init(*this);
        detail::hammer_init(*this);
        detail::hatano_init(*this);
        detail::healpix_init(*this);
        detail::krovak_init(*this);
        detail::igh_init(*this);
        detail::imw_p_init(*this);
        detail::isea_init(*this);
        detail::labrd_init(*this);
        detail::laea_init(*this);
        detail::lagrng_init(*this);
        detail::larr_init(*this);
        detail::lask_init(*this);
        detail::latlong_init(*this);
        detail::lcc_init(*this);
        detail::lcca_init(*this);
        detail::loxim_init(*this);
        detail::lsat_init(*this);
        detail::mbtfpp_init(*this);
        detail::mbtfpq_init(*this);
        detail::mbt_fps_init(*this);
        detail::merc_init(*this);
        detail::mill_init(*this);
        detail::mod_ster_init(*this);
        detail::moll_init(*this);
        detail::natearth_init(*this);
        detail::nell_init(*this);
        detail::nell_h_init(*this);
        detail::nocol_init(*this);
        detail::nsper_init(*this);
        detail::nzmg_init(*this);
        detail::ob_tran_init(*this);
        detail::ocea_init(*this);
        detail::oea_init(*this);
        detail::omerc_init(*this);
        detail::ortho_init(*this);
        detail::qsc_init(*this);
        detail::poly_init(*this);
        detail::putp2_init(*this);
        detail::putp3_init(*this);
        detail::putp4p_init(*this);
        detail::putp5_init(*this);
        detail::putp6_init(*this);
        detail::robin_init(*this);
        detail::rouss_init(*this);
        detail::rpoly_init(*this);
        detail::sconics_init(*this);
        detail::somerc_init(*this);
        detail::stere_init(*this);
        detail::sterea_init(*this);
        detail::sts_init(*this);
        detail::tcc_init(*this);
        detail::tcea_init(*this);
        detail::tmerc_init(*this);
        detail::tpeqd_init(*this);
        detail::urm5_init(*this);
        detail::urmfps_init(*this);
        detail::vandg_init(*this);
        detail::vandg2_init(*this);
        detail::vandg4_init(*this);
        detail::wag2_init(*this);
        detail::wag3_init(*this);
        detail::wag7_init(*this);
        detail::wink1_init(*this);
        detail::wink2_init(*this);
    }

    void add_to_factory(key_type const& key, entry_base* entry)
    {
        // The pointer has to be owned before std::map::operator[] in case it thrown an exception.
        entry_ptr ptr(entry);
        m_entries[key] = ptr;
    }

    detail::base_v<CT, ProjParams>* create_new(Params const& params, ProjParams const& proj_par) const
    {
        typename factory_key_util<Params>::type key = factory_key_util<Params>::get(proj_par);
        typename entries_map::const_iterator it = m_entries.find(key);
        if (it != m_entries.end())
        {
            return it->second->create_new(params, proj_par);
        }

        return 0;
    }
};

template <typename T>
inline detail::base_v<T, projections::parameters<T> >*
    create_new(srs::detail::proj4_parameters const& params,
               projections::parameters<T> const& parameters)
{
    static factory<srs::detail::proj4_parameters, T, projections::parameters<T> > const fac;
    return fac.create_new(params, parameters);
}

template <typename T>
inline detail::base_v<T, projections::parameters<T> >*
    create_new(srs::dpar::parameters<T> const& params,
               projections::parameters<T> const& parameters)
{
    static factory<srs::dpar::parameters<T>, T, projections::parameters<T> > const fac;
    return fac.create_new(params, parameters);
}


} // namespace detail

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_FACTORY_HPP

