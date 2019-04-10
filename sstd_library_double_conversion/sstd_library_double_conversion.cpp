#include "sstd_library_double_conversion.hpp"
#include "double-conversion/double-conversion.h"

#include <limits>

namespace sstd {

    namespace detail {

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
            if (arg.empty()) {
                return std::numeric_limits<long double>::quiet_NaN();
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

        SSTD_SYMBOL_DECL std::basic_string<char, std::char_traits<char>, sstd::allocator<char>> fromStringLongDouble(long double) {
            return {};
        }

    }/*namespace detail*/

}/*namespace sstd*/









