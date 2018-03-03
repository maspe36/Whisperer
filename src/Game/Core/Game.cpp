//
// Created by Sam on 9/25/2017.
//

#include <utility>

#include "../../../include/Game/Core/Game.h"
#include "../../../include/Game/Core/Player.h"
#include "../../../include/Network/Client.h"
#include "../../../include/Network/Server.h"
#include "../../../include/Network/Message.h"

void Game::writePlayers(const std::string &data)
{
    for (const auto& player : players)
    {
        player->client->write(data);
    }
}

void Game::registerPlayers(const std::vector<std::shared_ptr<Player>> &players)
{
    for (const auto& player : players)
    {
        player->game = shared_from_this();
    }
}

void Game::startGame()
{
    Message start(Message::START_GAME);
    writePlayers(start.getJSON());
}

Game::Game(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Server> server)
        : players(std::move(players)), server(std::move(server))
{
    registerPlayers(players);
    startGame();
}

Game::~Game()
= default;
