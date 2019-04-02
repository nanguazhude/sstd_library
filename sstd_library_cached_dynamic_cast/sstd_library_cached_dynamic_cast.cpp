#include "../sstd_library.hpp"
#include "sstd_library_cached_dynamic_cast.hpp"

#include <map>
#include <list>
#include <shared_mutex>
#include <unordered_map>

namespace _theSSTDLibraryCachedDynamicCastFile {

#ifndef sstd_virtual_cached_all
#define sstd_virtual_cached_all (true)
#endif

#if (false==sstd_virtual_cached_all)
    inline std::size_t catchedSize() {
        return (1024uLL * 1024uLL);
    }
#endif

    class CastKey {
    public:
        std::type_index from;
        std::type_index to;
    };

    class CastKeyHash {
    public:
        std::size_t operator()(const CastKey  & arg) const {
            return arg.from.hash_code() + arg.to.hash_code();
        }
    };

    class CastKeyEqual {
    public:
        bool operator()(const CastKey  & l, const CastKey  & r) const {
            return (l.from == r.from) && (l.to == r.to);
        }
    };

#if (false == sstd_virtual_cached_all)
    /*按照标准，迭代器不会失效*/
    using CastList = std::list< std::pair< std::ptrdiff_t, CastKey >,
        sstd::allocator< std::pair< std::ptrdiff_t, CastKey > > >;
    /*按照标准，迭代器可能失效*/
    using CastMap =
        std::unordered_map< CastKey,
        CastList::const_iterator,
        CastKeyHash,
        CastKeyEqual,
        sstd::allocator< std::pair< const CastKey, CastList::const_iterator > > >;
#else
    using CastMap =
        std::unordered_map< CastKey,
        std::ptrdiff_t,
        CastKeyHash,
        CastKeyEqual,
        sstd::allocator< std::pair< const CastKey, std::ptrdiff_t > > >;
#endif


    class CastCache {

        template<bool IsWriteLocked = false>
        inline std::ptrdiff_t rawFindCachedVirtualPointerDistance(const CastKey& arg) {
#if (false == sstd_virtual_cached_all)
            auto varPos = thisMap.find(arg);
            if (varPos == thisMap.end()) {
                return sstd::virtual_cast_not_find_pos;
            }
            if constexpr (!IsWriteLocked) {
                std::unique_lock varWriteLock{
                    thisFindCachedVirtualPointerDistanceMutex };
                auto varBeginPos = thisList.cbegin();
                if (varPos->second != varBeginPos) {
                    thisList.splice(varBeginPos, thisList, varPos->second);
                }
                return varPos->second->first;
            } else {
                auto varBeginPos = thisList.cbegin();
                if (varPos->second != varBeginPos) {
                    thisList.splice(varBeginPos, thisList, varPos->second);
                }
                return varPos->second->first;
            }
#else
            auto varPos = thisMap.find(arg);
            if (varPos == thisMap.end()) {
                return sstd::virtual_cast_not_find_pos;
            }
            return varPos->second;
            (void)IsWriteLocked;
#endif
        }

        inline void rawRegisterCachedVirtualPointerDistance(const CastKey & arg,
            std::ptrdiff_t value) {
#if (false == sstd_virtual_cached_all)
            thisList.emplace_front(value, arg);
            thisMap[arg] = thisList.cbegin();

            while (thisList.size() > catchedSize()) {
                auto varLostPos = --thisList.cend();
                thisMap.erase(varLostPos->second);
                thisList.pop_back();
            }
#else
            thisMap[arg] = value;
#endif
        }

    public:
        inline CastCache() {
            thisMap.reserve(1024uLL * 1024uLL);
        }

    private:
        CastMap thisMap;
#if (false == sstd_virtual_cached_all)
        CastList thisList;
#endif
        /*本类一共有两个函数，
        thisReadWriteMutex：用于区别findCachedVirtualPointerDistance，registerCachedVirtualPointerDistance
        thisFindCachedVirtualPointerDistanceMutex：仅用于findCachedVirtualPointerDistance
        */
        std::shared_mutex thisReadWriteMutex;
#if (false == sstd_virtual_cached_all)
        class ListMutex {
            std::atomic_flag thisFlag{ ATOMIC_FLAG_INIT };
        public:
            inline ListMutex() = default;
            sstd_delete_copy_create(ListMutex);
            inline void lock() {
                while (thisFlag.test_and_set(std::memory_order_acquire));
            }
            inline void unlock() {
                thisFlag.clear(std::memory_order_release);
            }
        } thisFindCachedVirtualPointerDistanceMutex;
#endif

    public:

        inline std::ptrdiff_t findCachedVirtualPointerDistance(const CastKey & arg) {
            std::shared_lock varReadLock{ thisReadWriteMutex };
            return rawFindCachedVirtualPointerDistance<false>(arg);
        }

        inline void registerCachedVirtualPointerDistance(const CastKey & arg,
            std::ptrdiff_t value) {

            if (findCachedVirtualPointerDistance(arg) != sstd::virtual_cast_not_find_pos) {
                return;
            }

            std::unique_lock varWriteLock{ thisReadWriteMutex };
            if (rawFindCachedVirtualPointerDistance<true>(arg) != sstd::virtual_cast_not_find_pos) {
                return;
            }
            rawRegisterCachedVirtualPointerDistance(arg, value);

        }

    private:
        sstd_class(CastCache);
    };

    CastCache & getCastCache() {
        static auto * varAns = sstd_new<CastCache>();
        return *varAns;
    }

}/*namespace _theSSTDLibraryCachedDynamicCastFile*/

namespace sstd {

    extern void * private_runtime_dynamic_cast(
        void * argInput/*dynamic_cast<void *>*/,
        const std::type_info * argInputType/*type_id(remove_cvr)*/,
        const std::type_info * argOutputType/*type_id(remove_cvr)*/);

    namespace detail {

        SSTD_SYMBOL_DECL std::ptrdiff_t findCachedVirtualPointerDistance(const std::type_index& argFrom,
            const std::type_index & argTo) {
            return _theSSTDLibraryCachedDynamicCastFile::getCastCache().
                findCachedVirtualPointerDistance({ argFrom,argTo });
        }

        SSTD_SYMBOL_DECL void registerCachedVirtualPointerDistance(const std::type_index& argFrom,
            const std::type_index & argTo,
            std::ptrdiff_t argValue) {
            return _theSSTDLibraryCachedDynamicCastFile::getCastCache().
                registerCachedVirtualPointerDistance({ argFrom,argTo }, argValue);
        }

        class PrivateTypeIndex{
        public:
            std::type_info * data;
        };

        SSTD_SYMBOL_DECL void * runtimeDynamicCast(const void * arg,
                                                   const std::type_index & a,
                                                   const std::type_index & b){

            if( arg == nullptr){
                return nullptr;
            }

            if(a ==b){
                return const_cast<void *>( arg );
            }

            static_assert (  sizeof( std::type_index ) == sizeof(std::type_info *) );

            return sstd::private_runtime_dynamic_cast( const_cast<void *>(arg),
                                                (((PrivateTypeIndex *)(&a))->data) ,
                                                (((PrivateTypeIndex *)(&b))->data));

        }

    }

}/*namespace sstd*/


/*
boost::lockfree::queue：... pod
boost::lockfree::stack：... any
boost::lockfree::spsc_queue： ... single
*/















