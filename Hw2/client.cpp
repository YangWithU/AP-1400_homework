#include "client.h"
#include "server.h"

Client::Client(std::string id_, const Server &server_) : id(id_), server(&server_) {
    crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id() {
    return this->id;
}

std::string Client::get_publickey() const {
    return this->public_key;
}

double Client::get_wallet() const {
    return server->get_wallet(this->id);
}

// use private_key to sign transaction
std::string Client::sign(std::string txt) const {
    return crypto::signMessage(this->private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) {
    std::string trx_ = id + "-" + receiver + "-" + std::to_string(value);
    if(server->add_pending_trx(trx_, sign(trx_))) {
        return true;
    }
    return false;
}

size_t Client::generate_nonce() {
    std::mt19937_64 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<std::size_t> rnd(0, std::numeric_limits<std::size_t>::max());
    return rnd(gen);
}



