#include "../sstd_library.hpp"
#include "sstd_library_cached_dynamic_cast.hpp"

#include <map>
#include <list>
#include <shared_mutex>
#include <unordered_map>

namespace _theSSTDLibraryCachedDynamicCastFile {

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

    class CastCache {

        template<bool IsWriteLocked=false>
        inline std::ptrdiff_t rawFindCachedVirtualPointerDistance(const CastKey& arg) {
            auto varPos = thisMap.find(arg);
            if (varPos == thisMap.end()) {
                return sstd::virtual_cast_not_find_pos;
            }
            if constexpr(!IsWriteLocked){
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
        }

        inline void rawRegisterCachedVirtualPointerDistance(const CastKey & arg,
            std::ptrdiff_t value) {
            thisList.emplace_front(value, arg);
            thisMap[arg] = thisList.cbegin();

            if (thisList.size() > (1024uLL * 1024uLL)) {
                auto varLostPos = --thisList.cend();
                thisMap.erase(varLostPos->second);
                thisList.pop_back();
            }

        }

    private:
        CastMap thisMap;
        CastList thisList;
        /*本类一共有两个函数，
        thisReadWriteMutex：用于区别findCachedVirtualPointerDistance，registerCachedVirtualPointerDistance
        thisFindCachedVirtualPointerDistanceMutex：仅用于findCachedVirtualPointerDistance
        */
        std::shared_mutex thisReadWriteMutex;
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

    }

}/*namespace sstd*/


/*
boost::lockfree::queue：... pod
boost::lockfree::stack：... any
boost::lockfree::spsc_queue： ... single
*/















