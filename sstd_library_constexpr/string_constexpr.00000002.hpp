 template< auto A0 
,auto A1 ,auto A2  ,auto ... Args >  
class string_constexpr_builder_helper< 3, A0
 , A1  , A2  ,Args ... > {
public: 
using type = constexpr_string_literal< A0   , A1  , A2 >;
};
