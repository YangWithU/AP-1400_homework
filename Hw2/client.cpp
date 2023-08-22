#include "client.h"

Client::Client(std::string id_, const Server &server_) : id(id_), server(&server_) {
    crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id() {
    return this->id;
}



