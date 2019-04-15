#pragma once

/*  https://en.cppreference.com/w/cpp/filesystem/path  */

#include <fstream>
#include <iostream>
#include <type_traits>

#include <string>

#if __has_include(<filesystem>)
#include <filesystem>
#else
#include <experimental/filesystem>
#endif

namespace sstd {

#if __has_include(<filesystem>)
    namespace filesystem = std::filesystem;
#else
    namespace filesystem = std::experimental::filesystem;
#endif

    template< typename T = std::ifstream >
    inline decltype(auto) getFileStreamPath(const filesystem::path & arg){
        if constexpr( std::is_constructible_v< T , const filesystem::path & > ) {
            return arg;
        } else if constexpr( std::is_constructible_v< T , const std::wstring & > ){
            return arg.wstring();
        }else {
            return arg.string();
        }
    }

}/*namespace sstd*/
