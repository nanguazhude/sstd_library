#include <sstd_library.hpp>
#include <array>
#include <iostream>

static int valueTest = 1;

class A : public virtual sstd::GCMemoryNode {
    using super = sstd::GCMemoryNode;
    int value = ++valueTest;
public:
    using super::super;
    inline ~A() {
        std::cout << __func__ << value << std::endl;
    }
};

class B : public virtual sstd::GCMemoryNode {
    using super = sstd::GCMemoryNode;
    int value = ++valueTest;
public:
    using super::super;
    inline ~B() {
        std::cout << __func__ << value << std::endl;
    }
};

class C : public A, public B {
    using super = sstd::GCMemoryNode;
    int value = ++valueTest;
public:
    inline C(const sstd::gc_lock& arg) : super(arg),
        A(arg),
        B(arg) {
    }
public:
    inline ~C() {
        std::cout << __func__ << value << std::endl;
    }
public:
    inline void construct() {
        sstd::gc_lock varLock{ *getGCMemoryManager() };
        a = this;
        b = this;
        c = this;
        for (auto & varI : data) {
            if (std::rand() & 1) {
                varI = sstd::GCMemoryManager::createObject<A>(varLock);
            } else {
                varI = sstd::GCMemoryManager::createObject<B>(varLock);
            }
        }
    }
    void directChildren(sstd::GCMemoryNodeChildrenWalker * arg) {
        A::directChildren(arg);
        B::directChildren(arg);
        arg->findChild(a);
        arg->findChild(b);
        arg->findChild(c);
        for (auto & varI : data) {
            arg->findChild(varI);
        }
    }
    A * a{ nullptr };
    B * b{ nullptr };
    C * c{ nullptr };
    std::array< sstd::GCMemoryNode *, 16 > data;
};

void testGCManager() {

    auto varManager =
        sstd_make_shared<sstd::GCMemoryManager>();

    C * varObject;
    {
        /*构造的时候暂停gc*/
        varObject = varManager->createObject<C>(varManager);
        varObject->markAsRoot();
        varObject->construct();
    }
    
    varManager->gc();
    varManager->gc();

    varObject->markAsRoot<false>();

    varManager->gc();
    varManager->gc();

}


