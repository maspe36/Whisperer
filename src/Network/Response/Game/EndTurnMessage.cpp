//
// Created by Sam on 3/17/2018.
//

#include "../../../../include/Network/Response/Game/EndTurnMessage.h"
#include "../../../../include/Game/Game.h"
#include "../../../../include/Game/Player.h"

EndTurnMessage::EndTurnMessage(EndTurnEvent endTurnEvent)
{
    auto toPlayer = endTurnEvent.player;
    auto game = endTurnEvent.game;

    std::vector<json> opponentsJSON = game->getOpponentJSON(toPlayer);

    rawJSON[TYPE_KEY] = Message::END_TURN;
    addDataMember("opponents", opponentsJSON);
    addDataMember("player", toPlayer->getState());
    addDataMember("gameState", game->getJSON(toPlayer));
}

EndTurnMessage::~EndTurnMessage()
= default;
