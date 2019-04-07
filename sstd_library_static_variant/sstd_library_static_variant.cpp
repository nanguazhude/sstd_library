#include "sstd_library_static_variant.hpp"

#include <map>
#include <vector>
#include <unordered_map>
#include <shared_mutex>
#include <limits>
#include <charconv>
#include <regex>

namespace _theSSTDLibraryStaticVariantFile {

    constexpr const static auto theNopos =
        std::numeric_limits<std::size_t>::max();

    class StaticClassInformation {
    public:
        std::size_t index{ 1 };
        std::type_index stdIndex;
        std::basic_string< char, std::char_traits<char>, sstd::allocator<char> > typeName;
        std::map< std::size_t,
            ConvertFunction,
            std::less<  >,
            sstd::allocator< std::pair<const std::size_t, ConvertFunction > > > convertFunctionMap;
        inline StaticClassInformation(const std::type_index & arg) :
            stdIndex(arg) {
            typeName = arg.name();
        }
    public:
        sstd_class(StaticClassInformation);
    };

    class StaticClass {
    public:

        using Vector = std::vector<
            std::unique_ptr< StaticClassInformation >,
            sstd::allocator< std::unique_ptr< StaticClassInformation > > >;

        using Map = std::unordered_map<
            std::type_index,
            StaticClassInformation *,
            std::hash< std::type_index >,
            std::equal_to<void>,
            sstd::allocator< std::pair< const std::type_index, StaticClassInformation * > > >;

        Vector thisListInformation;
        Map thisMapInformation;
        std::shared_mutex thisMutex;
    private:
        std::size_t rawRegisterTypeID(const std::type_index & arg) {

            auto varThisPos = thisMapInformation.find(arg);
            if (varThisPos != thisMapInformation.end()) {
                return varThisPos->second->index;
            }

            return theNopos;
        }
    public:
        inline std::size_t registerTypeID(const std::type_index & arg) {

            {
                std::shared_lock varReadLock{ thisMutex };
                auto varAns = rawRegisterTypeID(arg);
                if (varAns != theNopos) {
                    return varAns;
                }
            }

            {
                std::unique_lock varWriteLock{ thisMutex };
                auto varAns = rawRegisterTypeID(arg);
                if (varAns != theNopos) {
                    return varAns;
                }
                thisListInformation.push_back(sstd_make_unique<StaticClassInformation>(arg));
                auto varThePointer =
                    thisListInformation.back().get();
                varThePointer->index = thisListInformation.size();
                thisMapInformation[arg] = varThePointer;
                return varThePointer->index;
            }

        }

        inline bool registerCastFunction(std::size_t argFrom,
            std::size_t argTo,
            ConvertFunction argFunction) {

            if (argFrom < 1) {
                return false;
            }

            if (argTo < 1) {
                return false;
            }

            std::unique_lock varWriteLock{ thisMutex };

            if (argFrom > thisListInformation.size()) {
                return false;
            }

            if (argTo > thisListInformation.size()) {
                return false;
            }

            if (argFunction == nullptr) {
                thisListInformation[argFrom - 1]->convertFunctionMap.erase(argTo);
            } else {
                thisListInformation[argFrom - 1]->convertFunctionMap[argTo] = argFunction;
            }

            return true;

        }

        inline std::string_view findTypeName(std::size_t argIndex) {
            if (argIndex < 1) {
                return ""sv;
            }

            std::shared_lock varReadLock{ thisMutex };

            if (argIndex > thisListInformation.size()) {
                return ""sv;
            }

            return thisListInformation[argIndex - 1]->typeName;

        }

        inline bool registerTypeName(std::size_t argIndex, std::string_view argName) {
            if (argIndex < 1) {
                return false;
            }

            std::unique_lock varWriteLock{ thisMutex };

            if (argIndex > thisListInformation.size()) {
                return false;
            }

            thisListInformation[argIndex - 1]->typeName = argName;

            return true;
        }

