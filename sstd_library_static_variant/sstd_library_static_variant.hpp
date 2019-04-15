#pragma once

#include "../sstd_library.hpp"
#include <typeinfo>
#include <typeindex>

namespace _theSSTDLibraryStaticVariantFile {

    typedef std::pair<void*, void(*)(void *)>(*ConvertFunction)(void *);
    SSTD_SYMBOL_DECL std::size_t registerTypeID(const std::type_index &);
    SSTD_SYMBOL_DECL bool registerCastFunction(std::size_t/*from*/, std::size_t/*to*/, ConvertFunction/*function*/);
    SSTD_SYMBOL_DECL ConvertFunction findCastFunction(std::size_t /*from*/, std::size_t /*to*/);
    SSTD_SYMBOL_DECL bool registerTypeName(std::size_t, std::string_view);
    SSTD_SYMBOL_DECL std::string_view typeName(std::size_t);

}/*namespace _theSSTDLibraryStaticVariantFile*/

namespace sstd {

    namespace hpp_detail {
        template<typename T1>
        class RegisterStaticClass {
            using T = std::remove_cv_t< std::remove_reference_t<T1> >;
            static_assert (false == std::is_polymorphic_v<T>);
        public:
            using ConvertFunction = _theSSTDLibraryStaticVariantFile::ConvertFunction;
        public:
            using TheType = T;
            constexpr inline static bool isRegistered() noexcept {
                return true;
            }

            inline static std::size_t typeIndex() {
                const static auto varAns =
                    _theSSTDLibraryStaticVariantFile::registerTypeID(typeid (TheType));
                return varAns;
            }

            inline static std::string_view typeName() {
                return _theSSTDLibraryStaticVariantFile::typeName(typeIndex());
            }

            inline static bool registerTypeName(std::string_view arg) {
                return _theSSTDLibraryStaticVariantFile::registerTypeName(typeIndex(), arg);
            }

            template<typename To>
            inline static bool registerConvertFunction(ConvertFunction arg) {
                using TheTypeTo = RegisterStaticClass< typename RegisterStaticClass<To>::TheType >;
                if constexpr (std::is_same_v< typename TheTypeTo::TheType, TheType >) {
                    return true;
                } else {
                    auto varFromTypeIndex = typeIndex();
                    auto varToTypeIndex = TheTypeTo::typeIndex();
                    return
                        _theSSTDLibraryStaticVariantFile::registerCastFunction(varFromTypeIndex,
                            varToTypeIndex,
                            arg);
                }
            }

            template<typename To>
            inline static ConvertFunction convertFunction() {
                using TheTypeTo = RegisterStaticClass< typename RegisterStaticClass<To>::TheType >;
                if constexpr (std::is_same_v< typename TheTypeTo::TheType, TheType >) {
                    return [](void * arg)->std::pair<void *, void(*)(void *)> {
                        return { arg,nullptr };
                    };
                } else {
                    return _theSSTDLibraryStaticVariantFile::findCastFunction(typeIndex(),
                        TheTypeTo::typeIndex());
                }
            }

        };
    }/* namespace hpp_detail */

    template<typename T>
    using RegisterStaticClass = hpp_detail::RegisterStaticClass<
        std::remove_cv_t<
        std::remove_reference_t< T > > >;

    template< typename T, typename TName /*sstd_cstr("")*/ >
    inline std::size_t registerStaticClass() {
        static std::size_t varAns = []() -> std::size_t {
            auto varAns = RegisterStaticClass<T>::typeIndex();
            RegisterStaticClass<T>::registerTypeName(TName::toStringView());
            return varAns;
        }();
        return varAns;
    }


}/*namespace sstd*/
