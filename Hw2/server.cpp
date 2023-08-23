#include "server.h"
#include "client.h"

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
    return nullptr;
}

double Server::get_wallet(std::string id) const {
    for(auto &[k, v]: clients) {
        if(k->get_id() == id) {
            return v;
        }
    }
    return 0;
}

// use regex to divide trx
bool Server::parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value) {
    std::regex pattern(R"(\b([\_a-zA-Z]+)-([\_a-zA-Z]+)-([0-9]+\.[0-9]+)\b)");
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
    auto p_sender = get_client(sender_);
    auto p_receiver = get_client(receiver_);
    if(p_receiver == nullptr) {
        return false;
    }
    bool authentic = crypto::verifySignature(p_sender->get_publickey(), trx, signature);
    if(authentic and clients.at(p_sender) >= value_) {
        pending_trxs.push_back(trx);
        return true;
    }
    return false;
}

size_t Server::mine() {
    std::string mem_pool{};
    for(auto &x : pending_trxs) {
        mem_pool += x;
    }
    for(auto &[k, v] : clients) {
        std::string res = mem_pool + std::to_string(k->generate_nonce());
        res = crypto::sha256(res);
        res = res.substr(0, 10);
        int cnt = 0;
        for(auto &x : res) {
            if(x == '0') {
                cnt++;
            }
        }
        if(cnt >= 3) {
            v += 6.25;
        }
        pending_trxs.clear();
        break;
    }
}

void  show_wallets(const Server& server)
{
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& client: server.clients)
        std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}