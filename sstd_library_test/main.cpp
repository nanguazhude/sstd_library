
#include <sstd_library.hpp>

#include <iostream>
#include <sstd/boost/context/fiber.hpp>

class AClass {
private:
    sstd_class(AClass);
public:
    virtual ~AClass() = default;
    AClass() = default;
public:
    sstd_delete_copy_create(AClass);
};

class BClass : public AClass {
    sstd_class(BClass);
};

int main(int,char **){

    using fiber = boost::context::fiber;
    fiber var([](fiber &&f){
        std::cout << "Hellow World!" << std::endl;
        {
            auto varUniqueTest = sstd_make_unique<BClass>();
        }
        {
            auto varSharedTest = sstd_make_shared<BClass>();
        }
        return std::move(f);
    });
    var=std::move(var).resume();

}




