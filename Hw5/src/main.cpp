#include <iostream>
#include <gtest/gtest.h>
#include "ingredient.h"
#include "sub_ingredients.h"
#include "espresso_based.h"
#include "cappuccino.h"
#include "mocha.h"
#include <iostream>

class A {
public:
    virtual void vfunc() {
        std::cout << "base func called!\n";
    }
    virtual void pureVfunc() = 0;
};

class B : public A {
public:
    void vfunc() {
        std::cout << "derived func called!\n";
    }
    void pureVfunc() {
        std::cout << "pure v derived func called\n";
    }
};

int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        A* bp = new A();
        bp->pureVfunc();
        bp->vfunc();

    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}