        inline ConvertFunction findCastFunction(std::size_t argFrom, std::size_t argTo) {
            if (argFrom < 1) {
                return nullptr;
            }

            if (argTo < 1) {
                return nullptr;
            }

            std::shared_lock varReadLock{ thisMutex };

            if (argFrom > thisListInformation.size()) {
                return nullptr;
            }

            if (argTo > thisListInformation.size()) {
                return nullptr;
            }

            const auto & varMap =
                thisListInformation[argFrom - 1]->convertFunctionMap;

            auto varPos = varMap.find(argTo);
            if (varPos == varMap.end()) {
                return nullptr;
            }

            return varPos->second;

        }

    public:
        sstd_class(StaticClass);
    };


    template<typename Key, typename KeyName>
    class TheIndex {
    public:
        std::size_t value{ 1 };
        using index_t = Key;
        using name_t = KeyName;
    };

    template<typename T>
    inline void registerAType(StaticClass * varAns, T &  arg) {
        using U = std::remove_cv_t< std::remove_reference_t<T> >;
        using index_t = typename U::index_t;
        using name_t = typename U::name_t;
        arg.value = varAns->registerTypeID(typeid(index_t));
        varAns->registerTypeName(arg.value, name_t::toStringView());
    }

    template<typename ... T>
    inline void registerTypeList(StaticClass * varAns, T & ... arg) {
        (registerAType(varAns, arg), ...);
    }

    template<typename T>
    class StaticTypeWrap {
    public:
        T value;

        template<typename U>
        inline StaticTypeWrap(const U & arg) :
            value(static_cast<T>(arg)) {
        }

    protected:
        inline StaticTypeWrap() {
        }
    private:
        sstd_class(StaticTypeWrap);
    };

    template<std::size_t>
    class Number_8_16_32;

    template<  >
    class Number_8_16_32<8> {
    public:
        using type = std::int8_t;
        using unsigned_type = std::uint8_t;
    };

    template<  >
    class Number_8_16_32<16> {
    public:
        using type = std::int16_t;
        using unsigned_type = std::uint16_t;
    };

    template<  >
    class Number_8_16_32<32> {
    public:
        using type = std::int32_t;
        using unsigned_type = std::uint32_t;
    };

    template<typename T>
    class StaticFromStringViewWrap : public StaticTypeWrap<T> {
    public:
        inline StaticFromStringViewWrap(const std::string_view & arg) {
            using U = std::remove_cv_t< std::remove_reference_t< T > >;
            if constexpr (std::is_same_v< U, bool >) {

                /* http://www.cplusplus.com/reference/regex/basic_regex/ */
                {
                    const static std::regex varTrue{ u8R"(\s*true\s*)" ,std::regex_constants::ECMAScript |
                        std::regex_constants::icase |
                        std::regex_constants::optimize
                    };
                    this->value = std::regex_match(arg.begin(), arg.end(), varTrue);
                    if (this->value) {
                        return;
                    }
                }
                {
                    const static std::regex varFlase{ u8R"(\s*false\s*)" ,std::regex_constants::ECMAScript |
                       std::regex_constants::icase |
                       std::regex_constants::optimize
                    };
                    this->value = std::regex_match(arg.begin(), arg.end(), varFlase);
                    if (this->value) {
                        this->value = false;
                        return;
                    }
                }
                long double varAns;
                std::from_chars(arg.data(), arg.data() + arg.size(), varAns);
                this->value = varAns;
            } else if constexpr (std::is_same_v< U, wchar_t >) {
                from_int< typename Number_8_16_32< sizeof(wchar_t) * 8 >::unsigned_type >(arg);
            } else if constexpr (std::is_same_v< U, char16_t >) {
                from_int< typename Number_8_16_32<16>::unsigned_type >(arg);
            } else if constexpr (std::is_same_v< U, char32_t >) {
                from_int< typename Number_8_16_32<32>::unsigned_type >(arg);
            } else if constexpr (std::is_same_v< U, char >) {
                from_int< typename Number_8_16_32<8>::unsigned_type >(arg);
            } else if constexpr (std::is_same_v< U, signed char >) {
                from_int< typename Number_8_16_32<8>::type >(arg);
            } else if constexpr (std::is_same_v< U, unsigned char >) {
                from_int< typename Number_8_16_32<8>::unsigned_type >(arg);
            } else {
                /* https://en.cppreference.com/w/cpp/utility/from_chars */
                std::from_chars_result varAns =
                    std::from_chars(arg.data(), arg.data() + arg.size(), this->value);
                if (varAns.ec == std::errc{}) {
                    return;
                }
                if constexpr (std::numeric_limits<U>::has_quiet_NaN) {
                    this->value = std::numeric_limits<U>::quiet_NaN();
                    return;
                } else {
                    this->value = 0;
                    return;
                }
            }
        }

