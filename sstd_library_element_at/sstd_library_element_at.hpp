#pragma once

#include <memory>
#include <tuple>
#include <type_traits>
#include "../sstd_library.hpp"

namespace sstd::the {
    enum class ConstructAtType {
        Element,
        Construct,
    };
}/*namespace the*/

namespace sstd::the {

    namespace _private {

        template<typename T, typename AfterConstruct, auto Flag>
        class ConstructAtBasic {
            using ThisTypeNotRef = std::remove_reference_t<T>;
            using ThisType = std::remove_cv_t<ThisTypeNotRef>;
            using ThisSTorage = std::aligned_storage_t<sizeof(ThisType), alignof(ThisType)>;
            ThisSTorage thisData;

            inline ThisType * thePointer() {
                return reinterpret_cast<ThisType *>(&thisData);
            }

            inline const ThisType * thePointer() const {
                return reinterpret_cast<const ThisType *>(&thisData);
            }

            inline ConstructAtBasic(const ConstructAtBasic &) = delete;
            inline ConstructAtBasic(ConstructAtBasic &&) = delete;
            inline ConstructAtBasic&operator=(const ConstructAtBasic &) = delete;
            inline ConstructAtBasic&operator=(ConstructAtBasic &&) = delete;
        protected:

            inline void destory_at() {
                if constexpr (!std::is_trivially_destructible_v<ThisType>) {
                    std::destroy_at(thePointer());
                }
            }

        public:
            template<typename ... Args>
            inline ConstructAtBasic(Args && ... args) {
                ThisType * varPointer;

                if constexpr ((std::is_constructible_v<ThisType, Args && ...>) && ((sizeof...(Args)) > 0)) {
                    varPointer = ::new(&thisData) ThisType(std::forward<Args>(args)...);
                } else {
                    varPointer = ::new(&thisData) ThisType{ std::forward<Args>(args)... };
                }

                if constexpr (!std::is_same_v<AfterConstruct, void>) {
                    try {
                        AfterConstruct varAfterConstruct;
                        varAfterConstruct(varPointer);
                    } catch (...) {
                        std::destroy_at(varPointer);
                        throw;
                    }
                }

            }

            inline const ThisTypeNotRef * operator->() const {
                return thePointer();
            }

            inline ThisTypeNotRef * operator->() {
                return thePointer();
            }

            inline const ThisTypeNotRef & operator*() const & {
                return *thePointer();
            }

            inline ThisTypeNotRef & operator*() & {
                return *thePointer();
            }

            inline ThisTypeNotRef && operator*() && {
                return std::move(*thePointer());
            }

            inline operator ThisTypeNotRef && () && {
                return std::move(*thePointer());
            }

            inline operator const ThisTypeNotRef & () && {
                return std::move(*thePointer());
            }

            inline operator ThisTypeNotRef & () & {
                return *thePointer();
            }

            inline operator const ThisTypeNotRef & () const & {
                return std::move(*thePointer());
            }

            inline ThisTypeNotRef * pointer() {
                return thePointer();
            }

            inline const ThisTypeNotRef * pointer() const {
                return thePointer();
            }
        private:
            sstd_class(ConstructAtBasic);
        };

    }/*namespace _private*/

    template<typename T, typename AfterConstruct, auto Flag, 
        bool = std::is_trivially_destructible_v<std::remove_cv_t<
        std::remove_reference_t<T>>>>
    class ConstructAtBasic :
        public _private::ConstructAtBasic<T, AfterConstruct, Flag> {
        using Super = _private::ConstructAtBasic<T, AfterConstruct, Flag>;
    public:
        using Super::Super;
        inline ~ConstructAtBasic() {
            Super::destory_at();
        }
    };

    template<typename T, typename AfterConstruct, auto Flag>
    class ConstructAtBasic<T, AfterConstruct,Flag,true> :
        public _private::ConstructAtBasic<T, AfterConstruct, Flag> {
        using Super = _private::ConstructAtBasic<T, AfterConstruct, Flag>;
    public:
        using Super::Super;
    };

}/*namespace the*/

namespace sstd {

    template<typename T, typename A = void, auto Flag = the::ConstructAtType::Element >
    using ElementAt = the::ConstructAtBasic<T, A, Flag>;

    template<typename T, typename A = void, auto Flag = the::ConstructAtType::Construct >
    using ConstructAt = the::ConstructAtBasic<T, A, Flag>;

}/*namespace sstd*/
