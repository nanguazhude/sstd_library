 template< auto A0
,auto A1 ,auto A2 ,auto A3 ,auto A4 ,auto A5  ,auto ... Args >
class string_constexpr_builder_helper< 6, A0
 , A1  , A2  , A3  , A4  , A5  ,Args ... > {
public:
using type = constexpr_string_literal< A0   , A1  , A2  , A3  , A4  , A5 >;
};
