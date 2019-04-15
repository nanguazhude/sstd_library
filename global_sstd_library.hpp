#pragma once

#include <sstd/boost/config.hpp>

#ifndef SSTD_SYMBOL_EXPORT
#define SSTD_SYMBOL_EXPORT BOOST_SYMBOL_EXPORT
#endif

#ifndef SSTD_SYMBOL_IMPORT
#define SSTD_SYMBOL_IMPORT BOOST_SYMBOL_IMPORT
#endif

#ifndef SSTD_SYMBOL_DECL

#if defined(SSTD_BUILD_SOURCE)
#define SSTD_SYMBOL_DECL SSTD_SYMBOL_EXPORT
#else
#define SSTD_SYMBOL_DECL SSTD_SYMBOL_IMPORT
#endif

#endif

#ifndef sstd_default_copy_create
#define sstd_default_copy_create(...) __VA_ARGS__ (const __VA_ARGS__ &) = default ; \
__VA_ARGS__ (__VA_ARGS__ &&) = default ; \
__VA_ARGS__ &operator= (__VA_ARGS__ &&) = default ; \
__VA_ARGS__ &operator= (const __VA_ARGS__ &) = default ; \
static_assert(true)/*__VA_ARGS__*/
#endif

#ifndef sstd_delete_copy_create
#define sstd_delete_copy_create(...) __VA_ARGS__ (const __VA_ARGS__ &) = delete ; \
__VA_ARGS__ (__VA_ARGS__ &&) = delete ; \
__VA_ARGS__ &operator= (__VA_ARGS__ &&) = delete ; \
__VA_ARGS__ &operator= (const __VA_ARGS__ &) = delete ; \
static_assert(true)/*__VA_ARGS__*/
#endif

#ifndef sstd_data
#define sstd_data(...)           the##__VA_ARGS__##Data
#endif

#ifndef sstd_data_type
#define sstd_data_type(...)      __VA_ARGS__##Data
#endif
