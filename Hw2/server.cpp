#include "server.h"
#include "client.h"

#include <random>
#include <chrono>
#include <regex>

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

std::shared_ptr<Client> Server::get_client(std::string id) const {
    for(auto &x : clients) {
        if(x.first->get_id() == id) {
            return x.first;
        }
    }
}

double Server::get_wallet(std::string id) const {
    for(auto &x : clients) {
        if(x.first->get_id() == id) {
            return x.second;
        }
    }
    return 0;
}

// use regex to divide trx
bool Server::parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value) const {
    std::regex pattern(R"(\b[a-zA-Z]+-[a-zA-Z]+-[0-9]+\.[0-9]+\b)");
    std::smatch match;
    if(std::regex_match(trx, match, pattern)) {
        sender = match.str(1);
        receiver = match.str(2);
        value = stod(match.str(3));
    } else {
        throw std::runtime_error("trx incomplete");
    }
    return false;
}

// 1.use parse_trx to get sender, receiver, value
// 2.authenticate, check balance
bool Server::add_pending_trx(std::string trx, std::string signature) const {
    std::string sender_, receiver_;
    double value_;
    parse_trx(trx, sender_, receiver_, value_);
    auto p_client = get_client(sender_);
    bool authentic = crypto::verifySignature(p_client->get_publickey(), trx, signature);
    if(authentic and clients.at(p_client) >= value_) {
        pending_trxs.emplace_back(trx);
        return true;
    }
    return false;
}

size_t Server::mine() {
    return 0;
}


