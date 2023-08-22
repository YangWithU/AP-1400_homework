#include "server.h"
#include "client.h"

#include <random>
#include <chrono>

// pending transaction
std::vector<std::string> pending_trxs;

Server::Server() = default;

std::shared_ptr<Client> Server::add_client(std::string id) {
    bool add_rand = false;
    for(auto &x : clients) {
        if(x.first->get_id() == id) {
            add_rand = true;
            break;
        }
    }
    if(add_rand) {
        std::mt19937_64 generator(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> gen_dist(1, 9);
        for(int i = 0; i < 4; i++) {
            id += std::to_string(gen_dist(generator));
        }
    }
    auto cli_ptr = std::make_shared<Client>(id, *this);
    clients[cli_ptr] = 5.0;
    return cli_ptr;
}

std::shared_ptr<Client> Server::get_client(std::string id) {
    for(auto &x : clients) {
        if(x.first->get_id() == id) {
            return x.first;
        }
    }
}