    private:

        template<typename U>
        inline void from_int(const std::string_view & arg) {
            auto var = reinterpret_cast<U *>(&(this->value));
            static_assert(sizeof(U) == sizeof(this->value));
            std::from_chars_result varAns =
                std::from_chars(arg.data(), arg.data() + arg.size(), *var);
            if (varAns.ec == std::errc{}) {
                return;
            }
            *var = 0;
        }

    private:
        sstd_class(StaticFromStringViewWrap);
    };

    template< typename TF, typename TT >
    inline void regesterAStaticTypeCast(StaticClass * varAns,
        TF & argFrom,
        TT & argTo) {

        if (argFrom.value == argTo.value) {
            return;
        }

        using ReturnType = std::pair<void*, void(*)(void *)>;

        using UTF = std::remove_cv_t< std::remove_reference_t< TF > >;
        using UTT = std::remove_cv_t< std::remove_reference_t< TT > >;

        using RTF = typename UTF::index_t;
        using RTT = typename UTT::index_t;

        varAns->registerCastFunction(argFrom.value, argTo.value,
            [](void * arg)->ReturnType {
            using CastValueType = StaticTypeWrap<RTT>;
            auto varAns = sstd_new< CastValueType >(
                *reinterpret_cast<RTF *>(arg));
            return { &(varAns->value),[](void * arg) {
                delete reinterpret_cast<CastValueType *>(arg); } }; });

        varAns->registerCastFunction(argTo.value, argFrom.value,
            [](void * arg)->ReturnType {
            using CastValueType = StaticTypeWrap<RTF>;
            auto varAns = sstd_new< CastValueType >(
                *reinterpret_cast<RTT *>(arg));
            return { &(varAns->value),[](void * arg) {
               delete reinterpret_cast<CastValueType *>(arg); } }; });

    }

    template< typename T0, typename ... T >
    inline void registerStaticTypeCast(StaticClass * varAns, T0 & f, T & ... arg) {
        if constexpr (sizeof...(arg) == 0) {
            (void)f;
            (void)varAns;
            return;
        } else {
            (regesterAStaticTypeCast(varAns, f, arg), ...);
            registerStaticTypeCast(varAns, arg ...);
        }
    }

    class StringViewWrap {
    public:
        std::string_view ans;
        std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> string;
    public:
        template<typename T1>
        inline void fromValue(const T1 & arg) {
            using T = std::remove_cv_t< std::remove_reference_t<T1> >;
            if constexpr (std::is_same_v<bool, T>) {
                if (arg) {
                    ans = sstd_cstr("true")::toStringView();
                } else {
                    ans = sstd_cstr("false")::toStringView();
                }
            } else {
                /* https://en.cppreference.com/w/cpp/utility/to_chars */
                char varTmp[256];
                std::to_chars_result varAns =
                    std::to_chars(std::begin(varTmp), std::end(varTmp), arg);
#if  defined(_DEBUG)
                assert(varAns.ec == std::errc{});
#endif
                auto varNumberSize =
                    static_cast<std::size_t>(varAns.ptr - static_cast<char *>(varTmp));
                string.reserve(varNumberSize);
                string.assign(varTmp, varNumberSize);
                ans = string;
            }
        }
    public:
        template<typename T1>
        inline static std::pair<void*, void(*)(void *)> createCastFunction(void * arg) {
            using T = std::remove_cv_t< std::remove_reference_t<T1> >;
            auto varAns = sstd_new<StringViewWrap>();
            varAns->fromValue(*reinterpret_cast<T *>(arg));
            return { varAns , [](void * arg) {
                delete reinterpret_cast<StringViewWrap *>(arg); } };
        }
    private:
        sstd_class(StringViewWrap);
    };

