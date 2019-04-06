 template< auto A0 
,auto A1  ,auto ... Args >  
class string_constexpr_builder_helper< 2, A0
 , A1  ,Args ... > {
public: 
using type = constexpr_string_literal< A0   , A1 >;
};
