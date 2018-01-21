//
// Created by Sam on 9/25/2017.
//

#include "../../include/Network/Client.h"
#include "../../include/Network/Server.h"
#include "../../include/Game/Core/Game.h"
#include "../../include/Game/Core/Player.h"
#include "../../include/Network/Message.h"

#include <iostream>

typedef boost::shared_ptr<Client> pointer;


pointer Client::Create(boost::asio::io_service & ioService)
{
    return pointer(new Client(ioService));
}

boost::asio::ip::tcp::socket & Client::GetSocket()
{
    return socket;
}

std::string Client::GetAddress()
{
    return shared_from_this()->GetSocket().remote_endpoint().address().to_string();
}

void Client::Start(Server* server)
{
    this->server = server;
    Write(Message("success", "Connected!").exportJSON());

    listening = true;
    Write(Message("authentication", "What is your name?").exportJSON());
    AsyncListen(&Client::authenticateClient);
}

void Client::Write(std::string data)
{
    data.append(delimiter);

    boost::asio::async_write(socket, boost::asio::buffer(data.c_str(), data.size()),
                             boost::bind(&Client::OnWrite, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void Client::Disconnect()
{
    socket.close();
    server->RemoveClient(shared_from_this());
    std::cout << "Lost connection to client!" << std::endl;
}

void Client::AsyncListen(void (Client::*callback)())
{
    boost::asio::async_read_until(socket, buffer, delimiter,
                                  boost::bind(&Client::Listen, shared_from_this(),
                                              boost::asio::placeholders::error, callback));
}

void Client::Listen(const boost::system::error_code& errorCode, void (Client::*callback)())
{
    if (errorCode == nullptr && listening)
    {
        (*this.*callback)();
        AsyncListen(&Client::printMessage);
    }
    else
    {
        Disconnect();
    }
}

void Client::emptyBuffer()
{
    buffer.consume(buffer.size());
}

void Client::authenticateClient()
{
    std::string message = GetString(buffer);
    name = message;
    emptyBuffer();

    server->AddClient(shared_from_this());
    Write(Message("success", "successfully authenticated").exportJSON());
}

void Client::printMessage()
{
    std::string message = GetString(buffer);
    std::cout << "Message from " << name << ": " << message << std::endl;
    emptyBuffer();

    // Echo the message to the client
    Write(message);
}

std::string Client::GetString(boost::asio::streambuf& buffer)
{
    boost::asio::streambuf::const_buffers_type bufs = buffer.data();
    std::string data(
            boost::asio::buffers_begin(bufs),
            boost::asio::buffers_begin(bufs) + buffer.size());

    // Return everything except the last character delimeter
    return data.substr(0, data.size() - 1);
}

void Client::OnWrite(const boost::system::error_code & errorCode, size_t bytesTransferred) const
{
}

Client::Client(boost::asio::io_service & ioService)
        : player(nullptr), server(nullptr), listening(false), socket(ioService), delimiter("\n")
{
}

