#include <iostream>
#include <gtest/gtest.h>

#include "client.h"
#include "server.h"

void  show_pending_transactions()
{
    std::cout  <<  std::string(20, '*') <<  std::endl;
    for(const  auto& trx : pending_trxs)
        std::cout << trx <<  std::endl;
    std::cout  <<  std::string(20, '*') <<  std::endl;
}

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        Server server_;
        auto Alice = server_.add_client("aaalice");
        auto Bob = server_.add_client("bbbob");

        std::string sd, rc;
        double cash;

        Alice->transfer_money("bbbob", 1.14);
        show_pending_transactions();
        std::cout << Bob->get_wallet() << '\n';
        std::cout << Alice->get_wallet() << '\n';
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