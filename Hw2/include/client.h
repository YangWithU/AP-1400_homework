#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"
#include "crypto.h"

class Server;
class Client {
public:
    Client(std::string id, const Server& server);
    std::string get_id();
    std::string get_publickey();
    double get_wallet() const;
    std::string sign(std::string txt);
    bool transfer_money(std::string receiver, double value);
    size_t generate_nonce();
private:
    // const*: 指针是一个常量指针，即指针本身是不可更改,不可更改指针让其改指
    // const server: 指针所指向的对象是一个常量对象，即该对象的值是不可修改
    // 等价于 const Server* const server
    Server const* const server;
    const std::string id;
    std::string public_key;
    std::string private_key;
};

#endif //CLIENT_H