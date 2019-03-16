
#include <iostream>
#include <sstd/boost/context/fiber.hpp>

int main(int,char **){

    using fiber = boost::context::fiber;
    fiber var([](fiber &&f){
        std::cout << "Hellow World!" << std::endl;
        return std::move(f);
    });
    var=std::move(var).resume();

}




