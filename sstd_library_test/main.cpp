
#include <sstd_library.hpp>

#include <iostream>
#include <sstd/boost/context/fiber.hpp>

#include <cassert>

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

inline void testException(std::exception_ptr,
    std::string_view/*func*/,
    std::string_view/*file*/,
    int/*line*/) noexcept {
    std::cout << "exception ok" << std::endl;
}

int main(int, char **) {

    {
        using fiber = boost::context::fiber;
        fiber var([](fiber &&f) {
            std::cout << "Hellow World!" << std::endl;
            {
                auto varUniqueTest = sstd_make_unique<BClass>();
            }
            {
                auto varSharedTest = sstd_make_shared<BClass>();
            }
            return std::move(f);
        });
        var = std::move(var).resume();
    }

    {
        sstd_try{
            sstd_throw(123);
        } sstd_catch(...) {
            sstd_on_exception();
        }
    }

    {
        auto varOldException = sstd::getExceptionFunction();
        auto varOldNew = sstd::setExceptionFunction(&testException);
        assert(varOldException == varOldNew);
        assert(sstd::getExceptionFunction() == &testException);
        (void)varOldException;
        (void)varOldNew;
    }

    {
        sstd_try{
            sstd_throw(123);
        } sstd_catch(...) {
            sstd_on_exception();
        }
    }

    {
        std::vector< int, sstd_allocator<int> > test;
        test.push_back(1);
        test.push_back(3);
    }

    {
        auto var = sstd_make_virtual_unique<const BClass>();
    }

    {
        auto var = sstd_make_shared< const std::array<int, 3> >(1, 2, 3);
    }

    return 0;

}




