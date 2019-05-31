#pragma once


#include <string_view>
#include "constexpr_string.hpp"

namespace sstd {

    template<auto ... Args>
    class constexpr_string_literal {
        const constexpr static char thisData[]{ Args ... , char(0) };
    public:
        inline static constexpr std::string_view toStringView() noexcept {
            return{ thisData , sizeof...(Args) };
        }
        inline static constexpr constexpr_string toConstexprStringView() noexcept {
            return { thisData };
        }
        inline constexpr static const char * data() noexcept {
            return thisData;
        }
        inline constexpr static std::size_t size() noexcept {
            return sizeof...(Args);
        }
    };

    template<typename T1>
    inline constexpr auto toStringView() noexcept {
        using T = std::remove_cv_t< std::remove_reference_t< T1 > >;
        return T::toStringView();
    }

    template<typename T1>
    inline constexpr auto toConstexprStringView() noexcept {
        using T = std::remove_cv_t< std::remove_reference_t< T1 > >;
        return T::toConstexprStringView();
    }

    template<typename T1>
    inline constexpr auto stringData() noexcept {
        using T = std::remove_cv_t< std::remove_reference_t< T1 > >;
        return T::data();
    }

    template<typename T1>
    inline constexpr auto stringSize() noexcept {
        using T = std::remove_cv_t< std::remove_reference_t< T1 > >;
        return T::size();
    }

}/*namespace sstd*/

namespace sstd::_string_detail_helper_0x0011 {

    template<auto ... Z>
    using Detail = constexpr_string_literal<Z...>;

    template<typename, typename >
    class Cat;

    template<auto ... A, auto ... B>
    class Cat<Detail<A...>, Detail<B...>> {
    public:
        using type = Detail<A..., B...>;
    };

    template< std::size_t N, auto ... Z  >
    class DetailHelper;

    template<auto Z0, auto Z1, auto Z2, auto ... Z >
    class DetailHelper<0, Z0, Z1, Z2, Z...> {
    public:
        using type = Detail<>;
    };

    template<auto Z0, auto Z1, auto Z2, auto ... Z >
    class DetailHelper<1, Z0, Z1, Z2, Z...> {
    public:
        using type = Detail<Z0>;
    };

    template<auto Z0, auto Z1, auto Z2, auto ... Z  >
    class DetailHelper<2, Z0, Z1, Z2, Z...> {
    public:
        using type = Detail<Z0, Z1>;
    };

    template<auto Z0, auto Z1, auto Z2, auto ... Z >
    class DetailHelper<3, Z0, Z1, Z2, Z...> {
    public:
        using type = Detail<Z0, Z1, Z2>;
    };

    template<std::size_t N, auto Z0, auto Z1, auto Z2, auto ... Z >
    class DetailHelper<N, Z0, Z1, Z2, Z...> {
        static_assert(N > 3);
        static_assert(N <= 512);
    public:
        using type = typename Cat< Detail<Z0, Z1, Z2>,
            typename DetailHelper<N - 3, Z...>::type
        >::type;
    };

}/*namespace sstd::_string_detail_helper_0x0011*/

#ifndef _sstd_key_at
#define _sstd_key_at(_POS_SSTD_,...) ((_POS_SSTD_)<(sizeof(__VA_ARGS__))?(__VA_ARGS__[_POS_SSTD_]):char(0))
#endif

