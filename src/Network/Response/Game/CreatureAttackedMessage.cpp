//
// Created by Sam on 3/29/2018.
//

#include "../../../../include/Network/Response/Game/CreatureAttackedMessage.h"
#include "../../../../include/Game/Player.h"
#include "../../../../include/Game/Card/Creature.h"

CreatureAttackedMessage::CreatureAttackedMessage(CreatureAttackedEvent creatureAttackedEvent)
{
    auto target = creatureAttackedEvent.target;
    auto attacker = creatureAttackedEvent.attacker;

    rawJSON[TYPE_KEY] = Message::CREATURE_ATTACKED;
    rawJSON[DATA_KEY]["target"] = target->getJSON();
    rawJSON[DATA_KEY]["attacker"] = attacker->getJSON();
    rawJSON[DATA_KEY]["attackerOwner"] = creatureAttackedEvent.attacker->player->getJSON();
}

CreatureAttackedMessage::~CreatureAttackedMessage()
= default;