    template<typename TF>
    inline void registerAToStringViewCast(StaticClass * varAns,
        std::size_t varStringViewIndex,
        TF & f) {
        using UTF = std::remove_cv_t< std::remove_reference_t< TF > >;
        using index_t = typename UTF::index_t;
        /*从数字转为字符串*/
        varAns->registerCastFunction(f.value, varStringViewIndex,
            &StringViewWrap::createCastFunction<index_t>);
        /*从字符转为数字*/
        varAns->registerCastFunction(varStringViewIndex, f.value, [](void * arg)
            ->std::pair<void*, void(*)(void *)> {
            auto varString = reinterpret_cast<std::string_view *>(arg);
            auto varAns = sstd_new< StaticFromStringViewWrap< index_t > >(*varString);
            return { varAns,[](void * arg) {
                delete reinterpret_cast<StaticFromStringViewWrap< index_t > *>(arg);
            } };
        });
    }

    template<typename ... T>
    inline void registerToStringViewCast(StaticClass * varAns,
        std::size_t varStringViewIndex,
        T & ... f) {
        (registerAToStringViewCast(varAns, varStringViewIndex, f), ...);
    }

    inline StaticClass & getStaticClass() {
        static auto varAns = []() {
            auto varAns = sstd_new< StaticClass >();

            using baisc_numbers = std::tuple<
                TheIndex< bool, sstd_cstr("bool") >,
                TheIndex< char, sstd_cstr("char") >,
                TheIndex< signed char, sstd_cstr("signed char") >,
                TheIndex< unsigned char, sstd_cstr("unsigned char") >,
                TheIndex< char16_t, sstd_cstr("char16_t") >,
                TheIndex< char32_t, sstd_cstr("char32_t") >,
                TheIndex< wchar_t, sstd_cstr("wchar_t") >,
                TheIndex< int, sstd_cstr("int") >,
                TheIndex< unsigned int, sstd_cstr("unsigned int") >,
                TheIndex< short, sstd_cstr("short") >,
                TheIndex< unsigned short, sstd_cstr("unsigned short") >,
                TheIndex< long int, sstd_cstr("long int") >,
                TheIndex< unsigned long int, sstd_cstr("unsigned long int") >,
                TheIndex< long long int, sstd_cstr("long long int") >,
                TheIndex< unsigned long long int, sstd_cstr("unsigned long long int") >,
                TheIndex< float, sstd_cstr("float") >,
                TheIndex< double, sstd_cstr("double") >,
                TheIndex< long double, sstd_cstr("long double") > >;

            auto varStringViewID = varAns->registerTypeID(typeid(std::string_view));
            {
                varAns->registerTypeName(varStringViewID, sstd_cstr("std::string_view")::toStringView());
            }

            {
                varAns->registerTypeName(varAns->registerTypeID(typeid(void)), 
                    sstd_cstr("void")::toStringView());
            }

            {
                /*注册类型*/
                baisc_numbers varNumbers;
                std::apply([varAns](auto && ... args) {
                    registerTypeList(varAns, args ...);
                }, varNumbers);
                /*注册类型转换*/
                std::apply([varAns](auto && ... args) {
                    registerStaticTypeCast(varAns, args ...);
                }, varNumbers);
                /*注册与string view相互转换*/
                std::apply([varAns, varStringViewID](auto && ... args) {
                    registerToStringViewCast(varAns, varStringViewID, args...);
                }, varNumbers);
            }

            return varAns;
        }();
        return *varAns;
    }

    SSTD_SYMBOL_DECL std::size_t registerTypeID(const std::type_index & arg) {
        return getStaticClass().registerTypeID(arg);
    }

    SSTD_SYMBOL_DECL bool registerCastFunction(std::size_t argFrom,
        std::size_t argTo,
        ConvertFunction argFunction) {
        return getStaticClass().registerCastFunction(argFrom, argTo, argFunction);
    }

    SSTD_SYMBOL_DECL  ConvertFunction findCastFunction(std::size_t argFrom, std::size_t argTo) {
        return getStaticClass().findCastFunction(argFrom, argTo);
    }

    SSTD_SYMBOL_DECL bool registerTypeName(std::size_t argIndex,
        std::string_view argName) {
        return getStaticClass().registerTypeName(argIndex, argName);
    }

    SSTD_SYMBOL_DECL std::string_view typeName(std::size_t argIndex) {
        return getStaticClass().findTypeName(argIndex);
    }


}/**/