#ifndef sstd_cstr
#define sstd_cstr(...) ::sstd::_string_detail_helper_0x0011::DetailHelper< (sizeof(__VA_ARGS__)-1)  \
,_sstd_key_at( 0 ,__VA_ARGS__)  ,_sstd_key_at( 1 ,__VA_ARGS__)  ,_sstd_key_at( 2 ,__VA_ARGS__)  ,_sstd_key_at( 3 ,__VA_ARGS__)  ,_sstd_key_at( 4 ,__VA_ARGS__)  ,_sstd_key_at( 5 ,__VA_ARGS__)  ,_sstd_key_at( 6 ,__VA_ARGS__)  ,_sstd_key_at( 7 ,__VA_ARGS__)  ,_sstd_key_at( 8 ,__VA_ARGS__)  ,_sstd_key_at( 9 ,__VA_ARGS__)  ,_sstd_key_at( 10 ,__VA_ARGS__)  ,_sstd_key_at( 11 ,__VA_ARGS__)  ,_sstd_key_at( 12 ,__VA_ARGS__)  ,_sstd_key_at( 13 ,__VA_ARGS__)  ,_sstd_key_at( 14 ,__VA_ARGS__)  ,_sstd_key_at( 15 ,__VA_ARGS__)  ,_sstd_key_at( 16 ,__VA_ARGS__)  ,_sstd_key_at( 17 ,__VA_ARGS__)  ,_sstd_key_at( 18 ,__VA_ARGS__)  ,_sstd_key_at( 19 ,__VA_ARGS__)  ,_sstd_key_at( 20 ,__VA_ARGS__)  ,_sstd_key_at( 21 ,__VA_ARGS__)  ,_sstd_key_at( 22 ,__VA_ARGS__)  ,_sstd_key_at( 23 ,__VA_ARGS__)  ,_sstd_key_at( 24 ,__VA_ARGS__)  ,_sstd_key_at( 25 ,__VA_ARGS__)  ,_sstd_key_at( 26 ,__VA_ARGS__)  ,_sstd_key_at( 27 ,__VA_ARGS__)  ,_sstd_key_at( 28 ,__VA_ARGS__)  ,_sstd_key_at( 29 ,__VA_ARGS__)  ,_sstd_key_at( 30 ,__VA_ARGS__)  ,_sstd_key_at( 31 ,__VA_ARGS__)  ,_sstd_key_at( 32 ,__VA_ARGS__)  ,_sstd_key_at( 33 ,__VA_ARGS__)  ,_sstd_key_at( 34 ,__VA_ARGS__)  ,_sstd_key_at( 35 ,__VA_ARGS__)  ,_sstd_key_at( 36 ,__VA_ARGS__)  ,_sstd_key_at( 37 ,__VA_ARGS__)  ,_sstd_key_at( 38 ,__VA_ARGS__)  ,_sstd_key_at( 39 ,__VA_ARGS__)  ,_sstd_key_at( 40 ,__VA_ARGS__)  ,_sstd_key_at( 41 ,__VA_ARGS__)  ,_sstd_key_at( 42 ,__VA_ARGS__)  ,_sstd_key_at( 43 ,__VA_ARGS__)  ,_sstd_key_at( 44 ,__VA_ARGS__)  ,_sstd_key_at( 45 ,__VA_ARGS__)  ,_sstd_key_at( 46 ,__VA_ARGS__)  ,_sstd_key_at( 47 ,__VA_ARGS__)  ,_sstd_key_at( 48 ,__VA_ARGS__)  ,_sstd_key_at( 49 ,__VA_ARGS__)  ,_sstd_key_at( 50 ,__VA_ARGS__)  ,_sstd_key_at( 51 ,__VA_ARGS__)  ,_sstd_key_at( 52 ,__VA_ARGS__)  ,_sstd_key_at( 53 ,__VA_ARGS__)  ,_sstd_key_at( 54 ,__VA_ARGS__)  ,_sstd_key_at( 55 ,__VA_ARGS__)  ,_sstd_key_at( 56 ,__VA_ARGS__)  ,_sstd_key_at( 57 ,__VA_ARGS__)  ,_sstd_key_at( 58 ,__VA_ARGS__)  ,_sstd_key_at( 59 ,__VA_ARGS__)  ,_sstd_key_at( 60 ,__VA_ARGS__)  ,_sstd_key_at( 61 ,__VA_ARGS__)  ,_sstd_key_at( 62 ,__VA_ARGS__)  ,_sstd_key_at( 63 ,__VA_ARGS__)  ,_sstd_key_at( 64 ,__VA_ARGS__)   \
,_sstd_key_at( 65 ,__VA_ARGS__)  ,_sstd_key_at( 66 ,__VA_ARGS__)  ,_sstd_key_at( 67 ,__VA_ARGS__)  ,_sstd_key_at( 68 ,__VA_ARGS__)  ,_sstd_key_at( 69 ,__VA_ARGS__)  ,_sstd_key_at( 70 ,__VA_ARGS__)  ,_sstd_key_at( 71 ,__VA_ARGS__)  ,_sstd_key_at( 72 ,__VA_ARGS__)  ,_sstd_key_at( 73 ,__VA_ARGS__)  ,_sstd_key_at( 74 ,__VA_ARGS__)  ,_sstd_key_at( 75 ,__VA_ARGS__)  ,_sstd_key_at( 76 ,__VA_ARGS__)  ,_sstd_key_at( 77 ,__VA_ARGS__)  ,_sstd_key_at( 78 ,__VA_ARGS__)  ,_sstd_key_at( 79 ,__VA_ARGS__)  ,_sstd_key_at( 80 ,__VA_ARGS__)  ,_sstd_key_at( 81 ,__VA_ARGS__)  ,_sstd_key_at( 82 ,__VA_ARGS__)  ,_sstd_key_at( 83 ,__VA_ARGS__)  ,_sstd_key_at( 84 ,__VA_ARGS__)  ,_sstd_key_at( 85 ,__VA_ARGS__)  ,_sstd_key_at( 86 ,__VA_ARGS__)  ,_sstd_key_at( 87 ,__VA_ARGS__)  ,_sstd_key_at( 88 ,__VA_ARGS__)  ,_sstd_key_at( 89 ,__VA_ARGS__)  ,_sstd_key_at( 90 ,__VA_ARGS__)  ,_sstd_key_at( 91 ,__VA_ARGS__)  ,_sstd_key_at( 92 ,__VA_ARGS__)  ,_sstd_key_at( 93 ,__VA_ARGS__)  ,_sstd_key_at( 94 ,__VA_ARGS__)  ,_sstd_key_at( 95 ,__VA_ARGS__)  ,_sstd_key_at( 96 ,__VA_ARGS__)  ,_sstd_key_at( 97 ,__VA_ARGS__)  ,_sstd_key_at( 98 ,__VA_ARGS__)  ,_sstd_key_at( 99 ,__VA_ARGS__)  ,_sstd_key_at( 100 ,__VA_ARGS__)  ,_sstd_key_at( 101 ,__VA_ARGS__)  ,_sstd_key_at( 102 ,__VA_ARGS__)  ,_sstd_key_at( 103 ,__VA_ARGS__)  ,_sstd_key_at( 104 ,__VA_ARGS__)  ,_sstd_key_at( 105 ,__VA_ARGS__)  ,_sstd_key_at( 106 ,__VA_ARGS__)  ,_sstd_key_at( 107 ,__VA_ARGS__)  ,_sstd_key_at( 108 ,__VA_ARGS__)  ,_sstd_key_at( 109 ,__VA_ARGS__)  ,_sstd_key_at( 110 ,__VA_ARGS__)  ,_sstd_key_at( 111 ,__VA_ARGS__)  ,_sstd_key_at( 112 ,__VA_ARGS__)  ,_sstd_key_at( 113 ,__VA_ARGS__)  ,_sstd_key_at( 114 ,__VA_ARGS__)  ,_sstd_key_at( 115 ,__VA_ARGS__)  ,_sstd_key_at( 116 ,__VA_ARGS__)  ,_sstd_key_at( 117 ,__VA_ARGS__)  ,_sstd_key_at( 118 ,__VA_ARGS__)  ,_sstd_key_at( 119 ,__VA_ARGS__)  ,_sstd_key_at( 120 ,__VA_ARGS__)  ,_sstd_key_at( 121 ,__VA_ARGS__)  ,_sstd_key_at( 122 ,__VA_ARGS__)  ,_sstd_key_at( 123 ,__VA_ARGS__)  ,_sstd_key_at( 124 ,__VA_ARGS__)  ,_sstd_key_at( 125 ,__VA_ARGS__)  ,_sstd_key_at( 126 ,__VA_ARGS__)  ,_sstd_key_at( 127 ,__VA_ARGS__)  ,_sstd_key_at( 128 ,__VA_ARGS__)   \
,_sstd_key_at( 129 ,__VA_ARGS__)  ,_sstd_key_at( 130 ,__VA_ARGS__)  ,_sstd_key_at( 131 ,__VA_ARGS__)  ,_sstd_key_at( 132 ,__VA_ARGS__)  ,_sstd_key_at( 133 ,__VA_ARGS__)  ,_sstd_key_at( 134 ,__VA_ARGS__)  ,_sstd_key_at( 135 ,__VA_ARGS__)  ,_sstd_key_at( 136 ,__VA_ARGS__)  ,_sstd_key_at( 137 ,__VA_ARGS__)  ,_sstd_key_at( 138 ,__VA_ARGS__)  ,_sstd_key_at( 139 ,__VA_ARGS__)  ,_sstd_key_at( 140 ,__VA_ARGS__)  ,_sstd_key_at( 141 ,__VA_ARGS__)  ,_sstd_key_at( 142 ,__VA_ARGS__)  ,_sstd_key_at( 143 ,__VA_ARGS__)  ,_sstd_key_at( 144 ,__VA_ARGS__)  ,_sstd_key_at( 145 ,__VA_ARGS__)  ,_sstd_key_at( 146 ,__VA_ARGS__)  ,_sstd_key_at( 147 ,__VA_ARGS__)  ,_sstd_key_at( 148 ,__VA_ARGS__)  ,_sstd_key_at( 149 ,__VA_ARGS__)  ,_sstd_key_at( 150 ,__VA_ARGS__)  ,_sstd_key_at( 151 ,__VA_ARGS__)  ,_sstd_key_at( 152 ,__VA_ARGS__)  ,_sstd_key_at( 153 ,__VA_ARGS__)  ,_sstd_key_at( 154 ,__VA_ARGS__)  ,_sstd_key_at( 155 ,__VA_ARGS__)  ,_sstd_key_at( 156 ,__VA_ARGS__)  ,_sstd_key_at( 157 ,__VA_ARGS__)  ,_sstd_key_at( 158 ,__VA_ARGS__)  ,_sstd_key_at( 159 ,__VA_ARGS__)  ,_sstd_key_at( 160 ,__VA_ARGS__)  ,_sstd_key_at( 161 ,__VA_ARGS__)  ,_sstd_key_at( 162 ,__VA_ARGS__)  ,_sstd_key_at( 163 ,__VA_ARGS__)  ,_sstd_key_at( 164 ,__VA_ARGS__)  ,_sstd_key_at( 165 ,__VA_ARGS__)  ,_sstd_key_at( 166 ,__VA_ARGS__)  ,_sstd_key_at( 167 ,__VA_ARGS__)  ,_sstd_key_at( 168 ,__VA_ARGS__)  ,_sstd_key_at( 169 ,__VA_ARGS__)  ,_sstd_key_at( 170 ,__VA_ARGS__)  ,_sstd_key_at( 171 ,__VA_ARGS__)  ,_sstd_key_at( 172 ,__VA_ARGS__)  ,_sstd_key_at( 173 ,__VA_ARGS__)  ,_sstd_key_at( 174 ,__VA_ARGS__)  ,_sstd_key_at( 175 ,__VA_ARGS__)  ,_sstd_key_at( 176 ,__VA_ARGS__)  ,_sstd_key_at( 177 ,__VA_ARGS__)  ,_sstd_key_at( 178 ,__VA_ARGS__)  ,_sstd_key_at( 179 ,__VA_ARGS__)  ,_sstd_key_at( 180 ,__VA_ARGS__)  ,_sstd_key_at( 181 ,__VA_ARGS__)  ,_sstd_key_at( 182 ,__VA_ARGS__)  ,_sstd_key_at( 183 ,__VA_ARGS__)  ,_sstd_key_at( 184 ,__VA_ARGS__)  ,_sstd_key_at( 185 ,__VA_ARGS__)  ,_sstd_key_at( 186 ,__VA_ARGS__)  ,_sstd_key_at( 187 ,__VA_ARGS__)  ,_sstd_key_at( 188 ,__VA_ARGS__)  ,_sstd_key_at( 189 ,__VA_ARGS__)  ,_sstd_key_at( 190 ,__VA_ARGS__)  ,_sstd_key_at( 191 ,__VA_ARGS__)  ,_sstd_key_at( 192 ,__VA_ARGS__)   \
,_sstd_key_at( 193 ,__VA_ARGS__)  ,_sstd_key_at( 194 ,__VA_ARGS__)  ,_sstd_key_at( 195 ,__VA_ARGS__)  ,_sstd_key_at( 196 ,__VA_ARGS__)  ,_sstd_key_at( 197 ,__VA_ARGS__)  ,_sstd_key_at( 198 ,__VA_ARGS__)  ,_sstd_key_at( 199 ,__VA_ARGS__)  ,_sstd_key_at( 200 ,__VA_ARGS__)  ,_sstd_key_at( 201 ,__VA_ARGS__)  ,_sstd_key_at( 202 ,__VA_ARGS__)  ,_sstd_key_at( 203 ,__VA_ARGS__)  ,_sstd_key_at( 204 ,__VA_ARGS__)  ,_sstd_key_at( 205 ,__VA_ARGS__)  ,_sstd_key_at( 206 ,__VA_ARGS__)  ,_sstd_key_at( 207 ,__VA_ARGS__)  ,_sstd_key_at( 208 ,__VA_ARGS__)  ,_sstd_key_at( 209 ,__VA_ARGS__)  ,_sstd_key_at( 210 ,__VA_ARGS__)  ,_sstd_key_at( 211 ,__VA_ARGS__)  ,_sstd_key_at( 212 ,__VA_ARGS__)  ,_sstd_key_at( 213 ,__VA_ARGS__)  ,_sstd_key_at( 214 ,__VA_ARGS__)  ,_sstd_key_at( 215 ,__VA_ARGS__)  ,_sstd_key_at( 216 ,__VA_ARGS__)  ,_sstd_key_at( 217 ,__VA_ARGS__)  ,_sstd_key_at( 218 ,__VA_ARGS__)  ,_sstd_key_at( 219 ,__VA_ARGS__)  ,_sstd_key_at( 220 ,__VA_ARGS__)  ,_sstd_key_at( 221 ,__VA_ARGS__)  ,_sstd_key_at( 222 ,__VA_ARGS__)  ,_sstd_key_at( 223 ,__VA_ARGS__)  ,_sstd_key_at( 224 ,__VA_ARGS__)  ,_sstd_key_at( 225 ,__VA_ARGS__)  ,_sstd_key_at( 226 ,__VA_ARGS__)  ,_sstd_key_at( 227 ,__VA_ARGS__)  ,_sstd_key_at( 228 ,__VA_ARGS__)  ,_sstd_key_at( 229 ,__VA_ARGS__)  ,_sstd_key_at( 230 ,__VA_ARGS__)  ,_sstd_key_at( 231 ,__VA_ARGS__)  ,_sstd_key_at( 232 ,__VA_ARGS__)  ,_sstd_key_at( 233 ,__VA_ARGS__)  ,_sstd_key_at( 234 ,__VA_ARGS__)  ,_sstd_key_at( 235 ,__VA_ARGS__)  ,_sstd_key_at( 236 ,__VA_ARGS__)  ,_sstd_key_at( 237 ,__VA_ARGS__)  ,_sstd_key_at( 238 ,__VA_ARGS__)  ,_sstd_key_at( 239 ,__VA_ARGS__)  ,_sstd_key_at( 240 ,__VA_ARGS__)  ,_sstd_key_at( 241 ,__VA_ARGS__)  ,_sstd_key_at( 242 ,__VA_ARGS__)  ,_sstd_key_at( 243 ,__VA_ARGS__)  ,_sstd_key_at( 244 ,__VA_ARGS__)  ,_sstd_key_at( 245 ,__VA_ARGS__)  ,_sstd_key_at( 246 ,__VA_ARGS__)  ,_sstd_key_at( 247 ,__VA_ARGS__)  ,_sstd_key_at( 248 ,__VA_ARGS__)  ,_sstd_key_at( 249 ,__VA_ARGS__)  ,_sstd_key_at( 250 ,__VA_ARGS__)  ,_sstd_key_at( 251 ,__VA_ARGS__)  ,_sstd_key_at( 252 ,__VA_ARGS__)  ,_sstd_key_at( 253 ,__VA_ARGS__)  ,_sstd_key_at( 254 ,__VA_ARGS__)  ,_sstd_key_at( 255 ,__VA_ARGS__)  ,_sstd_key_at( 256 ,__VA_ARGS__)   \
,_sstd_key_at( 257 ,__VA_ARGS__)  ,_sstd_key_at( 258 ,__VA_ARGS__)  ,_sstd_key_at( 259 ,__VA_ARGS__)  ,_sstd_key_at( 260 ,__VA_ARGS__)  ,_sstd_key_at( 261 ,__VA_ARGS__)  ,_sstd_key_at( 262 ,__VA_ARGS__)  ,_sstd_key_at( 263 ,__VA_ARGS__)  ,_sstd_key_at( 264 ,__VA_ARGS__)  ,_sstd_key_at( 265 ,__VA_ARGS__)  ,_sstd_key_at( 266 ,__VA_ARGS__)  ,_sstd_key_at( 267 ,__VA_ARGS__)  ,_sstd_key_at( 268 ,__VA_ARGS__)  ,_sstd_key_at( 269 ,__VA_ARGS__)  ,_sstd_key_at( 270 ,__VA_ARGS__)  ,_sstd_key_at( 271 ,__VA_ARGS__)  ,_sstd_key_at( 272 ,__VA_ARGS__)  ,_sstd_key_at( 273 ,__VA_ARGS__)  ,_sstd_key_at( 274 ,__VA_ARGS__)  ,_sstd_key_at( 275 ,__VA_ARGS__)  ,_sstd_key_at( 276 ,__VA_ARGS__)  ,_sstd_key_at( 277 ,__VA_ARGS__)  ,_sstd_key_at( 278 ,__VA_ARGS__)  ,_sstd_key_at( 279 ,__VA_ARGS__)  ,_sstd_key_at( 280 ,__VA_ARGS__)  ,_sstd_key_at( 281 ,__VA_ARGS__)  ,_sstd_key_at( 282 ,__VA_ARGS__)  ,_sstd_key_at( 283 ,__VA_ARGS__)  ,_sstd_key_at( 284 ,__VA_ARGS__)  ,_sstd_key_at( 285 ,__VA_ARGS__)  ,_sstd_key_at( 286 ,__VA_ARGS__)  ,_sstd_key_at( 287 ,__VA_ARGS__)  ,_sstd_key_at( 288 ,__VA_ARGS__)  ,_sstd_key_at( 289 ,__VA_ARGS__)  ,_sstd_key_at( 290 ,__VA_ARGS__)  ,_sstd_key_at( 291 ,__VA_ARGS__)  ,_sstd_key_at( 292 ,__VA_ARGS__)  ,_sstd_key_at( 293 ,__VA_ARGS__)  ,_sstd_key_at( 294 ,__VA_ARGS__)  ,_sstd_key_at( 295 ,__VA_ARGS__)  ,_sstd_key_at( 296 ,__VA_ARGS__)  ,_sstd_key_at( 297 ,__VA_ARGS__)  ,_sstd_key_at( 298 ,__VA_ARGS__)  ,_sstd_key_at( 299 ,__VA_ARGS__)  ,_sstd_key_at( 300 ,__VA_ARGS__)  ,_sstd_key_at( 301 ,__VA_ARGS__)  ,_sstd_key_at( 302 ,__VA_ARGS__)  ,_sstd_key_at( 303 ,__VA_ARGS__)  ,_sstd_key_at( 304 ,__VA_ARGS__)  ,_sstd_key_at( 305 ,__VA_ARGS__)  ,_sstd_key_at( 306 ,__VA_ARGS__)  ,_sstd_key_at( 307 ,__VA_ARGS__)  ,_sstd_key_at( 308 ,__VA_ARGS__)  ,_sstd_key_at( 309 ,__VA_ARGS__)  ,_sstd_key_at( 310 ,__VA_ARGS__)  ,_sstd_key_at( 311 ,__VA_ARGS__)  ,_sstd_key_at( 312 ,__VA_ARGS__)  ,_sstd_key_at( 313 ,__VA_ARGS__)  ,_sstd_key_at( 314 ,__VA_ARGS__)  ,_sstd_key_at( 315 ,__VA_ARGS__)  ,_sstd_key_at( 316 ,__VA_ARGS__)  ,_sstd_key_at( 317 ,__VA_ARGS__)  ,_sstd_key_at( 318 ,__VA_ARGS__)  ,_sstd_key_at( 319 ,__VA_ARGS__)  ,_sstd_key_at( 320 ,__VA_ARGS__)   \
,_sstd_key_at( 321 ,__VA_ARGS__)  ,_sstd_key_at( 322 ,__VA_ARGS__)  ,_sstd_key_at( 323 ,__VA_ARGS__)  ,_sstd_key_at( 324 ,__VA_ARGS__)  ,_sstd_key_at( 325 ,__VA_ARGS__)  ,_sstd_key_at( 326 ,__VA_ARGS__)  ,_sstd_key_at( 327 ,__VA_ARGS__)  ,_sstd_key_at( 328 ,__VA_ARGS__)  ,_sstd_key_at( 329 ,__VA_ARGS__)  ,_sstd_key_at( 330 ,__VA_ARGS__)  ,_sstd_key_at( 331 ,__VA_ARGS__)  ,_sstd_key_at( 332 ,__VA_ARGS__)  ,_sstd_key_at( 333 ,__VA_ARGS__)  ,_sstd_key_at( 334 ,__VA_ARGS__)  ,_sstd_key_at( 335 ,__VA_ARGS__)  ,_sstd_key_at( 336 ,__VA_ARGS__)  ,_sstd_key_at( 337 ,__VA_ARGS__)  ,_sstd_key_at( 338 ,__VA_ARGS__)  ,_sstd_key_at( 339 ,__VA_ARGS__)  ,_sstd_key_at( 340 ,__VA_ARGS__)  ,_sstd_key_at( 341 ,__VA_ARGS__)  ,_sstd_key_at( 342 ,__VA_ARGS__)  ,_sstd_key_at( 343 ,__VA_ARGS__)  ,_sstd_key_at( 344 ,__VA_ARGS__)  ,_sstd_key_at( 345 ,__VA_ARGS__)  ,_sstd_key_at( 346 ,__VA_ARGS__)  ,_sstd_key_at( 347 ,__VA_ARGS__)  ,_sstd_key_at( 348 ,__VA_ARGS__)  ,_sstd_key_at( 349 ,__VA_ARGS__)  ,_sstd_key_at( 350 ,__VA_ARGS__)  ,_sstd_key_at( 351 ,__VA_ARGS__)  ,_sstd_key_at( 352 ,__VA_ARGS__)  ,_sstd_key_at( 353 ,__VA_ARGS__)  ,_sstd_key_at( 354 ,__VA_ARGS__)  ,_sstd_key_at( 355 ,__VA_ARGS__)  ,_sstd_key_at( 356 ,__VA_ARGS__)  ,_sstd_key_at( 357 ,__VA_ARGS__)  ,_sstd_key_at( 358 ,__VA_ARGS__)  ,_sstd_key_at( 359 ,__VA_ARGS__)  ,_sstd_key_at( 360 ,__VA_ARGS__)  ,_sstd_key_at( 361 ,__VA_ARGS__)  ,_sstd_key_at( 362 ,__VA_ARGS__)  ,_sstd_key_at( 363 ,__VA_ARGS__)  ,_sstd_key_at( 364 ,__VA_ARGS__)  ,_sstd_key_at( 365 ,__VA_ARGS__)  ,_sstd_key_at( 366 ,__VA_ARGS__)  ,_sstd_key_at( 367 ,__VA_ARGS__)  ,_sstd_key_at( 368 ,__VA_ARGS__)  ,_sstd_key_at( 369 ,__VA_ARGS__)  ,_sstd_key_at( 370 ,__VA_ARGS__)  ,_sstd_key_at( 371 ,__VA_ARGS__)  ,_sstd_key_at( 372 ,__VA_ARGS__)  ,_sstd_key_at( 373 ,__VA_ARGS__)  ,_sstd_key_at( 374 ,__VA_ARGS__)  ,_sstd_key_at( 375 ,__VA_ARGS__)  ,_sstd_key_at( 376 ,__VA_ARGS__)  ,_sstd_key_at( 377 ,__VA_ARGS__)  ,_sstd_key_at( 378 ,__VA_ARGS__)  ,_sstd_key_at( 379 ,__VA_ARGS__)  ,_sstd_key_at( 380 ,__VA_ARGS__)  ,_sstd_key_at( 381 ,__VA_ARGS__)  ,_sstd_key_at( 382 ,__VA_ARGS__)  ,_sstd_key_at( 383 ,__VA_ARGS__)  ,_sstd_key_at( 384 ,__VA_ARGS__)   \
,_sstd_key_at( 385 ,__VA_ARGS__)  ,_sstd_key_at( 386 ,__VA_ARGS__)  ,_sstd_key_at( 387 ,__VA_ARGS__)  ,_sstd_key_at( 388 ,__VA_ARGS__)  ,_sstd_key_at( 389 ,__VA_ARGS__)  ,_sstd_key_at( 390 ,__VA_ARGS__)  ,_sstd_key_at( 391 ,__VA_ARGS__)  ,_sstd_key_at( 392 ,__VA_ARGS__)  ,_sstd_key_at( 393 ,__VA_ARGS__)  ,_sstd_key_at( 394 ,__VA_ARGS__)  ,_sstd_key_at( 395 ,__VA_ARGS__)  ,_sstd_key_at( 396 ,__VA_ARGS__)  ,_sstd_key_at( 397 ,__VA_ARGS__)  ,_sstd_key_at( 398 ,__VA_ARGS__)  ,_sstd_key_at( 399 ,__VA_ARGS__)  ,_sstd_key_at( 400 ,__VA_ARGS__)  ,_sstd_key_at( 401 ,__VA_ARGS__)  ,_sstd_key_at( 402 ,__VA_ARGS__)  ,_sstd_key_at( 403 ,__VA_ARGS__)  ,_sstd_key_at( 404 ,__VA_ARGS__)  ,_sstd_key_at( 405 ,__VA_ARGS__)  ,_sstd_key_at( 406 ,__VA_ARGS__)  ,_sstd_key_at( 407 ,__VA_ARGS__)  ,_sstd_key_at( 408 ,__VA_ARGS__)  ,_sstd_key_at( 409 ,__VA_ARGS__)  ,_sstd_key_at( 410 ,__VA_ARGS__)  ,_sstd_key_at( 411 ,__VA_ARGS__)  ,_sstd_key_at( 412 ,__VA_ARGS__)  ,_sstd_key_at( 413 ,__VA_ARGS__)  ,_sstd_key_at( 414 ,__VA_ARGS__)  ,_sstd_key_at( 415 ,__VA_ARGS__)  ,_sstd_key_at( 416 ,__VA_ARGS__)  ,_sstd_key_at( 417 ,__VA_ARGS__)  ,_sstd_key_at( 418 ,__VA_ARGS__)  ,_sstd_key_at( 419 ,__VA_ARGS__)  ,_sstd_key_at( 420 ,__VA_ARGS__)  ,_sstd_key_at( 421 ,__VA_ARGS__)  ,_sstd_key_at( 422 ,__VA_ARGS__)  ,_sstd_key_at( 423 ,__VA_ARGS__)  ,_sstd_key_at( 424 ,__VA_ARGS__)  ,_sstd_key_at( 425 ,__VA_ARGS__)  ,_sstd_key_at( 426 ,__VA_ARGS__)  ,_sstd_key_at( 427 ,__VA_ARGS__)  ,_sstd_key_at( 428 ,__VA_ARGS__)  ,_sstd_key_at( 429 ,__VA_ARGS__)  ,_sstd_key_at( 430 ,__VA_ARGS__)  ,_sstd_key_at( 431 ,__VA_ARGS__)  ,_sstd_key_at( 432 ,__VA_ARGS__)  ,_sstd_key_at( 433 ,__VA_ARGS__)  ,_sstd_key_at( 434 ,__VA_ARGS__)  ,_sstd_key_at( 435 ,__VA_ARGS__)  ,_sstd_key_at( 436 ,__VA_ARGS__)  ,_sstd_key_at( 437 ,__VA_ARGS__)  ,_sstd_key_at( 438 ,__VA_ARGS__)  ,_sstd_key_at( 439 ,__VA_ARGS__)  ,_sstd_key_at( 440 ,__VA_ARGS__)  ,_sstd_key_at( 441 ,__VA_ARGS__)  ,_sstd_key_at( 442 ,__VA_ARGS__)  ,_sstd_key_at( 443 ,__VA_ARGS__)  ,_sstd_key_at( 444 ,__VA_ARGS__)  ,_sstd_key_at( 445 ,__VA_ARGS__)  ,_sstd_key_at( 446 ,__VA_ARGS__)  ,_sstd_key_at( 447 ,__VA_ARGS__)  ,_sstd_key_at( 448 ,__VA_ARGS__)   \
,_sstd_key_at( 449 ,__VA_ARGS__)  ,_sstd_key_at( 450 ,__VA_ARGS__)  ,_sstd_key_at( 451 ,__VA_ARGS__)  ,_sstd_key_at( 452 ,__VA_ARGS__)  ,_sstd_key_at( 453 ,__VA_ARGS__)  ,_sstd_key_at( 454 ,__VA_ARGS__)  ,_sstd_key_at( 455 ,__VA_ARGS__)  ,_sstd_key_at( 456 ,__VA_ARGS__)  ,_sstd_key_at( 457 ,__VA_ARGS__)  ,_sstd_key_at( 458 ,__VA_ARGS__)  ,_sstd_key_at( 459 ,__VA_ARGS__)  ,_sstd_key_at( 460 ,__VA_ARGS__)  ,_sstd_key_at( 461 ,__VA_ARGS__)  ,_sstd_key_at( 462 ,__VA_ARGS__)  ,_sstd_key_at( 463 ,__VA_ARGS__)  ,_sstd_key_at( 464 ,__VA_ARGS__)  ,_sstd_key_at( 465 ,__VA_ARGS__)  ,_sstd_key_at( 466 ,__VA_ARGS__)  ,_sstd_key_at( 467 ,__VA_ARGS__)  ,_sstd_key_at( 468 ,__VA_ARGS__)  ,_sstd_key_at( 469 ,__VA_ARGS__)  ,_sstd_key_at( 470 ,__VA_ARGS__)  ,_sstd_key_at( 471 ,__VA_ARGS__)  ,_sstd_key_at( 472 ,__VA_ARGS__)  ,_sstd_key_at( 473 ,__VA_ARGS__)  ,_sstd_key_at( 474 ,__VA_ARGS__)  ,_sstd_key_at( 475 ,__VA_ARGS__)  ,_sstd_key_at( 476 ,__VA_ARGS__)  ,_sstd_key_at( 477 ,__VA_ARGS__)  ,_sstd_key_at( 478 ,__VA_ARGS__)  ,_sstd_key_at( 479 ,__VA_ARGS__)  ,_sstd_key_at( 480 ,__VA_ARGS__)  ,_sstd_key_at( 481 ,__VA_ARGS__)  ,_sstd_key_at( 482 ,__VA_ARGS__)  ,_sstd_key_at( 483 ,__VA_ARGS__)  ,_sstd_key_at( 484 ,__VA_ARGS__)  ,_sstd_key_at( 485 ,__VA_ARGS__)  ,_sstd_key_at( 486 ,__VA_ARGS__)  ,_sstd_key_at( 487 ,__VA_ARGS__)  ,_sstd_key_at( 488 ,__VA_ARGS__)  ,_sstd_key_at( 489 ,__VA_ARGS__)  ,_sstd_key_at( 490 ,__VA_ARGS__)  ,_sstd_key_at( 491 ,__VA_ARGS__)  ,_sstd_key_at( 492 ,__VA_ARGS__)  ,_sstd_key_at( 493 ,__VA_ARGS__)  ,_sstd_key_at( 494 ,__VA_ARGS__)  ,_sstd_key_at( 495 ,__VA_ARGS__)  ,_sstd_key_at( 496 ,__VA_ARGS__)  ,_sstd_key_at( 497 ,__VA_ARGS__)  ,_sstd_key_at( 498 ,__VA_ARGS__)  ,_sstd_key_at( 499 ,__VA_ARGS__)  ,_sstd_key_at( 500 ,__VA_ARGS__)  ,_sstd_key_at( 501 ,__VA_ARGS__)  ,_sstd_key_at( 502 ,__VA_ARGS__)  ,_sstd_key_at( 503 ,__VA_ARGS__)  ,_sstd_key_at( 504 ,__VA_ARGS__)  ,_sstd_key_at( 505 ,__VA_ARGS__)  ,_sstd_key_at( 506 ,__VA_ARGS__)  ,_sstd_key_at( 507 ,__VA_ARGS__)  ,_sstd_key_at( 508 ,__VA_ARGS__)  ,_sstd_key_at( 509 ,__VA_ARGS__)  ,_sstd_key_at( 510 ,__VA_ARGS__)  ,_sstd_key_at( 511 ,__VA_ARGS__)  >::type
#endif
