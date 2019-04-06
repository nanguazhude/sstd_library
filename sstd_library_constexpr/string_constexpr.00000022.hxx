 template< auto A0 
,auto A1 ,auto A2 ,auto A3 ,auto A4 ,auto A5 ,auto A6 ,auto A7 ,auto A8 ,auto A9 ,auto A10 ,auto A11 ,auto A12 ,auto A13 ,auto A14 ,auto A15 ,auto A16 ,auto A17 ,auto A18 ,auto A19 ,auto A20 ,auto A21 ,auto A22  ,auto ... Args >  
class string_constexpr_builder_helper< 23, A0
 , A1  , A2  , A3  , A4  , A5  , A6  , A7  , A8  , A9  , A10  , A11  , A12  , A13  , A14  , A15  , A16  , A17  , A18  , A19  , A20  , A21  , A22  ,Args ... > {
public: 
using type = constexpr_string_literal< A0   , A1  , A2  , A3  , A4  , A5  , A6  , A7  , A8  , A9  , A10  , A11  , A12  , A13  , A14  , A15  , A16  , A17  , A18  , A19  , A20  , A21  , A22 >;
};
