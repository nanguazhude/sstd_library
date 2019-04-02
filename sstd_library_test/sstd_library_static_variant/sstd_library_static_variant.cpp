#include "sstd_library_static_variant.hpp"

#include <map>
#include <vector>
#include <unordered_map>
#include <shared_mutex>
#include <limits>

namespace _theSSTDLibraryStaticVariantFile {

    constexpr const static auto theNopos =
            std::numeric_limits<std::size_t>::max();

    class StaticClassInformation  {
    public:
        std::size_t index{1};
        std::type_index stdIndex ;
        std::basic_string< char, std::char_traits<char> ,sstd::allocator<char> > typeName;
        std::map< std::size_t ,
        ConvertFunction ,
        std::less<  >,
        sstd::allocator< std::pair<const std::size_t, ConvertFunction > > > convertFunctionMap;
        inline StaticClassInformation(const std::type_index & arg):
            stdIndex(arg){}
    public:
        sstd_class(StaticClassInformation);
    };

class StaticClass{
public:

    using Vector = std::vector<
    std::unique_ptr< StaticClassInformation > ,
    sstd::allocator< std::unique_ptr< StaticClassInformation > > >;

    using Map = std::unordered_map<
    std::type_index ,
    StaticClassInformation * ,
    std::hash< std::type_index >,
    std::equal_to<void>,
    sstd::allocator< std::pair< const std::type_index , StaticClassInformation * > > >;

    Vector thisListInformation;
    Map thisMapInformation;
    std::shared_mutex thisMutex;
private:
    std::size_t rawRegisterTypeID(const std::type_index & arg)   {

        auto varThisPos = thisMapInformation.find( arg );
        if( varThisPos != thisMapInformation.end() ){
            return varThisPos->second->index;
        }

        return theNopos ;
    }
public:
    inline std::size_t registerTypeID(const std::type_index & arg)  {

        {
            std::shared_lock varReadLock{ thisMutex };
            auto varAns = rawRegisterTypeID(arg);
            if( varAns != theNopos ){
                return varAns;
            }
        }

        {
            std::unique_lock varWriteLock{ thisMutex };
            auto varAns = rawRegisterTypeID(arg);
            if( varAns != theNopos ){
                return varAns;
            }
            thisListInformation.push_back( sstd_make_unique<StaticClassInformation>(arg) );
            auto varThePointer =
                    thisListInformation.back().get();
            varThePointer->index = thisListInformation.size() ;
            thisMapInformation[ arg ]=varThePointer;
            return varThePointer->index;
        }

    }

    inline bool registerCastFunction(std::size_t argFrom,
                                     std::size_t argTo,
                                     ConvertFunction argFunction){

        if( argFrom<1 ){
            return false;
        }

        if( argTo <1 ){
            return false;
        }

        std::unique_lock varWriteLock{ thisMutex };

        if( argFrom > thisListInformation.size() ){
            return false;
        }

        if( argTo > thisListInformation.size() ){
            return false;
        }

        if(argFunction==nullptr){
            thisListInformation[ argFrom - 1 ]->convertFunctionMap.erase(argTo);
        }else{
            thisListInformation[ argFrom - 1 ]->convertFunctionMap[argTo]= argFunction;
        }

        return true;

    }

    inline std::string_view findTypeName(std::size_t argIndex){
        if( argIndex < 1 ){
            return ""sv;
        }

         std::shared_lock varReadLock{ thisMutex };

         if ( argIndex > thisListInformation.size() ){
             return ""sv;
         }

         return thisListInformation[ argIndex - 1 ] ->typeName;

    }

    inline bool registerTypeName( std::size_t argIndex , std::string_view argName ){
        if( argIndex < 1 ){
            return false;
        }

        std::unique_lock varWriteLock{ thisMutex };

        if ( argIndex > thisListInformation.size() ){
            return false;
        }

        thisListInformation[ argIndex - 1 ] ->typeName = argName;

        return true;
    }

    inline ConvertFunction findCastFunction(std::size_t argFrom,std::size_t argTo){
        if( argFrom<1 ){
            return nullptr;
        }

        if( argTo <1 ){
            return nullptr;
        }

         std::shared_lock varReadLock{ thisMutex };

         if( argFrom > thisListInformation.size() ){
             return nullptr;
         }

         if( argTo > thisListInformation.size() ){
             return nullptr;
         }

         const auto & varMap =
            thisListInformation[ argFrom-1 ]->convertFunctionMap;

         auto varPos = varMap.find( argTo );
         if(varPos == varMap.end() ){
             return nullptr;
         }

         return varPos->second;

    }

public:
    sstd_class(  StaticClass );
};

inline StaticClass & getStaticClass(){
    static auto varAns = new StaticClass;
    return *varAns;
}

extern std::size_t registerTypeID(const std::type_index & arg){
    return getStaticClass().registerTypeID( arg );
}

extern bool registerCastFunction( std::size_t argFrom,
                           std::size_t argTo,
                           ConvertFunction argFunction){
    return getStaticClass().registerCastFunction(argFrom,argTo,argFunction);
}

extern  ConvertFunction findCastFunction(std::size_t argFrom,std::size_t argTo){
     return getStaticClass().findCastFunction(argFrom,argTo);
}

extern bool registerTypeName(std::size_t argIndex,
                             std::string_view argName){
    return getStaticClass().registerTypeName(argIndex,argName);
}

extern std::string_view typeName(std::size_t argIndex){
    return getStaticClass().findTypeName(argIndex);
}


}/**/




