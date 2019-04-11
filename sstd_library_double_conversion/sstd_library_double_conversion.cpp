#include "sstd_library_double_conversion.hpp"
#include "double-conversion/double-conversion.h"

#include <limits>
#include <sstream>
#if __has_include(<charconv>)
#include <charconv>
#define HAS_CHARCONV_THE_FILE_ (1u)
#else
#define HAS_CHARCONV_THE_FILE_ (0u)
#endif

namespace sstd {

    namespace detail {

#if HAS_CHARCONV_THE_FILE_

        class NoType {
        };

        template<typename ... T>
        inline decltype(std::from_chars(std::declval<T>()...)) isCallAble(T &&  ... args) {
            return std::from_chars(std::forward<T>(args)...);
        }

        inline NoType isCallAble(...) {
            return{};
        }

#endif

        inline constexpr bool hasCharConv() {
#if HAS_CHARCONV_THE_FILE_
            using T = std::remove_cv_t< std::remove_reference_t<
                decltype(isCallAble("1.0", "1.0" + 1, std::declval<long double &>()))>>;
            return !std::is_same_v< T, NoType >;
#else
            return false;
#endif
        }

        SSTD_SYMBOL_DECL double toDouble(std::string_view arg) {
            double_conversion::StringToDoubleConverter varConverter{
                double_conversion::StringToDoubleConverter::ALLOW_LEADING_SPACES |
                double_conversion::StringToDoubleConverter::ALLOW_TRAILING_SPACES |
                double_conversion::StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN |
                double_conversion::StringToDoubleConverter::ALLOW_CASE_INSENSIBILITY,
                0.0/*empty*/,
                0.0,
                "Infinity",
                "NaN"
            };
            int varAnsLength{ 0 };
            return varConverter.StringToDouble(arg.data(), static_cast<int>(arg.size()), &varAnsLength);
        }

        SSTD_SYMBOL_DECL float toFloat(std::string_view arg) {
            double_conversion::StringToDoubleConverter varConverter{
                double_conversion::StringToDoubleConverter::ALLOW_LEADING_SPACES |
                double_conversion::StringToDoubleConverter::ALLOW_TRAILING_SPACES |
                double_conversion::StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN |
                double_conversion::StringToDoubleConverter::ALLOW_CASE_INSENSIBILITY,
                0.0/*empty*/,
                0.0,
                "Infinity",
                "NaN"
            };
            int varAnsLength{ 0 };
            return varConverter.StringToFloat(arg.data(), static_cast<int>(arg.size()), &varAnsLength);
        }

        SSTD_SYMBOL_DECL long double toLongDouble(std::string_view arg) {
            if constexpr (hasCharConv()) {
#if HAS_CHARCONV_THE_FILE_
                long double varAns{ 0 };
                std::from_chars(arg.data(), arg.data() + arg.size(), varAns);
                return varAns;
#endif
            } else {
                std::basic_stringstream< char, std::char_traits<char>, sstd::allocator<char> > var;
                var << arg;
                long double varAns{ 0 };
                var >> varAns;
                return varAns;
            }
            return {};
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringFloat(float arg) {
            std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> varAns;
            varAns.resize(64, char(0));
            auto & varConversion =
                double_conversion::DoubleToStringConverter::EcmaScriptConverter();
            double_conversion::StringBuilder varBuilder{ varAns.data(), static_cast<int>(varAns.size()) };
            varConversion.ToShortestSingle(arg, &varBuilder);
            varAns.resize(static_cast<std::size_t>(varBuilder.position()));
            return std::move(varAns);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringDouble(double arg) {
            std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> varAns;
            varAns.resize(64, char(0));
            auto & varConversion =
                double_conversion::DoubleToStringConverter::EcmaScriptConverter();
            double_conversion::StringBuilder varBuilder{ varAns.data(), static_cast<int>(varAns.size()) };
            varConversion.ToShortest(arg, &varBuilder);
            varAns.resize(static_cast<std::size_t>(varBuilder.position()));
            return std::move(varAns);
        }

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringLongDouble(long double arg) {
            if constexpr (hasCharConv()) {
#if HAS_CHARCONV_THE_FILE_
                std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> varAns;
                varAns.resize(64, char(0));
                auto[p, e] = std::to_chars(varAns.data(), varAns.data() + varAns.size(), arg);
                if (e != std::errc{}) {
                    return{};
                }
                varAns.resize(static_cast<std::size_t>(p - varAns.data()));
                return std::move(varAns);
#endif
            } else {
                std::basic_stringstream< char, std::char_traits<char>, sstd::allocator<char> > var;
                var << arg;
                std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> varAns;
                var >> varAns;
                return std::move(varAns);
            }
            return {};
        }

    }/*namespace detail*/

}/*namespace sstd*/









