//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CLIENT_H
#define WHISPERERENGINE_CLIENT_H


#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>

class Player;
class Server;
class Card;

class Client
        : public boost::enable_shared_from_this<Client>
{
public:
    typedef boost::shared_ptr<Client> pointer;

    std::string delimiter;
    boost::asio::streambuf buffer;
    Player* player;
    Server* server;
    bool listening;

    static pointer Create(boost::asio::io_service& ioService);
    boost::asio::ip::tcp::socket& GetSocket();

    void Start(Server* server);
    void Write(std::string data);
    void Disconnect();
    void AsyncListen();
    void Listen(const boost::system::error_code & errorCode);

private:
    boost::asio::ip::tcp::socket socket;

    static std::string GetString(boost::asio::streambuf& buffer);
    void OnWrite(const boost::system::error_code& error, size_t bytesTransferred) const;

    explicit Client(boost::asio::io_service& ioService);
};


#endif //WHISPERERENGINE_CLIENT_H
