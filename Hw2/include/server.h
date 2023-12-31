#ifndef SERVER_H
#define SERVER_H

#include "client.h"

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <regex>

extern std::vector<std::string> pending_trxs;

class Client;
class Server {
public:
    Server();
    // create a new Client with the specified id.
    // id already exists, add a random 4-digit number at the end of it
    std::shared_ptr<Client> add_client(std::string id);

    // get a pointer to a Client using its id.
    std::shared_ptr<Client> get_client(std::string id) const;

    // returns the wallet of the client with username id.
    double get_wallet(std::string id) const;

    // parse
    static bool parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value);
    bool add_pending_trx(std::string trx, std::string signature) const ;
    size_t mine();

    friend void show_wallets(const Server& server);
private:
    // map each client to its wallet
    // k,v: clients<client, wallet>
    std::map<std::shared_ptr<Client>, double> clients;
};

#endif //SERVER_H