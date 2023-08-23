#include "client.h"
#include "server.h"

Client::Client(std::string id_, const Server &server_) : id(id_), server(&server_) {
    crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id() {
    return this->id;
}

std::string Client::get_publickey() {
    return this->public_key;
}

double Client::get_wallet() const {
    return server->get_wallet(this->id);
}

std::string Client::sign(std::string txt) {
    return crypto::signMessage(this->private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) {
    std::string trx_ = id + "-" + receiver + "-" + std::to_string(value);
    std::string signature_ = crypto::signMessage(private_key, trx_);
    server->add_pending_trx(trx_, signature_);
}



