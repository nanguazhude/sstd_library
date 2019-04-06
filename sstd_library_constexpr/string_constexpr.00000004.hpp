 template< auto A0 
,auto A1 ,auto A2 ,auto A3 ,auto A4  ,auto ... Args >  
class string_constexpr_builder_helper< 5, A0
 , A1  , A2  , A3  , A4  ,Args ... > {
public: 
using type = constexpr_string_literal< A0   , A1  , A2  , A3  , A4 >;
};
