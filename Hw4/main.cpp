#include <iostream>
#include <gtest/gtest.h>
#include "unique_ptr.h"
#include "shared_ptr.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        auto p1 = make_shared<std::string>("hello");
        p1 = p1;
        auto p2 = make_shared<std::string>("world");
        p2 = p1;
        std::cout << *p2 << '\n';
//        auto p1 = std::make_shared<std::string>("hello");
//        std::cout << p1.use_count() << '\n';
//        p1 = p1;
//        std::cout << p1.use_count() << '\n';
//        auto p2 = std::make_shared<std::string>("world");
//        std::cout << "p2 use before: " << p2.use_count() << '\n';
//        p2 = p1;
//        std::cout << "p2 use af: " << p2.use_count() << '\n';
//        std::cout << "p1 use af: " << p1.use_count() << '\n';
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